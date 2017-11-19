#ifndef ROOM_H
#define ROOM_H


#include <vector>
#include <utility>


class Game_map;

class Node {
public:
    Node(int x, int y): x_(x), y_(y){}
    int x_;
    int y_;
};

class Room {
public:
    std::vector<Node *> node_vector_;
    std::vector<Node *> boundary_nodes_;
    std::vector<Room *> connected_rooms_;
    bool is_main_room_ = false;
    bool is_connected_to_main_room_ = false;
public:
    static bool cmp_rooms_by_size(Room *room_one, Room *room_two);

    Room(std::vector<Node *>& node_vector, Game_map *game_map);
    void create_boundary_nodes(Game_map *game_map);
    Room *get_closest_room(std::vector<Room *>& rooms);
    void connect_room(Room *other_room);
    std::vector<Node *> boundary_nodes();
    int get_size();
    int calc_distance_to_room(Room* other_room);
    std::pair<Node *, Node *> get_closest_nodes(Room *other_room);
};


#endif // ROOM_H
