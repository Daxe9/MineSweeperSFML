#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "grid.h"
#include "board_handler.h"
#include "sfml_text.h"

#if 0
#define LOG(x, y) std::cout << x << " " << y << std::endl
#else
#define LOG(x)
#endif


namespace Game {
    void run() {
        // define the window' sizes
        int board_width = 500, board_height = board_width;
        // define the size of the matrix
        int matrix_width = 10, matrix_height = matrix_width;
        // get the ratio of the window and the matrix
        float rect_size = board_width / matrix_width;
        // define outline thickness
        float rectangle_outline_thickness = 2.f;

        // initialize the font for the text
        sf::Font font;
        if(!font.loadFromFile("../media/RobotoSlab-VariableFont_wght.ttf")) {
            throw std::runtime_error("Font not found");
        }

        // initialize board handler in order to play the game
        BoarderHandler board(matrix_width, matrix_height);
        // initialize the matrix of text
        std::vector<std::vector<SFMLText>> grid_text;
        for (size_t i = 0; i < board.matrix.size(); ++i) {
            std::vector<SFMLText> temp;
            for (size_t j = 0; j < board.matrix.at(i).size(); ++j) {
                temp.emplace_back(
                        SFMLText(
                                std::to_string(
                                        board.matrix.at(i).at(j).count),
                                font,
                                matrix_width,
                                i * rect_size + rect_size / 2.f,
                                j * rect_size + rect_size / 2.f));
            }
            grid_text.emplace_back(temp);
        }
        // initialize the vector that contains every spotted cells
        std::vector<std::pair<int, int>> visible_cells;

        // initialize the render with window' sizes and title
        sf::RenderWindow *window = new sf::RenderWindow(
                sf::VideoMode(
                        board_width,
                        board_height),
                "MineSweeper(low budget version)");

        // initialize the texure for background
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


        // main loop
        sf::Event event;
        bool isGameOver = false;
        while (window->isOpen()) {
            // waiting for event
            if (window->waitEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window->close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            // get the position of the selected cell and check if it is a bomb,
                            // if not explore the surrounding cells
                            int x = event.mouseButton.x / rect_size;
                            int y = event.mouseButton.y / rect_size;
                            if (board.matrix
                                .at(x)
                                .at(y).count != -1) {
                                board.controlNeighbours(
                                        x,
                                        y);
                                visible_cells = board.countVisibleCells();
                            } else {
                                isGameOver = true;
                            }

                        }
                        break;
                }
            }




            // clear all the window
            window->clear();
            // draw the background, (not needed)
            window->draw(background);
            // draw the grid
            grid.draw();
            // draw the spotted cells
            for (std::pair<int, int> &coordinates: visible_cells) {
                window->draw(grid_text.at(coordinates.first).at(coordinates.second).text);
            }
            // if the game is over, display text
            if (isGameOver) {
                SFMLText win(
                        "You lost!",
                        font,
                        5,
                        board_width / 2.f,
                        board_height / 2.f);
                win.text.setStyle(sf::Text::Bold);
                win.text.setFillColor(sf::Color::Red);
                window->draw(win.text);
            }
            // if there is no more cells to explore, display text
            if (board.getNeededCellToExplore() == 0) {
                SFMLText win(
                        "You won!",
                        font,
                        5,
                        board_width / 2.f,
                        board_height / 2.f);
                win.text.setStyle(sf::Text::Bold);
                win.text.setFillColor(sf::Color::Red);
                window->draw(win.text);
            }
            // display the window
            window->display();
        }
    }
};

