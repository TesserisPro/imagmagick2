#include "std.h"
#include "worker.h"

class ResizeWorker : public Worker {
    private:
      int width;
      int height;
    public:
      ResizeWorker(MagickWand *wand, int width, int height, Nan::Callback *callback) : Worker(wand, callback) 
      {
          this->width = width;
          this->height = height;
      }

      void Execute() 
      {
          if(MagickResizeImage(wand, width, height, LanczosFilter, 1.0) == MagickFalse)
          {
              this->SetErrorMessage("Resize image filed");
          }
      }
};

NAN_METHOD(resize){
  MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
  int width = (int)info[1].As<v8::Number>()->Value();
  int height = (int)info[2].As<v8::Number>()->Value();
  Nan::AsyncQueueWorker(new ResizeWorker(wand, width, height, new Nan::Callback(info[3].As<v8::Function>())));
}
