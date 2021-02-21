
#include "includes/widget.h"

Widget::Widget(float x, float y, float width, float height, sf::Color col) : color{col} {
    vertices = new sf::VertexArray(sf::PrimitiveType::Quads, 4);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    (*vertices)[0] = sf::Vertex(sf::Vector2f(x, y), col);
    (*vertices)[1] = sf::Vertex(sf::Vector2f(x+width, y), col);
    (*vertices)[2] = sf::Vertex(sf::Vector2f(x+width, y+height), col);
    (*vertices)[3] = sf::Vertex(sf::Vector2f(x, y+height), col);
}

void Widget::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    window->draw(*vertices);
}


HighlightWidget::HighlightWidget(float x, float y, float width, float height, sf::Color col, sf::Color alt) : Widget(x, y, width, height, col), alt_color{alt} {
    
}

void HighlightWidget::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    const bool is_hovering = mouse_x >= x && mouse_x <= x+width && mouse_y >= y && mouse_y <= y+height;
    if (is_hovering) {
        (*vertices)[0].color = alt_color;
        (*vertices)[1].color = alt_color;
        (*vertices)[2].color = alt_color;
        (*vertices)[3].color = alt_color;
    }
    window->draw(*vertices);
    
    // reset colors to non hovering colors
    (*vertices)[0].color = color;
    (*vertices)[1].color = color;
    (*vertices)[2].color = color;
    (*vertices)[3].color = color;
}

TextWidget::TextWidget(float x, float y, float width, float height, sf::Color col, const std::string& text, sf::Color txt_col, sf::Font* font, unsigned int font_size) :
Widget(x, y, width, height, col)
{
    this->text = {text, *font, font_size};
    const float offset_to_center_text = (float)-0.5f*font_size*text.size(); 
    // NOTE(Enda): The "centerX" value is meaningless and has no logic to it. I just put in and adjusted values until it looked good enough. Fix later if it gets unusable...
    const float centerX = x + (offset_to_center_text + width - font_size)*0.5f;
    const float centerY = y + ( (height-font_size) * 0.5f) ;
    
    this->text.setPosition(sf::Vector2f(centerX, centerY));
    this->text.setFillColor(txt_col);
    
}

void TextWidget::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    window->draw(*vertices);
    window->draw(text);
}

HighlightTextWidget::HighlightTextWidget(float x, float y, float width, float height, sf::Color col, sf::Color alt_clr, const std::string& text, sf::Color txt_col, sf::Font* font, unsigned int font_size) : TextWidget(x, y, width, height, col, text, txt_col, font, font_size)
{
    this->alt_color = alt_clr; 
}

void HighlightTextWidget::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    const bool is_hovering = mouse_x >= x && mouse_x <= x+width && mouse_y >= y && mouse_y <= y+height;
    if (is_hovering) {
        (*vertices)[0].color = alt_color;
        (*vertices)[1].color = alt_color;
        (*vertices)[2].color = alt_color;
        (*vertices)[3].color = alt_color;
    }
    window->draw(*vertices);
    window->draw(text);
    // reset colors to non hovering colors
    (*vertices)[0].color = color;
    (*vertices)[1].color = color;
    (*vertices)[2].color = color;
    (*vertices)[3].color = color;
}
