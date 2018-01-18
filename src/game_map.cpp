#include <vector>
#include <iostream>


#include "game_map.h"
#include "rng.h"
#include "room.h"
#include "util.h"
#include "config.h"



Game_map::Game_map(int width, int height, int map_fill_percentage,
                   int tile_width_in_pixels, int tile_height_in_pixels,
                   sf::RenderWindow& window):
                    width_(width), height_(height),
                    map_fill_percentage_(map_fill_percentage),
                    tile_width_in_pixels_(tile_width_in_pixels),
                    tile_height_in_pixels_(tile_height_in_pixels) {
    char_map_ = std::vector<std::vector<char> >(width, std::vector<char>(height, '1'));
    //print_map_to_console();
    randomize_map(0);
}


void Game_map::reset() {
    char_map_ = std::vector<std::vector<char> >(width(), std::vector<char>(height(), '1'));
}

void Game_map:: print_map_to_console() {
    std::cout << std::endl;
    for (size_t i = 0; i < char_map_.size(); ++i) {
        std::cout << " ";
        for (size_t j = 0; j < char_map_[0].size(); ++j) {
            std::cout << char_map_[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Game_map::randomize_map(int map_fill_percent) {
    for (size_t i = 0; i < char_map_.size(); ++i) {
        for (size_t j = 0; j < char_map_[0].size(); ++j) {
            if ((i == 0) || (j == 0) || (i == char_map_.size() - 1) || (j == char_map_[0].size() - 1)) {
                char_map_[i][j] = '1';
                continue;
            }
            int rand_int = Rng::int_in_range(0, 100);
            if (rand_int < map_fill_percent) {
                char_map_[i][j] = '1';
            } else {
                char_map_[i][j] = '0';
            }
        }
    }
}


bool Game_map::is_valid_cell(int i, int j) {
    return (i >= 0) && (i < height()) && (j >= 0) && (j < width());
}


int Game_map::count_neighbor_walls(int i, int j) {
    int cnt = 0;
    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            if ((dx == 0) && (dy == 0)) {
                continue;
            }
            if (is_valid_cell(i + dy, j + dx) && (char_map_[i + dy][j + dx] == '1')) {
                ++cnt;
            }
        }
    }
    return cnt;
}

void Game_map::smooth_map(int num_iterations) {
    for (int k = 0; k < num_iterations; ++k) {
        for (size_t i = 1; i < char_map_.size() - 1; ++i) {
            for (size_t j = 1; j < char_map_[0].size() - 1; ++j) {
                char curr = char_map_[i][j];
                int cnt = count_neighbor_walls(i, j);
                if (curr == '0') {//if the cell is dead
                    if (std::find(BIRTH_VALUES.begin(), BIRTH_VALUES.end(), cnt) !=
                       BIRTH_VALUES.end()) {
                        char_map_[i][j] = '1';
                    }
                } else {//if the cell is alive
                    if (std::find(SURVIVE_VALUES.begin(), SURVIVE_VALUES.end(), cnt) ==
                            SURVIVE_VALUES.end()) {
                        char_map_[i][j] = '0';
                    }
                }
            }
        }
    }
}


void Game_map::draw_map(sf::RenderWindow& window, double offset_x, double offset_y) {
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(tile_width_in_pixels_, tile_width_in_pixels_));
            rect.setPosition(sf::Vector2f(offset_x + j * tile_width_in_pixels_, offset_y + i * tile_width_in_pixels_));
            if (char_map_[i][j] == '1') {
                rect.setFillColor(sf::Color(0, 0, 0));
            }
            else {
                rect.setFillColor(sf::Color(255, 255, 255));
            }
            window.draw(rect);
        }
    }
}


bool Game_map::is_on_boundary(int i, int j) {
    return (char_map_[i + 1][j] == '1') || (char_map_[i - 1][j] == '1') ||
            (char_map_[i][j - 1] == '1') || (char_map_[i][j + 1] == '1');
}


int Game_map::height() {
    return char_map_.size();
}


