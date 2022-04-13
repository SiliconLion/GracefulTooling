

# Graceful Tooling

* requires cmake, make (I have cmake 20, so that is what the min version is set to, but if you have a slightly lower version you can just reduce the version in the cmake files).
* Download the appropreate zip from https://www.sfml-dev.org/download/sfml/2.5.1/ 
### Setting up for MacOS
* Unzip and copy all the .dylib files from `lib` into `/urs/local/lib`
* Thats it :)
### Setting up Windows, MinGW
* Unzip and copy all the .dll files from `bin` into the appropreate place for .dll files for MinGW
* Set `SFML_LIB_LOCATION` in the toplevel `CMakeLists.txt`
* May need to link OpenGL or other necessary libraries at the bottom of the top level `CMakeLists.txt`
### Building
```shell
cd cmake-build-debug
cmake ..
make 
```
Fingers crossed and everything should just work. 