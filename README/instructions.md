# AdamLibSDL3
## Introduction
AdamLib is a game development library written with the intention of allowing fast development with no supplimentary scripting language. An easy interface is provided allowing fast production of reuseable scenes. Built-in cross-compatibility for most desktop, mobile, console, and web platforms is provided. </br> </br>

This engine is not intended for use/installation of beginners to programming or C++, as a moderate amount of knowledge is needed to set-up and use this library properly.</br>

## Pre-requisites to use
A C++ compiler, CMake, and git are required to build, compile, and use this library. A package manager is required to install dependencies. An IDE is strongly recommended but not required. </br>


## Step 1: Installing dependencies
The library at present date requires three external libraries to be installed: SDL3, SDL3_image and SDL3_ttf. Different instructions are given for the currently supported platforms, Windows and Linux. </br> </br>

### Windows
Ensure you have the MSYS2 package manager installed. Using the command-line interface, enter the following commands to install the required dependencies: </br>
>pacman -S mingw-w64-x86_64-sdl3 </br>
>pacman -S mingw-w64-x86_64-sdl3-image </br>
>pacman -S mingw-w64-x86_64-sdl3-ttf </br>

Once completed, you may proceed directly to Step 2. </br> </br>

### Linux
All linux operating systems should be equipped with a package manager. 
These can install the libraries directly to your system using the command line interface. </br> </br>

For the apt package manager, type the commands as shown into the command line </br>
> sudo apt update </br>
> sudo apt install libsdl3-dev</br>
> sudo apt install libsdl3-image-dev libsdl3-ttf-dev</br>

</br>

For the yum/dnf package manager, the commands are as shown 
> sudo dnf update </br>
> sudo dnf install SDL3-devel </br>
> sudo dnf install SDL3_image-devel SDL3_ttf-devel</br>

</br>

#### Example for the dnf manager: </br>

---
![](install_dependencies.png) </br>
---

</br>

## Step 2: Building and Compiling
Once you've installed the prerequisite dependencies open the command line and input the following command.

#### Warning: Ensure you're in a folder that does not contain another folder with the name 'AdamLibSDL3', as this following command may be destructive if so </br>
>git clone https://github.com/MadamAdamAddem/AdamLibSDL3 </br>

</br>


Then, Build and Compile using the following commands:
>cd AdamLibSDL3 </br>
>mkdir build && cd build </br>
>cmake .\. </br>
>make </br>


#### Example output: </br>
---
![](build_lib.png) </br>
---
</br>
After some time compiling, the library will be ready for use! </br> </br>

## Step 3: Setting up your project with AdamLib

The following steps show how to set up your project within the AdamLib directory. Other set-ups are possible, but are not within the scope of this tutorial. </br>

### Configuring CMake
Let **\<new_name\>** represent the name of your project. </br>
Let **\<executable_name\>** represent the name of your executable. </br>
Let **\<list_of_cpp_files\>** represent a space-seperated list of the c++ files you wish to compile. </br>

#### Locate and open the CMakeLists.txt file found at *AdamLibSDL3/examples/CMakeLists.txt* </br>

---
![](cmake_config1.png) </br>
---

</br>

#### Modify the file such that it looks like this image, with your project's specifics replacing the **\<representations\>**. </br>

---
![](cmake_config2.png)</br>
---

</br>

#### Once completed, replace the name of the *examples* folder with **\<new_name\>**, then locate and open the CMakeLists.txt file found at *AdamLibSDL3/CMakeLists.txt* </br>

---
![](cmake_config3.png) </br>
---

</br>

#### Modify the file such that it looks like this image replacing **\<new_name\>**. </br>

---
![](cmake_config4.png) </br>
---

</br>

### Configuring your IDE
After configuring the CMake files, open the AdamLibSDL3 folder in your IDE of choice. </br> 
Enter the IDE's settings and set the *include/AdamLib* directory to be a registered include directory. </br>
Since there are many different IDE's, no specifics can be provided; there should be instructions available online.</br> </br>

### Compiling your project
Once done configuring, simply repeat the Building and Compiling steps mentioned in Step 2. </br>
If you'd like to recompile without rebuilding, type *make* into the build directory. </br> </br>

## Step 4: Creating a main file

There should exist three files within what was previously the examples directory: </br>
>main.cpp, test.hpp, and testgame.cpp

You may read or use these files, but for the sake of this tutorial we will consider them to be deleted. </br> </br>

### Setting up the main loop
Create your file that will contain the main function, and define it.</br>
There are seven parts to a main function with AdamLib: </br>
>Initialization (1)</br>
>Input processing (2)</br>
>FPS Limiting (3)</br>
>Node processing (4)</br>
>Node freeing (5)</br>
>Rendering (6)</br>
>Finalization (7)</br>

#### Each of these parts has a corresponding function. The following image shows how these can be used simply. </br>

---
![](example_main.png) </br>
---

</br>
Most main loops will look exactly like this, with the game loading function being the only variation point. Ensure the headers are included like so: </br>

---
![](example_main2.png) </br>
---

</br![alt text](example_main.png)>

### Setting up your game skeleton
AdamLib functions using a **Node Tree**. Put simply, Nodes are the objects that exist within the world. </br>

These objects can have children, which move as the parent object moves, while maintaining their relative position. </br>

To create a Node, we must first create a **Node Template** to describe the qualities of the node, such as its name, default position, and what child nodes it will have. Then, when ready, we can create an instance of the node by placing it as a child of the Root node.</br>

Here is an example of just that: </br>
![](example_game.png) </br>

There exist multiple types of Node with different properties. For example, the SpriteNode contains an image which will be displayed on screen at the SpriteNode's position. To create one, use the corresponding NodeTemplate type and add the relative path to your image. </br>

![](sprite_path.png) </br>

## Finishing Remarks
When run, you should see your image display with the top left corner at x: 200, y: 200. </br>

Much more functionality is offered by the library, but this tutorial intends to teach you the basics. Use the intellisense offered by your IDE to scour for functions that may suit your interests, or check out the headers within the */include* Directory for more informaton. </br>