/* date = February 21th 2021 3:48 pm */

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "datapoint.h"
#include "widget.h"

struct Screen {
    const unsigned int window_width;
    const unsigned int window_height;
    
    const float default_widget_width = 160;
    const float default_widget_height = 80;
    const unsigned int default_widget_font_size = 18;
    
    const float ticker_widgets_width = 80;
    const float ticker_widgets_height = 80;
    
    // Logo widget
    TextWidget* logo_widget = nullptr;
    
    // Stock selector widgets
    std::vector<HighlightTextWidget*>* ticker_widgets = nullptr;
    
    // Stock selector scroller widgets
    sf::VertexArray* left_ticker_scroller = nullptr;
    sf::VertexArray* right_ticker_scroller = nullptr;
    
    // Graph type selector widgets
    HighlightTextWidget* line_graph_select = nullptr;
    HighlightTextWidget* candle_graph_select = nullptr;
    HighlightTextWidget* bar_chart_select = nullptr;
    
    // Info widget
    sf::VertexArray* info_widget = nullptr;
    
    std::vector<std::string>* tickers = nullptr;
    std::vector<DataPoint*>* stock_data = nullptr;
    
    Screen(unsigned int win_wid, unsigned int win_hei, std::vector<std::string>* tickers, std::vector<DataPoint*>* stock_data, sf::Font* font);
    
    void draw(sf::RenderWindow* window, float mouse_x, float mouse_y);
};

#endif
