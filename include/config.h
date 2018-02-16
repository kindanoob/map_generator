#ifndef CONFIG_H_
#define CONFIG_H_


#include <vector>
#include <cmath>

constexpr int kScreenWidth = 1200;
constexpr int kScreenHeight = 800;
constexpr int kMapWidthInTiles = 100;
constexpr int kMapHeightInTiles = 100;
constexpr int kTileWidthInPixels = 5;
constexpr int kTileHeightInPixels = 5;
constexpr int kMapWidthInPixels = kTileWidthInPixels * kMapWidthInTiles;
constexpr int kMapHeightInPixels = kTileWidthInPixels *  kMapHeightInTiles;
constexpr int kOffsetX = (kScreenWidth - kMapWidthInPixels) / 2;
constexpr int kOffsetY = (kScreenHeight - kMapHeightInPixels) / 2;
constexpr int kNumIterationsSmooth = 10;
constexpr double kSqrt2 = sqrt(2);
constexpr double kEpsilon = 0.000001;
constexpr int kMapFillPercentage = 48;


//if dead cell has number of neighbors that
//belongs to this set of values, it becomes alive, o/w it stays dead
const std::vector<int> BIRTH_VALUES = {5,6,7,8};

//if alive cell has number of neighbors that
//belongs to this set, it stays alive, o/w it becomes dead
const std::vector<int> SURVIVE_VALUES = {4,5,6,7,8};

///Examples of cellular automata:
//---https://en.wikipedia.org/wiki/Life-like_cellular_automaton
//---B5678/S45678 - default
//---B5678/S345678 - 25...55
//---B5678/S2345678 - 15...55
//---B5678/S12345678 - 10...40
//---B678/S12345678 - 10...80
//---B78/S12345678 - 40
//---B678/S35678 - 60, 65, 70, 75, 80
//---B35678/S35678 - 10, 15, 20,25
//---B35678/S235678 - 1...10
//---B5678/S25678 - 65, 70
//---B678/S2567
//---B4678/S35678 - Anneal - 45...55
//---B35678/S5678 - Diamoeba - 40...45
//---B3678/S34678 - Day & Night 20...40
//---B3/S23 - Conway's Game of Life
//---B368/S245 - Morley
//---B36/S125 - 2x2
//---B/S1
//---B/S12
//---B/S14
//---B/S23
//---B/S24
//---B123/S
//---B13/S

#endif // CONFIG_H_
