#include <SFML/Graphics.hpp>

class Grid {
private:
    sf::RectangleShape rect;
    sf::RenderWindow *window;
    sf::Vector2f rect_size = sf::Vector2f(0.f, 0.f);
    int width = 0, height = 0;
    float outline_thickness = 0.f;
public:
    Grid(sf::RenderWindow *window, int width, int height) : window(window) {
        this->width = width;
        this->height = height;
    };

    void init_rect_size(const sf::Vector2f size) {
        rect_size = size;
        rect.setSize(rect_size);
    }

    void init_rect_color(const sf::Color color) {
        rect.setFillColor(color);
    }

    void init_rect_outline(const float outline_size) {
        outline_thickness = outline_size;
        rect.setOutlineThickness(outline_size);
        float rect_offset = outline_size * 2.f;
        sf::Vector2f temp = sf::Vector2f(rect_size.x - rect_offset, rect_size.y - rect_offset);
        rect.setSize(temp);
    }

    void init_rect_outline_color(const sf::Color background, const sf::Color border) {
        rect.setOutlineColor(border);
        rect.setFillColor(background);
    }

    void draw() {
        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned j = 0; j < height; ++j) {
                rect.setPosition(i * (rect_size.x) + outline_thickness,
                                 j * (rect_size.y) + outline_thickness);
                window->draw(rect);
            }
        }
    }

    sf::Vector3i detect_cell(const int x, const int y)  {
        int cell_x_position = x / rect_size.x;
        int cell_y_position = y / rect_size.y;
//        LOG("x: " << cell_x_position, " y: " << cell_y_position);
        return {cell_x_position, cell_y_position, (int) rect_size.x};
    }
};