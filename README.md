# ImageMagic module for NodeJS

## Tested with
 - Linux x64
 - Windows x86 / Visual Studio 2015
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

To use imagemagick first you need to create and image, currently only reading from file is supported.

```js
const image = require('imagemagick2');

var img = image(filePath);
```

Than you can apply transformations and/or calculations on image with fluent style. Note than transformations/calculations and even reading image from file will be performed only after apply() method is called.

```js
    const image = require('imagemagick2');
    image(filePath) // Do nothing just save action
        .resize(640, 480) // Do nothing just save action
        .write(destinationPath) // Do nothing just save action
        .apply(); //Apply all actions
```

Apply returns promise.

```js
    const image = require('imagemagick2');

    image(filePath)
        .resize(640)
        .write(destination)
        .apply()
        .than(() => console.log("OK"))
        .catch(err => console.log("Error: " + err)); 
```

To handle results of every action you can use action callback. In case of any error action callback will not be called and global promise will fail;

```js
    const image = require('imagemagick2');

    image(filePath)
        .resize(640, 480, function(img){ console.log("Resize finished") })
        .write(destination)
        .apply();
```

Additionally you can perform any custom action after any operation with method do.

```js
    const image = require('imagemagick2');

    image(filePath)
        .resize(640, 480)
        .do(function(img) { console.log("Resize finished") })
        .write(destination)
        .apply();
```

### Apply time actions

In some cases you may need to decide to continue some transformations or not based on results of previous transformations/calculations. In that case you can use apply time actions.

```js
    const image = require('imagemagick2');

    image(filePath)
        .size(function(img, size) { 
                if(size.width > 640) 
                    img.resize(640)
                       .write(destination); 
              })
        .apply();
```

## Methods

### Resize

```js
    const image = require('imagemagick2');
    image(filePath).resize(640, 480, function(img){});
```

### Rotate

```js
    const image = require('imagemagick2');
    image(filePath).rotate(90 /* angle in degrees */, function(img){}); 
```

### Write

```js
    const image = require('imagemagick2');
    image(filePath).write(destinationFilePath, function(img){}); 
```

### Grayscale

```js
    const image = require('imagemagick2');
    image(filePath).grayscale(function(img){}); 
```

### Strip (remove all additional data like EXIF or thumbnails)

```js
    const image = require('imagemagick2');
    image(filePath).strip(function(img){}); 
```

### Size (retrieves image size)

```js
    const image = require('imagemagick2');
    image(filePath).size(function(img, size) { console.log(size.width, size.height) }); 
```

### Brightness histogram

```js
    const image = require('imagemagick2');
    image(filePath).brightnessHistogram(40 /* histogram components number*/, 
            function(img, hist /* array of values, each between 0 and 1 */) { }); 
```