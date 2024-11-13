#ifndef __IENGINABLE_CPP__
#define __IENGINABLE_CPP__

namespace minig {
    class IEnginable {
    public:
        virtual void pre_run() = 0;
        virtual void run() = 0;
    }; 
}
#endif