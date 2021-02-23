#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>

struct Widget {
    float x, y, width, height;
    sf::VertexArray* vertices = nullptr;
    sf::Color color;
    
    Widget(float x, float y, float width, float height, sf::Color col);
    
    virtual void move(float dx, float dy);
    virtual void draw(sf::RenderWindow* window, float mouse_x, float mouse_y);
};

struct HighlightWidget : public Widget {
    sf::Color alt_color;
    
    HighlightWidget(float x, float y, float width, float height, sf::Color col, sf::Color alt);
    
    void draw(sf::RenderWindow* window, float mouse_x, float mouse_y) override;
};

struct TextWidget : public Widget {
    sf::Text text;
    sf::Color text_color;
    unsigned int font_size;
    unsigned int nchars;
    
    TextWidget(float x, float y, float width, float height, sf::Color col, const std::string& text, sf::Color txt_col, sf::Font* font, unsigned int font_size);
    
    void draw(sf::RenderWindow* window, float mouse_x, float mouse_y) override;
    void move(float dx, float dy);
    void set_position(float x, float y);
};

struct HighlightTextWidget : public TextWidget {
    sf::Color alt_color;
    
    HighlightTextWidget(float x, float y, float width, float height, sf::Color col, sf::Color alt_clr, const std::string& text, sf::Color txt_col, sf::Font* font, unsigned int font_size);
    
    void draw(sf::RenderWindow* window, float mouse_x, float mouse_y) override;
};

#endif