int Game_map::width() {
    return char_map_[0].size();
}


std::vector<std::unique_ptr<Room>> Game_map::generate_rooms() {
    std::vector<std::unique_ptr<Room>> rooms;
    std::vector<std::vector<int> > visited(height(), std::vector<int>(width(), 0));
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            if (!visited[i][j] && (char_map_[i][j] == '0')) {
                std::vector<Node *> connected_component;
                dfs(i, j, visited, connected_component);
                std::unique_ptr<Room> new_room(new Room(connected_component, this));
                rooms.push_back(std::move(new_room));
            }
        }
    }
    return rooms;
}


int Game_map::count_connected_componenets(std::vector<std::unique_ptr<Room>>& rooms) {
    int cnt = 0;
    std::vector<std::vector<int> > visited(height(), std::vector<int>(width(), 0));
    std::vector<std::pair<int, int> > connected_component;
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            if (!visited[i][j] && (char_map_[i][j] == '0')) {
                dfs_simple(i, j, visited, connected_component);
                ++cnt;
            }
        }
    }
    return cnt;
}



std::vector<std::vector<std::pair<int, int> > > Game_map::group_tiles_into_connected_componenets(
                                                            std::vector<std::unique_ptr<Room>>& rooms) {
    std::vector<std::vector<std::pair<int, int> > > res;
    std::vector<std::vector<int> > visited(height(), std::vector<int>(width(), 0));
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            if (!visited[i][j] && (char_map_[i][j] == '0')) {
                std::vector<std::pair<int, int> > cc;
                dfs_simple(i, j, visited, cc);
                res.push_back(cc);
            }
        }
    }
    return res;
}


void Game_map::remove_connected_components(std::vector<std::unique_ptr<Room>>& rooms) {
    std::vector<std::vector<std::pair<int, int> > > connected_components =
        group_tiles_into_connected_componenets(rooms);
    std::sort(connected_components.begin(), connected_components.end(),
              Util::cmp_tile_connected_components_by_size_descending);
    for (size_t i = 1; i < connected_components.size(); ++i) {
        for (auto& n: connected_components[i]) {
            char_map_[n.first][n.second] = '1';
        }
    }
}


void Game_map::dfs(int i, int j, std::vector<std::vector<int> >& visited,
                   std::vector<Node *>& connected_component) {
    visited[i][j] = 1;
    Node *new_node = new Node(j, i);
    connected_component.push_back(new_node);
    if ((is_valid_cell(i + 1, j)) && !visited[i + 1][j] && (char_map_[i + 1][j] == '0')) {
        dfs(i + 1, j, visited, connected_component);
    }
    if ((is_valid_cell(i - 1, j)) && !visited[i - 1][j] && (char_map_[i - 1][j] == '0')) {
        dfs(i - 1, j, visited, connected_component);
    }
    if ((is_valid_cell(i, j + 1)) && !visited[i][j + 1] && (char_map_[i][j + 1] == '0')) {
        dfs(i, j + 1, visited, connected_component);
    }
    if ((is_valid_cell(i, j - 1)) && !visited[i][j - 1] && (char_map_[i][j - 1] == '0')) {
        dfs(i, j - 1, visited, connected_component);
    }
}


void Game_map::dfs_simple(int i, int j, std::vector<std::vector<int> >& visited,
                        std::vector<std::pair<int, int> >& connected_component) {
    visited[i][j] = 1;
    connected_component.push_back(std::make_pair(i, j));
    if ((is_valid_cell(i + 1, j)) && !visited[i + 1][j] && (char_map_[i + 1][j] == '0')) {
        dfs_simple(i + 1, j, visited, connected_component);
    }
    if ((is_valid_cell(i - 1, j)) && !visited[i - 1][j] && (char_map_[i - 1][j] == '0')) {
        dfs_simple(i - 1, j, visited, connected_component);
    }
    if ((is_valid_cell(i, j + 1)) && !visited[i][j + 1] && (char_map_[i][j + 1] == '0')) {
        dfs_simple(i, j + 1, visited, connected_component);
    }
    if ((is_valid_cell(i, j - 1)) && !visited[i][j - 1] && (char_map_[i][j - 1] == '0')) {
        dfs_simple(i, j - 1, visited, connected_component);
    }
}


