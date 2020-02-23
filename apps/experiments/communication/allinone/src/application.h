#ifndef APPLICATION_H_9847tzj238t73y87
#define APPLICATION_H_9847tzj238t73y87

class Application
{
public:
    virtual ~Application() = default;

    virtual void run() = 0;
    virtual void terminate() = 0;
};

#endif
