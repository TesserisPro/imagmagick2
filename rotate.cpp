#include "std.h"
#include "worker.h"

class RotateWorker : public Worker {
    private:
      double angle;
    public:
      RotateWorker(MagickWand *wand, double angle, Nan::Callback *callback) : Worker(wand, callback) 
      {
          this->angle = angle;
      }

      void Execute() 
      {
          PixelWand *pixel = NewPixelWand();
          if(MagickRotateImage(wand, pixel, this->angle) == MagickFalse)
          {
              this->SetErrorMessage("Rotate image filed");
          }
          DestroyPixelWand(pixel);
      }
};

NAN_METHOD(rotate){
  MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
  double angle = info[1].As<v8::Number>()->Value();
  Nan::AsyncQueueWorker(new RotateWorker(wand, angle, new Nan::Callback(info[2].As<v8::Function>())));
}
