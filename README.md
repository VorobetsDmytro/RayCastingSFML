# Ray Casting: SFML + C++

![123](https://user-images.githubusercontent.com/82779713/181919048-dcec408c-4137-4d5f-8b98-609ecb77c95a.png)

## Requirements
1. GCC MinGW (SEH) 64-bit: Minimum version - 7.3.0

2. GNU Make: Recommended version - 3.81

3. CMake: Recommended version - 3.20

4. C++17

## Build
Firstly recommended to create a new directory`(example "mkdir build")` and move to`(example "cd build")`.

The next step is generating build files:
>`cmake .. -G "MinGW Makefiles"`

After this you have to build the project:
>`cmake --build`

## Settings
You can change the game settings in "main.cpp" file.

## Start
Execute `"*.exe"` file in the build directory.

## Control
To move the rays you can just move your mouse.

To rotate the rays:

    1. Сounterclockwise
    - Scroll your mouse wheel up

    2. Clockwise:
    - Scroll your mouse wheel down

## Author
[Dmytro Vorobets](https://github.com/Parasik72)
