#include <array>
#include <cstdio>
#include <iostream>

const size_t size = 1'000'000;
const size_t tile = 1;
using ValueType = uint64_t;
std::array<ValueType, size> dst;

__global__ void kernel(uint64_t* d_dst) {
    ValueType i = blockIdx.x * blockDim.x + threadIdx.x;
    d_dst[i] = static_cast<ValueType>(static_cast<double>(i * i) / 3.0 + 0.5);
}

int DUMMYmain() {
    uint64_t* d_dst;

    float time;
    cudaEvent_t start, stop;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    cudaMalloc(reinterpret_cast<void**>(&d_dst), size * sizeof(ValueType));

    hello<<<size, tile>>>(d_dst);

    cudaDeviceSynchronize();

    cudaMemcpy(dst.data(), d_dst, size * sizeof(ValueType), cudaMemcpyDeviceToHost);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time, start, stop);

    for (size_t i = 0; i < size; ++i) {
        std::cout << dst[i];
        if ((i + 1) % 10) {
            std::cout << " ";
        } else {
            std::cout << "\n";
        }
    }

    printf("Time to generate:  %3.1f ms \n", time);

    return 0;
}
