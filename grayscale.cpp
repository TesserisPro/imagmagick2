#include "std.h"
#include "worker.h"

class GrayscaleWorker : public Worker {
    public:
      GrayscaleWorker(MagickWand *wand, Nan::Callback *callback) : Worker(wand, callback) {  }

      void Execute() 
      {
          if(MagickTransformImageColorspace(wand, GRAYColorspace) == MagickFalse)
          {
              this->SetErrorMessage("Grayscale failed");
          }
      }
};

NAN_METHOD(grayscale){
  MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
  Nan::AsyncQueueWorker(new GrayscaleWorker(wand, new Nan::Callback(info[1].As<v8::Function>())));
}
