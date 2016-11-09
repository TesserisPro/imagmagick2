#include "std.h"
#include "worker.h"

class WriteWorker : public Worker {
    private:
      char *fileName;
    public:
      WriteWorker(MagickWand *wand, char *fileName, Nan::Callback *callback) : Worker(wand, callback) 
      {
          this->fileName = strdup(fileName);
      }

      ~WriteWorker()
      {
         free(this->fileName);
      }

      void Execute() 
      {
          if (MagickWriteImage(this->wand, this->fileName) == MagickFalse) 
          {
              this->SetErrorMessage("Write image filed");
          }
      }
};

NAN_METHOD(write){
    MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
    Nan::Utf8String fileName(info[1].As<v8::String>());
    Nan::AsyncQueueWorker(new WriteWorker(wand, *fileName, new Nan::Callback(info[2].As<v8::Function>())));
}