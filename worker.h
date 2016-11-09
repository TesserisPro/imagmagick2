#include "std.h"

class Worker : public Nan::AsyncWorker {
    public:
        Worker(MagickWand *wand, Nan::Callback *callback);
        ~Worker();
    protected:
        MagickWand *wand;
        void HandleOKCallback();
        void HandleErrorCallback();
};
