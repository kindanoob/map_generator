#include <iostream>
#include "room.h"
#include "game_map.h"
#include "config.h"
#include "util.h"

bool Room::CmpRoomsBySize(Room *room_one, Room *room_two) {
    return room_one->GetSize() > room_two->GetSize();
}


Room::Room(std::vector<Node *>& node_vector, GameMap *game_map) : node_vector_(node_vector) {
    CreateBoundaryNodes(game_map);
};


void Room::CreateBoundaryNodes(GameMap *game_map) {
    for (auto& n: node_vector_) {
        if (game_map->IsOnBoundary(n->y_, n->x_)) {
            boundary_nodes_.push_back(n);
        }
    }
}


//this function returns the pair of two nodes (one from the caller room, another -
//from the other_room room) which is the pair with smallest distance between the nodes
std::pair<Node *, Node *> Room::GetClosestNodes(Room *other_room) {
    Node *this_node = nullptr;
    Node *other_node = nullptr;
    int min_dist = 2000000000;
    for (auto& curr_node: BoundaryNodes()) {
        for (auto& curr_other_node: other_room->BoundaryNodes()) {
            double curr_dist = Util::DistSquaredFromPointToPoint(curr_node->x_, curr_node->y_,
                                            curr_other_node->x_, curr_other_node->y_);
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                this_node = curr_node;
                other_node = curr_other_node;
            }
        }
    }
    std::pair<Node *, Node *> res(this_node, other_node);
    return res;
}


int Room::CalcDistanceToRoom(Room* other_room) {
    int min_dist = kMapWidthInTiles * kMapWidthInTiles + kMapHeightInTiles * kMapHeightInTiles;
    for (auto& node: BoundaryNodes()) {
        for (auto& other_node: other_room->BoundaryNodes()) {
            int dx = node->x_ - other_node->x_;
            int dy = node->y_ - other_node->y_;
            int curr_dist = dx * dx + dy * dy;
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
            }
        }
    }
    return min_dist;
}


Room *Room::GetClosestRoom(std::vector<Room *>& rooms) {
    Room *min_dist_room = nullptr;
    int min_dist = -1;
    if (this == rooms[0]) {
        min_dist = CalcDistanceToRoom(rooms[1]);
        min_dist_room = rooms[1];
    } else {
        min_dist = CalcDistanceToRoom(rooms[0]);
        min_dist_room = rooms[0];
    }
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i] == this) {
            continue;
        }
        int curr_dist = CalcDistanceToRoom(rooms[i]);
        if (curr_dist < min_dist) {
            min_dist_room = rooms[i];
            min_dist = curr_dist;
        }
    }
    return min_dist_room;
}

void Room::ConnectRoom(Room *other_room) {
    connected_rooms_.push_back(other_room);
    other_room->connected_rooms_.push_back(this);
}

std::vector<Node *> Room::BoundaryNodes() {
    return boundary_nodes_;
}

int Room::GetSize() {
    return node_vector_.size();
}
