# AdamLibSDL3
## 2D Cross-Platform Game Engine/Library
AdamLib is a game development library written with the intention of allowing fast development using C++ itself as the main scripting language. An easy interface is provided allowing easy production of reuseable scenes. SDL3 suite libraries serve as the only external dependencies, providing built-in cross-compatibility for most desktop, mobile, console, and web platforms. </br>

## Building
[Install the dependencies](https://gist.github.com/NoxFly/1067c9fc24024d26b51a6825de5cff74) SDL3, SDL3_image, and SDL3_ttf. </br>
Clone the repo using: 
>git clone https://github.com/MadamAdamAddem/AdamLibSDL3 </br>

Build and compile using: </br>
>cd AdamLibSDL3 </br>
>mkdir build && cd build </br>
>cmake .\. </br>
>make </br>

The shared library will be located within build/src, and an example binary will have compiled within build/examples.
