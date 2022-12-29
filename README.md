# DSIP
 A Digital Signal Processing c++ toolchain using Dear ImGui and ImPlot to display things.

 I started the DISP project as a cross platform toolchain for my masters thesis in digital signal processing. since then it went through multiple iterations. I avoided dependency managers like Conan and most external dependencies except CMake as build system. All dependencies will be downloaded and configured using CMake.

 ## A note on git submodules
 I found working with git submodules troublesome. Switching between branches with different submodules or versions is troublesome. Things break. They have their use cases but I think downloading dependencies with cmake is a much cleaner solution. This will allow a much finer control of how things should be managed by CMake. This makes it possible to let the user select the required dependencies one by one.

 ## Building
 TODO
