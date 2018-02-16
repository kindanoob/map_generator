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
    if (!ubuntu_font.loadFromFile("resources/ubuntu.ttf")) {
        std::cout << "Error. Font failed to load." << std::endl;
    }

    sf::RectangleShape controls_rect_shape;
    controls_rect_shape.setSize(sf::Vector2f(125, 100));
    controls_rect_shape.setPosition(sf::Vector2f(100, 400));
    controls_rect_shape.setFillColor(sf::Color(255, 255, 255));

    sf::Text controls_text;
    controls_text.setFont(ubuntu_font);
    controls_text.setCharacterSize(25);
    controls_text.setColor(sf::Color(0, 0, 0));
    std::string controls_string = "Keyboard controls: \nG - generate new map";
    controls_text.setString(controls_string);
    auto controls_text_rect = controls_text.getGlobalBounds();
    controls_text.setOrigin(sf::Vector2f(controls_text_rect.width / 2,
                                                controls_text_rect.height / 2));
    controls_text.setPosition(controls_rect_shape.getPosition() +
                                     sf::Vector2f(controls_rect_shape.getSize().x / 2,
                                                  controls_rect_shape.getSize().y / 2));


    sf::RectangleShape generate_button_rect_shape;
    generate_button_rect_shape.setSize(sf::Vector2f(125, 55));
    generate_button_rect_shape.setPosition(sf::Vector2f(50, 600));
    generate_button_rect_shape.setFillColor(sf::Color(255, 255, 255));

    sf::Text generate_button_text;
    generate_button_text.setFont(ubuntu_font);
    generate_button_text.setCharacterSize(25);
    generate_button_text.setColor(sf::Color(0, 0, 0));
    auto generate_button_text_rect = generate_button_text.getGlobalBounds();
    generate_button_text.setOrigin(sf::Vector2f(generate_button_text_rect.width / 2,
                                                generate_button_text_rect.height / 2));
    generate_button_text.setPosition(generate_button_rect_shape.getPosition() +
                                     sf::Vector2f(generate_button_rect_shape.getSize().x / 2,
                                                  generate_button_rect_shape.getSize().y / 2));


    while (window.isOpen()) {
        generate_button_rect_shape.setFillColor(sf::Color(255, 255, 255));
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::G) {
                    game_map->ProcessMap(window);
                }
            }            
        }

        window.clear(sf::Color(255, 255, 255));


        game_map->DrawMap(window, kOffsetX, kOffsetY);
        window.draw(controls_rect_shape);
        window.draw(controls_text);
        window.draw(generate_button_rect_shape);
        window.draw(generate_button_text);
        window.display();
    }
    return 0;
}
