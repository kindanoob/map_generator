# map_generator
![Procedural map generator](resources/map_generator.png?raw=true "Procedural map generator")

Procedural map generator implemented in C++ using SFML

Requirements: 1) C++14, 2) SFML 2.6.1, 3) CMake 3.22.1

The program was tested on Ubuntu 22.04 LTS Jammy, gcc 11.4.0.

Instructions for an out-or-place build:
1) Change the SFML_ROOT variable in the CMakeLists.txt file according to your SFML location.
2) Go to the directory containing the CMakeLists.txt file.
3) Run `cmake -S . -B build`. This will create a `build` directory and put CMake files there.
4) Go to the `build` directory.
5) Build the project (e.g. for Unix makefiles it is achieved by running `make` command in the terminal).
6) Launch the executable file "map_generator".
7) Keyboard controls. Press "G" to generate new map. Press "Escape" to close the program.

Algorithm of map generator is as follows. First, the random map is created. That is, each cell of the map is set to filled with  probability P (the default value is 0.48) and is set to empty with probability 1 - P. After this the map is smoothed using the technique of cellular automata. At this point the map represents several (possibly, one) disconnected rooms. We choose one room as the "main room" and connect the main room to other rooms (if any). After this round of connections the map is smoothed once again. Now, there may still be rooms that are not connected. We connect them, so that now all the rooms are connected. So in the end we have a map with one connected component that is smooth and looks like a dungeon. Well, at least it should look like a dungeon. The parameters can be tuned to make the map and rooms look more realistic and dungeon-like.

If you want to learn more about cellular automata, please refer to the following wikipedia articles https://en.wikipedia.org/wiki/Cellular_automaton, https://en.wikipedia.org/wiki/Life-like_cellular_automaton.
