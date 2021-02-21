
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "includes/datapoint.h"
#include "includes/IO.h"
#include "includes/stockdata_manipulation.h"
#include "includes/widget.h"
#include "includes/graphs.h"
#include "includes/screen.h"

// Graph types: candle graph, bar chart, line graph
// View stock's open, close adj, high, low, volume over a specific date range
// 

/*
    auto t1 = std::chrono::high_resolution_clock::now();
// function();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    printf("It took: %ld milliseconds for the function to run\n", duration);
*/

int main() {
    constexpr unsigned int window_width = 1920;
    constexpr unsigned int window_height = 1080;
    
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(window_width, window_height, 1), "VisuStock V2!");
    
    std::string font_location = "res/liberation-mono.ttf";
    sf::Font* font = new sf::Font();
    bool font_loaded = font->loadFromFile(font_location);
    if (!font_loaded) {
        fprintf(stderr, "Could not open font at location: %s\n", font_location.c_str());
        assert(false);
    }
    
    std::string input_file_location = "res/stock_data/daily_prices100k.csv";
    auto stock_data = parse_datapoints_from_file(input_file_location);
    
    std::vector<std::string>* tickers = i_sort(stock_data);
    assert(tickers != nullptr);
    
    Screen* screen = new Screen(window_width, window_height, tickers, stock_data, font);
    
    while (window->isOpen()) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        const float mouse_x = (float)mouse_pos.x;
        const float mouse_y = (float)mouse_pos.y;
        
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }
        }
        
        window->clear();
        
        screen->draw(window, mouse_x, mouse_y);
        
        window->display();
        
    }
        
    return 0;
}