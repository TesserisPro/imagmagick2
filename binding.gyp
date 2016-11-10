{
  "targets": [],
  'conditions': [
      ['OS=="linux"', {
        'targets': [
          {
            "target_name": 'imagemagick',
            "sources": [ "main.cpp", "worker.cpp", "wand.cpp", "resize.cpp", "write.cpp", "profiles.cpp", "histogram.cpp", "grayscale.cpp", "rotate.cpp" ],
            "include_dirs" : ["<!(node -e \"require('nan')\")"],
            'libraries': ['<!@(pkg-config --libs MagickWand)'],
            "cflags": ['<!@(pkg-config --cflags MagickWand)']
          },
        ],
      }],
      ['OS=="win"', {
        'targets': [
          {
            "target_name": 'imagemagick',
            "sources": [ "main.cpp", "worker.cpp", "wand.cpp", "resize.cpp", "write.cpp", "profiles.cpp", "histogram.cpp", "grayscale.cpp", "rotate.cpp" ],
            "include_dirs" : ["<!(node -e \"require('nan')\")", "<!(echo %IMAGEMAGICK_HOME%)\include"],
            'libraries': ['<!(echo %IMAGEMAGICK_HOME%)\lib\CORE_RL_magick_.lib', '<!(echo %IMAGEMAGICK_HOME%)\lib\CORE_RL_wand_.lib'],
            "cflags": ['-fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16']
          },
        ],
      }]
  ]
}