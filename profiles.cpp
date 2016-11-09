#include "std.h"
#include "worker.h"

class StripWorker : public Worker {
    public:
      StripWorker(MagickWand *wand, Nan::Callback *callback) : Worker(wand, callback) { }

      void Execute() 
      {
          MagickStripImage(wand);
      }
};

NAN_METHOD(strip) {
    MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
    Nan::AsyncQueueWorker(new StripWorker(wand, new Nan::Callback(info[1].As<v8::Function>())));
}


NAN_METHOD(size) {
    MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
    size_t width = MagickGetImageWidth(wand);
	size_t height = MagickGetImageHeight(wand);
    v8::Local<v8::Object> result = Nan::New<v8::Object>();
    
    Nan::Set(result, v8::String::NewFromUtf8(Nan::GetCurrentContext()->GetIsolate(), "width"), Nan::New((int)width));
    Nan::Set(result, v8::String::NewFromUtf8(Nan::GetCurrentContext()->GetIsolate(), "height"), Nan::New((int)height));
    
    info.GetReturnValue().Set(result);
}