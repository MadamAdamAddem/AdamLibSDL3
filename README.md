# AdamLibSDL3
## 2D Cross-Platform Game Engine/Library
AdamLib is a game development library written with the intention of allowing fast development using C++ itself as the main scripting language. An easy interface is provided allowing easy production of reuseable scenes. SDL3 suite libraries serve as the only external dependencies, providing built-in cross-compatibility for most desktop, mobile, console, and web platforms.

## Building
[Install the dependencies](https://gist.github.com/NoxFly/1067c9fc24024d26b51a6825de5cff74) SDL3 and SDL3_image.

Clone the repo using: 
>git clone https://github.com/MadamAdamAddem/AdamLibSDL3

Build and compile using:
>cd AdamLibSDL3

>mkdir build && cd build

>cmake .\.

>make

The shared library will be located within build/src, and an example binary will have compiled within build/examples.
