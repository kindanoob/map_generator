#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <vector>
#include <SFML/Graphics.hpp>


class Room;
class Node;

class Game_map {
public:
    std::vector<std::vector<char> > char_map_;
    int width_ = 0;
    int height_ = 0;
    int map_fill_percentage_ = 0;
    int tile_width_in_pixels_ = 0;
    int tile_height_in_pixels_ = 0;
    std::vector<Room *> room_vector_;
public:
    Game_map(int width, int height, int map_fill_percentage,
             int tile_width_in_pixels, int tile_height_in_pixels,
             sf::RenderWindow& window);
    void randomize_map(int map_fill_percent);
    void print_map_to_console();
    bool is_valid_cell(int i, int j);
    bool is_on_boundary(int i, int j);
    int count_neighbor_walls(int i, int j);
    void smooth_map(int num_iterations);
    void draw_map(sf::RenderWindow& window, double offset_x, double offset_y);
    void remove_region(int i, int j);
    int width();
    int height();
    std::vector<Room *> generate_rooms();
    void dfs(int i, int j, std::vector<std::vector<int> >& visited,
                   std::vector<Node *>& connected_component);
    void dfs_room(Room *room, std::vector<Room *>& rooms, std::vector<Room *>& visited,
              std::vector<Room *>& connected_component);
    std::vector<std::vector<Room *> > group_rooms_into_connected_components(
                                std::vector<Room *>& rooms);
    void connect_main_room_to_other_rooms(Room *main_room, std::vector<Room *>& rooms,
                            std::vector<std::vector<Room *> >& rooms_connected_components);
    void create_passageways();
    void process_map(sf::RenderWindow& window);
    void connect_closest_rooms();
    void draw_room_connections(sf::RenderWindow& window);
    void reset();
    void create_boundaries();
    void connect_rooms(std::vector<Room *>& rooms);
    void dfs_simple(int i, int j, std::vector<std::vector<int> >& visited,
                    std::vector<std::pair<int, int> >& connected_component);
    int count_connected_componenets(std::vector<Room *>& rooms);
    void remove_connected_components(std::vector<Room *>& rooms);
    std::vector<std::vector<std::pair<int, int> > > group_tiles_into_connected_componenets(
                                                            std::vector<Room *>& rooms);
    int count_neighbors_dist(int i, int j, char c, int dist);
    void process_map2();
};


#endif // GAME_MAP_H_
