#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "grid.h"
#include "board_handler.h"
#include "sfml_text.h"

#if 1
#define LOG(x, y) std::cout << x << " " << y << std::endl
#else
#define LOG(x)
#endif


namespace App {






    void run() {
        int board_width = 500, board_height = 500;
        int matrix_width = 10, matrix_height = matrix_width;
        float rectangle_outline_thickness = 2.f;

        std::vector<std::vector<Single_Cell>> matrix = createMatrix(matrix_width, matrix_height);
        sf::RenderWindow *window = new sf::RenderWindow(
                sf::VideoMode(
                        board_width,
                        board_height),"MineSweeper(low budget version)");

        sf::Texture texture;
        // cannot load the background, exit
        if (!texture.loadFromFile("../media/background.png")) return;
        sf::Sprite background;
        background.setTexture(texture);

        // create a grid for cells
        Grid grid(window, matrix_width, matrix_height);
        // give the grey color to the cells in the grid
        grid.init_rect_color(sf::Color(19, 19, 19));
        // give cell' sizes base on ratio of the width and height of the board and matrix
        grid.init_rect_size(
                sf::Vector2f(
                        (float) board_width / (float) matrix_width,
                        (float) board_height / (float) matrix_height));
        // give outline thickness
        grid.init_rect_outline(rectangle_outline_thickness);
        // give outline color
        grid.init_rect_outline_color(sf::Color(192, 192, 192), sf::Color(0, 0, 0));

        int random_x = 3, random_y = 3;
        int rect_size = 50;

//        sf::Font font;
//        if(!font.loadFromFile("../media/RobotoSlab-VariableFont_wght.ttf")) return;
//        sf::Text text;
//
//        text.setFont(font);
//        text.setCharacterSize(24);
//        text.setFillColor(sf::Color::Black);
//
//
//        text.setString("1");
//        text.setOrigin(text.getLocalBounds().width/2.0f,text.getLocalBounds().height/2.0f);
////        text.setPosition(board_width / 2.f,board_height / 2.f);
//        text.setPosition(random_x * rect_size + rect_size / 2.f, random_y * rect_size + rect_size / 2.f);

        sf::Font font;
        // "../media/RobotoSlab-VariableFont_wght.ttf"
        if(!font.loadFromFile("../media/RobotoSlab-VariableFont_wght.ttf")) {
            throw std::runtime_error("Font not found");
        }

        SFMLText testText = SFMLText(
                "7",
                font,
                random_x * rect_size + rect_size / 2.f,
                random_y * rect_size + rect_size / 2.f);
        sf::Event event;
        while (window->isOpen()) {
            // waiting for event
            if (window->waitEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window->close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector3i positions = grid.detect_cell(event.mouseButton.x, event.mouseButton.y);
                            testText.reset_position(
                                    positions.x * positions.z + positions.z / 2.f,
                                    positions.y * positions.z + positions.z / 2.f);
                        }
                        break;
                    default:
                        LOG("Event not handled", 0);

                }
            }

            // clear all the window
            window->clear();

            window->draw(background);

            // draw the grid
            grid.draw();
            LOG(5,5);
            // draw the text
            window->draw(testText.text);
            LOG(6,6);
            // display the window
            window->display();
        }
    }
};

