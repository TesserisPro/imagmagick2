# ImageMagic module for NodeJS

## Tested with
 - Linux x64
 - Windows x86
 - ImageMagic 6.9.6 
 - NodeJS 6.7.0

## Installation
1. Install ImageMagic 6.9.6
1. **Windows only** configure IMAGEMAGICK_HOME environment variable to root of ImageMagic installation (e.g. C:\Program Files (x86)\ImageMagick-6.9.6-Q16-HDRI )  
1. **Windows only** If you have problems with ssize_t during build comment line #246 in %IMAGEMAGICK_HOME%\include\magick\magick-baseconfig.h (typedef int ssize_t)
    TODO: Solve this issue in better way
1. npm install imagemagic2
1. **electorn only** You may need to rebuild library for specific node version user in electron

## Usage

### Basic Example

```js
    const image = require('imagemagick2');

    image(filePath)
        .resize(640)
        .write(destination)
        .apply()
        .than(() => console.log("OK"))
        .catch(err => console.log("Error"); 
```
