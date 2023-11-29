Sphelix
=======
A twist reader for creating twist/roll joints in Maya

## Setup local development environment for Windows (Visual Studio)
1) Download and setup the Maya Devkit as per [Autodesk's documentation](https://help.autodesk.com/view/MAYAUL/2024/ENU/?guid=Maya_SDK_Setting_up_your_build_Windows_environment_64_bit_html)
2) Create a fork of this repo in your github account and create a local clone using:
```bash
git clone git@github.com:USERNAME/Sphelix.git
```
3) Navigate to the cloned repository and run the CMake generation command (make sure you have installed CMake 3.27 or higher):
```bash
cmake -B ./build -S ./ -G "Visual Studio 17 2022" -A x64
```
4) Open the directory in Visual Studio. Go to Project > CMake settings for SimpleMath4M > Show Advanced settings. Change the ``CMake generator`` to "Visual Studio 17 2022 Win64" and the ``CMake Executable`` to the path of your CMake executable. Save these settings by pressing ``CTRL + S``
5) Your development environment should be setup correctly. If you make any changes to the CMake configuration (such as modifying ``CMakeLists.txt``) visual studio should automatically regenerate the CMake build files. If not or if you are outside of your IDE you will need to re-run the command in step 3.
6) To build Sphelix simply navigate to the project directory and run:
```bash
cmake --build ./build
```
7) The ``.mll`` file will be located under ``./build/debug/``. You can then copy this file into the ``devkitBase/plug-ins/plug-ins`` directory you created in step 1. To test the plugin, open Maya and load the plugin through the plugins manager.

## Setup local development environment for MacOS (XCode) [Currently unavailable]