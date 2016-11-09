{
  "targets": [],
  'conditions': [
      ['OS=="linux"', {
        'targets': [
          {
            "target_name": 'imagemagick',
            "sources": [ "main.cpp", "worker.cpp", "wand.cpp", "resize.cpp", "write.cpp", "profiles.cpp", "histogram.cpp", "grayscale.cpp" ],
            "include_dirs" : ["<!(node -e \"require('nan')\")"],
            'libraries': ['<!@(pkg-config --libs MagickWand)'],
            "cflags": ['<!@(pkg-config --cflags MagickWand)']
          },
        ],
      }],
      ['OS=="win"', {
        'targets': [
          {
            "target_name": 'image-magick',
            "sources": [ "imagemagick.cpp" ],
            "include_dirs" : ["<!(node -e \"require('nan')\")"],
            'libraries': ['<!@(pkg-config --libs MagickWand)'],
            "cflags": ['<!@(pkg-config --cflags MagickWand)']
          },
        ],
      }]
  ]
}