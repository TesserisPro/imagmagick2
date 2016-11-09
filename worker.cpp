#include "std.h"
#include "worker.h"


Worker::Worker(MagickWand *wand, Nan::Callback *callback) : AsyncWorker(callback) 
{
    this->wand = wand;
}

Worker::~Worker()
{
 
}

void Worker::HandleOKCallback() 
{
    v8::Local<v8::Value> argv[] = { Nan::Null(), v8::External::New(Nan::GetCurrentContext()->GetIsolate(), wand) };
    this->callback->Call(2, argv);
}

void Worker::HandleErrorCallback()
{
    ExceptionType severity;
    char *error = MagickGetException(this->wand, &severity);
    
    v8::Local<v8::Value> argv[] = { 
        v8::String::NewFromUtf8(Nan::GetCurrentContext()->GetIsolate(), error), 
        v8::External::New(Nan::GetCurrentContext()->GetIsolate(), wand) };

    this->callback->Call(2, argv);
}

