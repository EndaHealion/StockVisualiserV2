
#include "includes/screen.h"

Screen::Screen(unsigned int win_wid, unsigned int win_hei, std::vector<std::string>* tickers, std::vector<DataPoint*>* stock_data, sf::Font* font) : window_width(win_wid), window_height(win_hei) {
    this->tickers = tickers;
    this->stock_data = stock_data;
    
    const unsigned int tickers_size = tickers->size();
    const unsigned int stock_data_size = stock_data->size();
    // Generate logo widget
     this->logo_widget = new TextWidget(0,0, default_widget_width,default_widget_height, sf::Color::Red, "Visu Stocks!", sf::Color::White, font, default_widget_font_size);
    
    // stock selector widgets
    ticker_widgets = new std::vector<HighlightTextWidget*>();
    ticker_widgets->resize(tickers_size);
    for (unsigned int i=0; i<tickers_size; i++) {
        const float x_pos = default_widget_width + i*ticker_widgets_width;
        (*ticker_widgets)[i] = new HighlightTextWidget(x_pos,0, ticker_widgets_width,ticker_widgets_height, sf::Color::White, sf::Color(200,200,200), (*tickers)[i], sf::Color::Black, font, default_widget_font_size);
    }
    
    // Graph type widgets
    this->line_graph_select = new HighlightTextWidget(0,default_widget_height, default_widget_width, default_widget_height, sf::Color::White, sf::Color(200,200,200), "Line Graph", sf::Color::Black, font, default_widget_font_size);
    this->candle_graph_select = new HighlightTextWidget(0,2*default_widget_height, default_widget_width, default_widget_height, sf::Color::White, sf::Color(200,200,200), "Candle Graph", sf::Color::Black, font, default_widget_font_size);
    this->bar_chart_select = new HighlightTextWidget(0,3*default_widget_height, default_widget_width, default_widget_height, sf::Color::White, sf::Color(200,200,200), "Bar Chart", sf::Color::Black, font, default_widget_font_size);
    
}

void Screen::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    const unsigned int tickers_size = tickers->size();
    
    logo_widget->draw(window, mouse_x, mouse_y);
    
    for (unsigned int i=0; i<tickers_size; i++) {
        (*ticker_widgets)[i]->draw(window, mouse_x, mouse_y);
    }
    
    line_graph_select->draw(window, mouse_x, mouse_y);
    candle_graph_select->draw(window, mouse_x, mouse_y);
    bar_chart_select->draw(window, mouse_x, mouse_y);
}

