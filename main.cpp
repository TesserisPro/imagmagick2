#include "std.h"

static void cleanup(void*) {
    MagickWandTerminus();
}

static void startup(void) {
    MagickWandGenesis();
}

NAN_METHOD(load);
NAN_METHOD(clone);
NAN_METHOD(close);

NAN_METHOD(resize);

NAN_METHOD(rotate);

NAN_METHOD(write);

NAN_METHOD(strip);
NAN_METHOD(size);

NAN_METHOD(brightnessHistogram);

NAN_METHOD(grayscale);



NAN_MODULE_INIT(init) {
    startup();
    node::AtExit(cleanup);
    
    
    NAN_EXPORT(target, load);
    NAN_EXPORT(target, clone);
    NAN_EXPORT(target, close);

    NAN_EXPORT(target, resize);

    NAN_EXPORT(target, rotate);

    NAN_EXPORT(target, write);
    
    NAN_EXPORT(target, strip);
    NAN_EXPORT(target, size);

    NAN_EXPORT(target, brightnessHistogram);

    NAN_EXPORT(target, grayscale);
}

NODE_MODULE(imagemagick, init);

// int main(void)
// {
//     MagickWandGenesis();
//     MagickWand *wand = NewMagickWand();
//     MagickBooleanType status; 
    
//     status = MagickReadImage(wand, "/home/dmitry/Photo/.preview.DSC_4603.JPG");
//     if (status == MagickFalse) 
//     {
//         printf("Fail. \n");
//         return 1;
//     }
//     MagickResizeImage(wand, 106, 80, LanczosFilter, 1.0);

//     status=MagickWriteImage(wand, "/home/dmitry/Photo/1.preview.DSC_4603.JPG");
//     if (status == MagickFalse) 
//     {
//         printf("Fail. \n");
//         return 1;
//     }
  
//     wand=DestroyMagickWand(wand);
//     MagickWandTerminus();
//     printf("Hello");

//     return 0;
// }