void Game_map::dfs_room(std::unique_ptr<Room>room, std::vector<std::unique_ptr<Room>>& rooms, 
    std::vector<std::unique_ptr<Room>>& visited, std::vector<std::unique_ptr<Room>>& connected_component) {
    if (std::find(visited.begin(), visited.end(), room) != visited.end()) {
        return;
    }
    visited.push_back(std::move(room));
    connected_component.push_back(room);
    for (auto& r: room->connected_rooms_) {
        dfs_room(r, rooms, visited, connected_component);
    }
}


std::vector<std::vector<std::unique_ptr<Room>> > Game_map::group_rooms_into_connected_components(
                                std::vector<std::unique_ptr<Room>>& rooms) {
    std::vector<std::vector<std::unique_ptr<Room>> > res;
    std::vector<std::unique_ptr<Room>> visited;
    for (size_t i = 0; i < rooms.size(); ++i) {
        std::vector<std::unique_ptr<Room>> connected_component;
        dfs_room(rooms[i], rooms, visited, connected_component);
        if (!connected_component.empty()) {
            res.push_back(connected_component);
        }
    }
    return res;
}


void Game_map::connect_main_room_to_other_rooms(std::unique_ptr<Room>main_room, std::vector<std::unique_ptr<Room>>& rooms,
                                      std::vector<std::vector<std::unique_ptr<Room>> >& rooms_connected_components) {
    for (auto& v: rooms_connected_components) {
        if (std::find(v.begin(), v.end(), main_room) == v.end()) {
            main_room->connect_room(main_room->get_closest_room(v));
        }
    }
}



void Game_map::create_passageways() {
    std::vector<std::vector<std::unique_ptr<Room>> > rooms_connected_components =
        group_rooms_into_connected_components(room_vector_);
    double offset_x = kOffsetX;
    double offset_y = kOffsetY;
    for (size_t i = 0; i < room_vector_.size(); ++i) {
        for (auto& r: room_vector_[i]->connected_rooms_) {
            if (room_vector_[i] == r) {
                continue;
            }
            std::pair<Node *, Node *> closest_nodes =
                room_vector_[i]->get_closest_nodes(r);
            double x0 = closest_nodes.first->x_;
            double y0 = closest_nodes.first->y_;
            x0 *= tile_width_in_pixels_;
            y0 *= tile_width_in_pixels_;
            x0 += offset_x;
            y0 += offset_y;
            double x1 = closest_nodes.second->x_;
            double y1 = closest_nodes.second->y_;
            x1 *= tile_width_in_pixels_;
            y1 *= tile_width_in_pixels_;
            x1 += offset_x;
            y1 += offset_y;
            double a = 0;
            double b = 0;
            double c = 0;
            if (fabs(x0 - x1) < kEpsilon) {//if the line is vertical, e.g. x = x0
                a = 1;
                b = 0;
                c = -x0;
            } else if (fabs(y0 - y1) < kEpsilon) {//if the line is vertical, e.g. x = x0
                a = 0;
                b = 1;
                c = -y0;
            } else {
                a = (y0 - y1) / (x0 - x1);
                b = 1;
                c = y0 - a * x0;
                a *= -1;
                c *= -1;
            }
            int cnt = 0;
            for (int i = 0; i < height(); ++i) {
                for (int j = 0; j < width(); ++j) {                    
                    double x = j * tile_width_in_pixels_ + tile_width_in_pixels_ / 2 + offset_x;
                    double y = i * tile_width_in_pixels_ + tile_width_in_pixels_ / 2 + offset_y;
                    double dist = Util::dist_from_point_to_line(x, y, a, b, c);
                    if (dist < tile_width_in_pixels_ * kSqrt2) {
                        double dist_to_first_end = Util::dist_squared_from_point_to_point(x, y, x0, y0);
                        double dist_to_second_end = Util::dist_squared_from_point_to_point(x, y, x1, y1);
                        double dist_first_to_second = Util::dist_squared_from_point_to_point(x0, y0, x1, y1);
                        if ((dist_to_first_end <= dist_first_to_second) &&
                           (dist_to_second_end <= dist_first_to_second)) {
                            char_map_[i][j] = '0';
                            ++cnt;
                        }
                    }
                }
            }
        }
    }
}


