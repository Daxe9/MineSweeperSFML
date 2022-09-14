#include <SFML/Graphics.hpp>

class Grid {
private:
    sf::RectangleShape rect;
    sf::RenderWindow *window;
    sf::Vector2f rect_size = sf::Vector2f(0.f, 0.f);
    int width = 0, height = 0;
    float outline_thickness = 0.f;
public:
    /**
     * @brief Construct a new Grid object
     *
     * @param window
     * @param rect_size
     * @param width
     * @param height
     * @param outline_thickness
     */
    Grid(sf::RenderWindow *window, int width, int height) : window(window) {
        this->width = width;
        this->height = height;
    };
    /**
     * @brief initialize rect_size
     *
     * @param size set sizes of
     */
    void init_rect_size(const sf::Vector2f size) {
        rect_size = size;
        rect.setSize(rect_size);
    }

    /**
     * @brief initialize rect color
     *
     * @param color
     */
    void init_rect_color(const sf::Color color) {
        rect.setFillColor(color);
    }

    /**
     * @brief initialize outline thickness
     *
     * @param outline_size
     */
    void init_rect_outline(const float outline_size) {
        outline_thickness = outline_size;
        rect.setOutlineThickness(outline_size);
        float rect_offset = outline_size * 2.f;
        sf::Vector2f temp = sf::Vector2f(rect_size.x - rect_offset, rect_size.y - rect_offset);
        rect.setSize(temp);
    }

    /**
     * @brief initialize outline color
     *
     * @param color
     */
    void init_rect_outline_color(const sf::Color background, const sf::Color border) {
        rect.setOutlineColor(border);
        rect.setFillColor(background);
    }

    /**
     * @brief draw the grid
     */
    void draw() {
        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned j = 0; j < height; ++j) {
                rect.setPosition(i * (rect_size.x) + outline_thickness,
                                 j * (rect_size.y) + outline_thickness);
                window->draw(rect);
            }
        }
    }
};