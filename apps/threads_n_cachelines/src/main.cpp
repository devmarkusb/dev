#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

// !!! YOU MUST UPDATE THIS TO BE ACCURATE !!!
constexpr size_t hardware_destructive_interference_size = 64;

// !!! YOU MUST UPDATE THIS TO BE ACCURATE !!!
constexpr size_t hardware_constructive_interference_size = 64;

constexpr unsigned k_timing_trials_to_compute_average = 100;
constexpr unsigned k_inner_loop_trials = 1'000'000;

typedef unsigned UselessResultT;
typedef double ElapsedSecsT;

//////// CODE TO BE SAMPLED:

// wraps an int, default alignment allows false-sharing
struct NaiveInt {
    int value;
};

static_assert(alignof(NaiveInt) < hardware_destructive_interference_size, "");

// wraps an int, cache alignment prevents false-sharing
struct CacheInt {
    alignas(hardware_destructive_interference_size) int value;
};

static_assert(alignof(CacheInt) == hardware_destructive_interference_size, "");

// wraps a pair of int, purposefully pushes them too far apart for true-sharing
struct BadPair {
    int first;
    char padding[hardware_constructive_interference_size];
    int second;
};

static_assert(sizeof(BadPair) > hardware_constructive_interference_size, "");

// wraps a pair of int, ensures they fit nicely together for true-sharing
struct GoodPair {
    int first;
    int second;
};

static_assert(sizeof(GoodPair) <= hardware_constructive_interference_size, "");

// accesses a specific array element many times
template <typename T, typename Latch>
UselessResultT sample_array_threadfunc(Latch& latch, unsigned thread_index, T& vec) {
    // prepare for computation
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{0, 4'096};

    auto& element = vec[vec.size() / 2 + thread_index];

    latch.count_down_and_wait();

    // compute
    for (unsigned trial = 0; trial != k_inner_loop_trials; ++trial) {
        element.value = dist(mt);
    }

    return static_cast<UselessResultT>(element.value);
}

// accesses a pair's elements many times
template <typename T, typename Latch>
UselessResultT sample_pair_threadfunc(Latch& latch, unsigned, T& pair) {
    // prepare for computation
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{0, 4'096};

    latch.count_down_and_wait();

    // compute
    for (unsigned trial = 0; trial != k_inner_loop_trials; ++trial) {
        pair.first = dist(mt);
        pair.second = dist(mt);
    }

    return static_cast<UselessResultT>(pair.first) + static_cast<UselessResultT>(pair.second);
}

//////// UTILITIES:

// utility: allow threads to wait until everyone is ready
class Threadlatch {
public:
    explicit Threadlatch(const size_t count)
        : count_{count} {
    }

    void count_down_and_wait() {
        std::unique_lock<std::mutex> lock{mutex_};
        if (--count_ == 0) {
            cv_.notify_all();
        } else {
            cv_.wait(lock, [&] {
                return count_ == 0;
            });
        }
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    size_t count_;
};

namespace {
// utility: runs a given function in N threads
std::tuple<UselessResultT, ElapsedSecsT> run_threads(
    const std::function<UselessResultT(Threadlatch&, unsigned)>& func, const unsigned num_threads) {
    Threadlatch latch{num_threads + 1};

    std::vector<std::future<unsigned>> futures;
    std::vector<std::thread> threads;
    for (unsigned thread_index = 0; thread_index != num_threads; ++thread_index) {
        std::packaged_task<UselessResultT()> task{
            std::bind(func, std::ref(latch), thread_index)
            //[&]() { return func(latch, thread_index); }
        };

        futures.push_back(task.get_future());
        threads.push_back(std::thread(std::move(task)));
    }

    const auto starttime = std::chrono::high_resolution_clock::now();

    latch.count_down_and_wait();
    for (auto& thread : threads) {
        thread.join();
    }

    const auto endtime = std::chrono::high_resolution_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(endtime - starttime).count();

    unsigned result = 0;
    for (auto& future : futures) {
        result += future.get();
    }

    return std::make_tuple(result, elapsed);
}

// utility: sample the time it takes to run func on N threads
void run_tests(const std::function<UselessResultT(Threadlatch&, unsigned)>& func, const unsigned num_threads) {
    UselessResultT final_result = 0;
    double avgtime = 0.0;
    for (unsigned trial = 0; trial != k_timing_trials_to_compute_average; ++trial) {
        const auto result_and_elapsed = run_threads(func, num_threads);
        const auto result = std::get<UselessResultT>(result_and_elapsed);
        const auto elapsed = std::get<ElapsedSecsT>(result_and_elapsed);

        final_result += result;
        avgtime = (avgtime * trial + elapsed) / (trial + 1);
    }

    std::cout << "Average time: " << avgtime << " seconds, useless result: " << final_result << std::endl;
}
} // namespace

int main() {
    const auto cores = std::thread::hardware_concurrency();
    std::cout << "Hardware concurrency: " << cores << std::endl;

    std::cout << "sizeof(naive_int): " << sizeof(NaiveInt) << std::endl;
    std::cout << "alignof(naive_int): " << alignof(NaiveInt) << std::endl;
    std::cout << "sizeof(cache_int): " << sizeof(CacheInt) << std::endl;
    std::cout << "alignof(cache_int): " << alignof(CacheInt) << std::endl;
    std::cout << "sizeof(bad_pair): " << sizeof(BadPair) << std::endl;
    std::cout << "alignof(bad_pair): " << alignof(BadPair) << std::endl;
    std::cout << "sizeof(good_pair): " << sizeof(GoodPair) << std::endl;
    std::cout << "alignof(good_pair): " << alignof(GoodPair) << std::endl;

    {
        std::cout << "Running naive_int test." << std::endl;

        std::vector<NaiveInt> vec;
        vec.resize((1U << 28) / sizeof(NaiveInt)); // allocate 256 mibibytes

        run_tests(
            [&](Threadlatch& latch, unsigned thread_index) {
                return sample_array_threadfunc(latch, thread_index, vec);
            },
            cores);
    }
    {
        std::cout << "Running cache_int test." << std::endl;

        std::vector<CacheInt> vec;
        vec.resize((1U << 28) / sizeof(CacheInt)); // allocate 256 mibibytes

        run_tests(
            [&](Threadlatch& latch, unsigned thread_index) {
                return sample_array_threadfunc(latch, thread_index, vec);
            },
            cores);
    }
    {
        std::cout << "Running bad_pair test." << std::endl;

        BadPair p;

        run_tests(
            [&](Threadlatch& latch, unsigned thread_index) {
                return sample_pair_threadfunc(latch, thread_index, p);
            },
            cores);
    }
    {
        std::cout << "Running good_pair test." << std::endl;

        GoodPair p;

        run_tests(
            [&](Threadlatch& latch, unsigned thread_index) {
                return sample_pair_threadfunc(latch, thread_index, p);
            },
            cores);
    }
}
