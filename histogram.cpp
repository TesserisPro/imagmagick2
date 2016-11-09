#include "std.h"
#include "worker.h"

class BrightnessHistogramWorker : public Worker {
    private:
      int size;
      double *histogram;
    
    public:
      BrightnessHistogramWorker(MagickWand *wand, int size, Nan::Callback *callback) : Worker(wand, callback) 
      {
          this->size = size;
          if(this->size > 256 || this->size < 2){
              this->size = 256;
          }
          this->histogram = (double *)malloc(sizeof(double)*size);
      }

      ~BrightnessHistogramWorker(){
          free(this->histogram);
      }

      void Execute() 
      {
          memset(histogram, 0, sizeof(double)*size);
          MagickWand *grayscale = CloneMagickWand(wand);
          MagickTransformImageColorspace(grayscale, GRAYColorspace);
          size_t width = MagickGetImageWidth(grayscale);
	      size_t height = MagickGetImageHeight(grayscale);
          size_t pixels_size = width * height;
          unsigned char *pixels = (unsigned char *)malloc(pixels_size);
          
          if ( MagickExportImagePixels(grayscale, 0, 0, width, height, "I", CharPixel, pixels) == MagickFalse ){
              this->SetErrorMessage("Histogram calculation failed");
              free(pixels);
              return;
          }
          
          unsigned char rangeSize = 256 / size;

          for(size_t i = 0; i < pixels_size; i++)
          {
              unsigned char range = pixels[i] / rangeSize;
              if(range >= 0 && range < size)
              {
                  histogram[range]++;
              }
          }
          
          free(pixels);

          for(int i = 0; i < size; i++)
          {
              histogram[i] /= ((double)pixels_size);
          }
          DestroyMagickWand(grayscale);
      }

      void HandleOKCallback() 
      {
          v8::Local<v8::Array> result = Nan::New<v8::Array>(size);
          for(int i = 0; i < size; i++)
          {
               result->Set(i, Nan::New(histogram[i]));
          }
          v8::Local<v8::Value> argv[] = { Nan::Null(), result };
          this->callback->Call(2, argv);
      }
};

NAN_METHOD(brightnessHistogram){
    MagickWand *wand = (MagickWand *)info[0].As<v8::External>()->Value();
    int size = (int)info[1].As<v8::Number>()->Value();
    Nan::AsyncQueueWorker(new BrightnessHistogramWorker(wand, size, new Nan::Callback(info[2].As<v8::Function>())));
}
