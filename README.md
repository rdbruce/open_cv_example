# open_cv_example
This is an image stabilization example using OpenCV in C++. The image stabilization works through feature tracking and moving the image to keep those features still. Features are represented in the program by little red dots. When the program is executed a window will pull up. Hit or hold the c key to advance the frames. Hit escape to kill the window. 

## Build instructions
These build instructions are an elaboration of [this example](https://blog.conan.io/2023/07/20/introduction-to-game-dev-with-sdl2.html).

### Install dependencies
Install Conan [here](https://docs.conan.io/1/installation.html)

Install CMake [download here](https://cmake.org/download/)

### Clone this repo and navigate to branch
```
git clone [https://github.com/rdbruce/final_pendulum.git](https://github.com/rdbruce/opencv_example.git)
cd opencv_example
```

### Conan packages
First run ```conan install . --build=missing```.
If you are running Linux and some necessary missing system libraries are missing on your system, you may have to add the ```-c tools.system.package_manager:mode=install``` or ```-c tools.system.package_manager:sudo=True``` flags.

### Build and Run
Building on Linux and macOS
```
cmake --preset conan-release
cmake --build --preset conan-release
cd build/Release
./final_pendulum
```

Building on Windows
```
cmake --preset conan-default
cmake --build --preset conan-release
cd build\Release
./opencv_example
```
