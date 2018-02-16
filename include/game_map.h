#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <vector>
#include <SFML/Graphics.hpp>


class Room;
class Node;

class GameMap {
public:
    std::vector<std::vector<char>> char_map_;
    int width_ = 0;
    int height_ = 0;
    int map_fill_percentage_ = 0;
    int tile_width_in_pixels_ = 0;
    int tile_height_in_pixels_ = 0;
    std::vector<Room *> room_vector_;
public:
    GameMap(int width, int height, int map_fill_percentage,
             int tile_width_in_pixels, int tile_height_in_pixels,
             sf::RenderWindow& window);
    void RandomizeMap(int map_fill_percent);
    void PrintMapToConsole();
    bool IsValidCell(int i, int j);
    bool IsOnBoundary(int i, int j);
    int CountNeighborWalls(int i, int j);
    void SmoothMap(int num_iterations);
    void DrawMap(sf::RenderWindow& window, double offset_x, double offset_y);
    void RemoveRegion(int i, int j);
    int Width();
    int Height();
    std::vector<Room *> GenerateRooms();
    void Dfs(int i, int j, std::vector<std::vector<int>>& visited,
                   std::vector<Node *>& connected_component);
    void DfsRoom(Room * room, std::vector<Room *>& rooms, 
        std::vector<Room *>& visited, std::vector<Room *>& connected_component);
    std::vector<std::vector<Room *>> GroupRoomsIntoConnectedComponents(
                                std::vector<Room *>& rooms);
    void ConnectMainRoomToOtherRooms(Room * main_room, std::vector<Room *>& rooms,
                            std::vector<std::vector<Room *>>& rooms_connected_components);
    void CreatePassageways();
    void ProcessMap(sf::RenderWindow& window);
    void ConnectClosestRooms();
    void DrawRoomConnections(sf::RenderWindow& window);
    void Reset();
    void CreateBoundaries();
    void ConnectRooms(std::vector<Room *>& rooms);
    void DfsSimple(int i, int j, std::vector<std::vector<int>>& visited,
                    std::vector<std::pair<int, int>>& connected_component);
    int CountConnectedComponents(std::vector<Room *>& rooms);
    void RemoveConnectedComponents(std::vector<Room *>& rooms);
    std::vector<std::vector<std::pair<int, int>>> GroupTilesIntoConnectedComponenets(
                                                            std::vector<Room *>& rooms);
    int CountNeighborsDist(int i, int j, char c, int dist);
};


#endif // GAME_MAP_H_
