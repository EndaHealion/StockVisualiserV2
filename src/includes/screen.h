/* date = February 21th 2021 3:48 pm */

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "datapoint.h"
#include "widget.h"

#define DEFAULT_WIDGET_WIDTH 160
#define DEFAULT_WIDGET_HEIGHT 80
#define DEFAULT_WIDGET_FONT_SIZE 18

#define TICKER_WIDGETS_WIDTH 80
#define TICKER_WIDGETS_HEIGHT 80
#define TICKER_WIDGETS_FONT_SIZE 24
#define TICKER_WIDGETS_DEFAULT_COLOR sf::Color::White
#define TICKER_WIDGETS_HIGHLIGHT_COLOR sf::Color(200,200,200)
#define TICKER_WIDGETS_SCROLLER_WIDTH 40

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

struct TickerWidgets {
    float x, y;
    std::vector<std::string>* tickers = nullptr;
    sf::Color default_color;
    sf::Color selected_color;
    
    // Stock selector scroller widgets
    HighlightWidget* left_ticker_scroller = nullptr;
    HighlightWidget* right_ticker_scroller = nullptr;
    
    std::vector<HighlightTextWidget*>* ticker_widgets = nullptr;
    std::vector<bool>* is_selected = nullptr;
    std::vector<bool>* should_draw = nullptr;
    
    TickerWidgets(float window_width, float window_height, float x, float y, std::vector<std::string>* tickers, sf::Font* font);
    
    void select_ticker(float mouse_x, float mouse_y);
    void scroll_tickers_left();
    void scroll_tickers_right();
    void draw(sf::RenderWindow* window, float mouse_x, float mouse_y);
    void update_should_draw();
};

struct Screen {
    const unsigned int window_width;
    const unsigned int window_height;
    
    const float default_widget_width = 160;
    const float default_widget_height = 80;
    const unsigned int default_widget_font_size = 18;
    
    const float ticker_widgets_width = 80;
    const float ticker_widgets_height = 80;
    
    std::vector<std::string>* tickers = nullptr;
    std::vector<DataPoint*>* stock_data = nullptr;
    
    // Logo widget
    TextWidget* logo_widget = nullptr;
    
    // Stock selector widgets
    TickerWidgets* ticker_widgets = nullptr;
    
    // Graph type selector widgets
    HighlightTextWidget* line_graph_select = nullptr;
    HighlightTextWidget* candle_graph_select = nullptr;
    HighlightTextWidget* bar_chart_select = nullptr;
    
    // Info widget
    sf::VertexArray* info_widget = nullptr;
    
    Screen(unsigned int win_wid, unsigned int win_hei, std::vector<std::string>* tickers, std::vector<DataPoint*>* stock_data, sf::Font* font);
    
    void draw(sf::RenderWindow* window, float mouse_x, float mouse_y);
};

#endif
