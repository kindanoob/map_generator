# map_generator
Procedural map generator implemented in C++ using SFML

Requirements: 1) C++11, 2) SFML 2.3.2

The program was tested on Ubuntu 16.04 LTS Xenial, gcc 5.4.0.

Instructions:

1) For an out-of-place build: create a build directory (mkdir build)
2) Change directory to the created build directory (cd build)
3) Create build files with CMake in the build directory (cmake ..)
4) Build the project (e.g. for Unix makefiles it is achieved by using "make" command in the terminal)
5) Launch the executable file "map_generator".
6) Keyboard controls. Press "G" to generate new map.

Algorithm of map generator is as follows. First, the random map is created. That is, each cell of the map is set to filled with  probability P (the default value is 0.48) and is set to empty with probability 1 - P. After this the map is smoothed using the technique of cellular automata. At this point the map represents several (possibly, one) disconnected rooms. We choose one room as the "main room" and connect the main room to other rooms (if any). After this round of connections the map is smoothed once again. Now, there may still be rooms that are not connected. We connect them, so that now all the rooms are connected. So in the end we have a map with one connected component that is smooth and looks like a dungeon. Well, at least it should look like a dungeon. The parameters can be tuned to make the map and rooms look more realistic and dungeon-like.

If you want to learn more about cellular automata, please refer to the following wikipedia articles https://en.wikipedia.org/wiki/Cellular_automaton, https://en.wikipedia.org/wiki/Life-like_cellular_automaton.
