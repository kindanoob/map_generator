#ifndef ROOM_H_
#define ROOM_H_


#include <vector>
#include <utility>


class GameMap;

class Node {
public:
    Node(int x, int y): x_(x), y_(y) {}
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
    static bool CmpRoomsBySize(Room *room_one, Room *room_two);

    Room(std::vector<Node *>& node_vector, GameMap *game_map);
    void CreateBoundaryNodes(GameMap *game_map);
    Room *GetClosestRoom(std::vector<Room *>& rooms);
    void ConnectRoom(Room *other_room);
    std::vector<Node *> BoundaryNodes();
    int GetSize();
    int CalcDistanceToRoom(Room* other_room);
    std::pair<Node *, Node *> GetClosestNodes(Room *other_room);
};


#endif // ROOM_H_