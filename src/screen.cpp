
#include "includes/screen.h"

Screen::Screen(unsigned int win_wid, unsigned int win_hei, std::vector<std::string>* tickers, std::vector<DataPoint*>* stock_data, sf::Font* font) : window_width(win_wid), window_height(win_hei) {
    this->tickers = tickers;
    this->stock_data = stock_data;
    
    const unsigned int tickers_size = tickers->size();
    const unsigned int stock_data_size = stock_data->size();
    
    ticker_widgets = new TickerWidgets(win_wid,win_hei, DEFAULT_WIDGET_WIDTH,0, tickers, font);
    
    // Generate logo widget
     this->logo_widget = new TextWidget(0,0, DEFAULT_WIDGET_WIDTH,DEFAULT_WIDGET_HEIGHT, sf::Color::Red, "VisuStocks!", sf::Color::White, font, DEFAULT_WIDGET_FONT_SIZE);
    
    // Graph type widgets
    this->line_graph_select = new HighlightTextWidget(0,DEFAULT_WIDGET_HEIGHT, DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT, sf::Color::White, sf::Color(200,200,200), "Line Graph", sf::Color::Black, font, DEFAULT_WIDGET_FONT_SIZE);
    this->candle_graph_select = new HighlightTextWidget(0,2*DEFAULT_WIDGET_HEIGHT, DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT, sf::Color::White, sf::Color(200,200,200), "Candle Graph", sf::Color::Black, font, DEFAULT_WIDGET_FONT_SIZE);
    this->bar_chart_select = new HighlightTextWidget(0,3*DEFAULT_WIDGET_HEIGHT, DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT, sf::Color::White, sf::Color(200,200,200), "Bar Chart", sf::Color::Black, font, DEFAULT_WIDGET_FONT_SIZE);
    
}

void Screen::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    const unsigned int tickers_size = tickers->size();
    
    logo_widget->draw(window, mouse_x, mouse_y);
    ticker_widgets->draw(window, mouse_x, mouse_y);
    
    line_graph_select->draw(window, mouse_x, mouse_y);
    candle_graph_select->draw(window, mouse_x, mouse_y);
    bar_chart_select->draw(window, mouse_x, mouse_y);
}

TickerWidgets::TickerWidgets(float window_width, float window_height, float x, float y, std::vector<std::string>* tickers, sf::Font* font) : x(x), y(y), tickers(tickers), ticker_widgets(ticker_widgets) {
    const unsigned int tickers_size = tickers->size();
    
    is_selected = new std::vector<bool>();
    is_selected->resize(tickers_size);
    for (unsigned int i=0; i<tickers_size; i++) (*is_selected)[i] = false;
    
    should_draw = new std::vector<bool>();
    should_draw->resize(tickers_size);
    
    left_ticker_scroller = new HighlightWidget(DEFAULT_WIDGET_WIDTH,0, TICKER_WIDGETS_SCROLLER_WIDTH,TICKER_WIDGETS_HEIGHT, sf::Color::Green, sf::Color::Red);
    right_ticker_scroller = new HighlightWidget(window_width-TICKER_WIDGETS_SCROLLER_WIDTH,0, TICKER_WIDGETS_SCROLLER_WIDTH,TICKER_WIDGETS_HEIGHT, sf::Color::Green, sf::Color::Red);
    
    // stock selector widgets
    ticker_widgets = new std::vector<HighlightTextWidget*>();
    ticker_widgets->resize(tickers_size);
    for (unsigned int i=0; i<tickers_size; i++) {
        const float x_pos = (DEFAULT_WIDGET_WIDTH + TICKER_WIDGETS_SCROLLER_WIDTH) + i*TICKER_WIDGETS_WIDTH;
        (*ticker_widgets)[i] = new HighlightTextWidget(x_pos,0, TICKER_WIDGETS_WIDTH,TICKER_WIDGETS_WIDTH, TICKER_WIDGETS_DEFAULT_COLOR, TICKER_WIDGETS_HIGHLIGHT_COLOR, (*tickers)[i], sf::Color::Black, font, DEFAULT_WIDGET_FONT_SIZE);
    }
    
    // Ticker widgets must be initialised before we can determine if they should be drawn or not
    update_should_draw();
    
}

void TickerWidgets::select_ticker(float mouse_x, float mouse_y) {
    // Find which ticker the mouse is hovering over
    const unsigned int tickers_size = tickers->size();
    int selected_index = 0;
    
    // Select the new ticker and unselect every other ticker
    for (unsigned int i=0; i<tickers_size; i++) {
        (*is_selected)[i] = false;
        (*ticker_widgets)[selected_index]->color = default_color;
    }
    (*is_selected)[selected_index] = true;
    
    (*ticker_widgets)[selected_index]->color = selected_color;
}

void TickerWidgets::draw(sf::RenderWindow* window, float mouse_x, float mouse_y) {
    const unsigned int tickers_size = tickers->size();
    for (unsigned int i=0; i<tickers_size; i++) {
        const float left_side = DEFAULT_WIDGET_WIDTH+TICKER_WIDGETS_SCROLLER_WIDTH;
        const float wx = (*ticker_widgets)[i]->x;
        const bool should_draw = (wx >= left_side) && wx <= WINDOW_WIDTH-TICKER_WIDGETS_SCROLLER_WIDTH;
        if (should_draw) {
            (*ticker_widgets)[i]->draw(window, mouse_x, mouse_y);
        }
    }
    left_ticker_scroller->draw(window, mouse_x, mouse_y);
    right_ticker_scroller->draw(window, mouse_x, mouse_y);
}

void TickerWidgets::scroll_tickers_left() {
    const unsigned int tickers_size = tickers->size();
    bool can_move = false;
    for (unsigned int i=0; i<tickers_size; i++) {
        const float left_side = DEFAULT_WIDGET_WIDTH;
        const float wx = (*ticker_widgets)[i]->x;
        if (wx <= left_side) {
            can_move = true;
            break;
        }
    }
    
    if (can_move) {
        for (unsigned int i=0; i<tickers_size; i++) {
            (*ticker_widgets)[i]->move(TICKER_WIDGETS_WIDTH, 0);
        }
        update_should_draw();
    }
}

void TickerWidgets::scroll_tickers_right() {
    const unsigned int tickers_size = tickers->size();
    bool can_move = false;
    for (unsigned int i=0; i<tickers_size; i++) {
        const float right_side = WINDOW_WIDTH-TICKER_WIDGETS_SCROLLER_WIDTH;
        const float wx = (*ticker_widgets)[i]->x;
        if (wx >= right_side) {
            can_move = true;
            break;
        }
    }
    
    if (can_move) {
        for (unsigned int i=0; i<tickers_size; i++) {
            (*ticker_widgets)[i]->move(-TICKER_WIDGETS_WIDTH, 0);
        }
        update_should_draw();
    }
}

void TickerWidgets::update_should_draw() {
    const unsigned int tickers_size = tickers->size();
        for (unsigned int i=0; i<tickers_size; i++) {
        const float left_side = DEFAULT_WIDGET_WIDTH+TICKER_WIDGETS_SCROLLER_WIDTH;
        const float wx = (*ticker_widgets)[i]->x;
        const bool sd = (wx >= left_side) && wx <= WINDOW_WIDTH-TICKER_WIDGETS_SCROLLER_WIDTH;
        (*should_draw)[i] = sd;
    }
}