void Game_map::connect_closest_rooms() {
    if (room_vector_.empty()) {
        std::cout << "Error. Cannot connect rooms, because room list is empty." << std::endl;
        return;
    }
    if (room_vector_.size() == 1) {
        std::cout << "Error. Cannot connect rooms, because room list contains "
        << "only one room" << std::endl;
        return;
    }
    for (size_t i = 0; i < room_vector_.size(); ++i) {
        room_vector_[i]->connect_room(room_vector_[i]->get_closest_room(room_vector_));
    }
}


void Game_map::connect_rooms(std::vector<std::unique_ptr<Room>>& rooms) {
    connect_closest_rooms();
    sort(room_vector_.begin(), room_vector_.end(), Room::cmp_rooms_by_size);
    if (!room_vector_.empty()) {
        room_vector_[0]->is_main_room_ = true;
    }
    std::vector<std::vector<std::unique_ptr<Room>> > rooms_connected_components =
        group_rooms_into_connected_components(room_vector_);
    if (!room_vector_.empty()) {
        connect_main_room_to_other_rooms(room_vector_[0], room_vector_, rooms_connected_components);
    }
    rooms_connected_components =
        group_rooms_into_connected_components(room_vector_);    
}

void Game_map::process_map(sf::RenderWindow& window) {
    randomize_map(map_fill_percentage_);
    smooth_map(kNumIterationsSmooth);
    room_vector_ = generate_rooms();    
    connect_rooms(room_vector_);

    //draw_room_connections(window);
    smooth_map(kNumIterationsSmooth);
    create_passageways();
    remove_connected_components(room_vector_);
}


void Game_map::draw_room_connections(sf::RenderWindow& window) {
    for (size_t i = 0; i < room_vector_.size(); ++i) {
        std::unique_ptr<Room>curr = room_vector_[i];
        for (auto& r: curr->connected_rooms_) {
            if (curr == r) {
                continue;
            }
            sf::VertexArray line(sf::LinesStrip, 2);
            int rand_index_0 = 0;
            int rand_index_1 = 0;
            line[0].position = sf::Vector2f(curr->node_vector_[rand_index_0]->x_ * kTileWidthInPixels + kOffsetX, curr->node_vector_[rand_index_0]->y_ * kTileWidthInPixels + kOffsetY);
            line[1].position = sf::Vector2f(r->node_vector_[rand_index_1]->x_ * kTileWidthInPixels + kOffsetX, r->node_vector_[rand_index_1]->y_ * kTileWidthInPixels + kOffsetY);
            line[0].color = sf::Color(255, 0, 0);
            line[1].color = sf::Color(255, 0, 0);
            window.draw(line);
        }
    }
}


void Game_map::create_boundaries() {
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            if ((i == 0) || (i == height() - 1) || (j == 0) || (j == width() - 1)) {
                char_map_[i][j] = '1';
            }
        }
    }
}


int Game_map::count_neighbors_dist(int i, int j, char c, int dist) {
    int cnt = 0;
    for (int dx = -dist; dx < dist + 1; ++dx) {
        for (int dy = -dist; dy < dist + 1; ++dy) {
            if ((dx == 0) && (dy == 0)) {
                continue;
            }
            if (is_valid_cell(i + dy, j + dx) && (char_map_[i + dy][j + dx] == c)) {
                ++cnt;
            }
        }
    }
    return cnt;
}
