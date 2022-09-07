#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "grid.h"
#include "board_handler.h"
#include "sfml_text.h"

#if 1
#define LOG(x, y) std::cout << x << " " << y << std::endl
#else
#define LOG(x)
#endif


namespace Game {
    void run() {
        int board_width = 500, board_height = board_width;
        int matrix_width = 10, matrix_height = matrix_width;
        float rect_size = board_width / matrix_width;

        float rectangle_outline_thickness = 2.f;

        // initialize the font for the text
        sf::Font font;
        if(!font.loadFromFile("../media/RobotoSlab-VariableFont_wght.ttf")) {
            throw std::runtime_error("Font not found");
        }

        // initialize board handler in order to play the game
        BoarderHandler board(matrix_width, matrix_height);
        std::vector<std::vector<SFMLText>> grid_text;
        std::vector<std::pair<int, int>> visible_cells;
        for (size_t i = 0; i < board.matrix.size(); ++i) {
            std::vector<SFMLText> temp;
            for (size_t j = 0; j < board.matrix.at(i).size(); ++j) {
                temp.emplace_back(
                        SFMLText(
                                std::to_string(
                                        board.matrix.at(i).at(j).count),
                                font,
                                i * rect_size + rect_size / 2.f,
                                j * rect_size + rect_size / 2.f));
            }
            grid_text.emplace_back(temp);
        }

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
                            board.controlNeighbours(event.mouseButton.x / rect_size, event.mouseButton.y / rect_size);
                            visible_cells = board.countVisibleCells();
                        }
                        break;
                }
            }

            // clear all the window
            window->clear();

            window->draw(background);

            // draw the grid
            grid.draw();

            // draw the text
            for (std::pair<int, int> &coordinates: visible_cells) {
                window->draw(grid_text.at(coordinates.first).at(coordinates.second).text);
            }

            // display the window
            window->display();
        }
    }
};

