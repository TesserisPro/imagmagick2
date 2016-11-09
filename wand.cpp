#include "std.h"
#include "worker.h"

class LoadWorker : public Worker {
    private:
      char *fileName;
    public:
      LoadWorker(MagickWand *wand, char *fileName, Nan::Callback *callback) : Worker(wand, callback) 
      {
          this->fileName = strdup(fileName);
      }

      ~LoadWorker()
      {
         free(this->fileName);
      }

      void Execute() 
      {
          if (MagickReadImage(this->wand, this->fileName) == MagickFalse) 
          {
              this->SetErrorMessage("Load image failed");
          }
      }
};

NAN_METHOD(load){
    Nan::Utf8String fileName(info[0].As<v8::String>());
    MagickWand *wand = NewMagickWand();
    Nan::AsyncQueueWorker(new LoadWorker(wand, *fileName, new Nan::Callback(info[1].As<v8::Function>())));
}

NAN_METHOD(close){
    MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
    DestroyMagickWand(wand);
}

NAN_METHOD(clone){
    MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
    MagickWand *newWand = CloneMagickWand(wand);
    info.GetReturnValue().Set(v8::External::New(Nan::GetCurrentContext()->GetIsolate(), newWand));
}