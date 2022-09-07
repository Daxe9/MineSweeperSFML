
class SFMLText : public sf::Text {
public:
    sf::Text text;
public:
    SFMLText(const sf::String &title,  const sf::Font &font , const float x, const float y) {
        // load the font
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        // the order: setString, setOrigin, setPosition, is important to make it work
        text.setString(title);
        text.setOrigin(
                text.getLocalBounds().width / 2.0f,
                text.getLocalBounds().height / 2.0f);
        text.setPosition(x, y);
    }

    void reset_title(int num) {
        text.setString(std::to_string(num));
    }

    void reset_position(const float x, const float y) {
        text.setPosition(x, y);
    }
};

