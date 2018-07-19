#include <iostream>
#include <SFML/Graphics.hpp>
#include "game_map.h"
#include "config.h"
#include "room.h"
#include "util.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight), "Map generator");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    GameMap *game_map = new GameMap(kMapWidthInTiles, kMapHeightInTiles,
                                      kMapFillPercentage, kTileWidthInPixels,
                                      kTileHeightInPixels, window);

    sf::Font ubuntu_font;
    if (!ubuntu_font.loadFromFile("resources/fonts/ubuntu.ttf")) {
        std::cout << "Error. Font failed to load." << std::endl;
        return 1;
    }


    sf::RectangleShape controls_rect_shape;
    controls_rect_shape.setSize(sf::Vector2f(125, 100));
    controls_rect_shape.setPosition(sf::Vector2f(100, 400));
    controls_rect_shape.setFillColor(sf::Color::Black);

    sf::Text controls_text;
    controls_text.setFont(ubuntu_font);
    controls_text.setCharacterSize(kControlsTextSize);
    controls_text.setOutlineColor(sf::Color::Black);
    controls_text.setFillColor(sf::Color::Black);
    std::string controls_string = "Keyboard controls: \nG - generate new map";
    controls_text.setString(controls_string);
    auto controls_text_rect = controls_text.getGlobalBounds();
    controls_text.setOrigin(sf::Vector2f(controls_text_rect.width / 2,
                                                controls_text_rect.height / 2));
    controls_text.setPosition(controls_rect_shape.getPosition() +
                                     sf::Vector2f(controls_rect_shape.getSize().x / 2,
                                                  controls_rect_shape.getSize().y / 2));


    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (e.key.code == sf::Keyboard::G) {
                    game_map->ProcessMap(window);
                }
            }
        }
        window.clear(sf::Color::White);

        window.draw(controls_text);
        game_map->DrawMap(window, kOffsetX, kOffsetY);
        window.display();
    }
    return 0;
}
