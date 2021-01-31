
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "includes/datapoint.h"
#include "includes/IO.h"
#include "includes/stockdata_manipulation.h"

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
    // sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600, 1), "VisuStock V2!");
    
    std::string input_file_location = "../res/stock_data/daily_prices200k.csv";
    
    auto stock_data = parse_datapoints_from_file(input_file_location);
    
    sort_by_ticker(stock_data);
    std::vector<std::string>* tickers = parse_tickers(stock_data);
    
    
    
    /*
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                
            }
            
            window->clear();
            window->display();
        }
        */
    return 0;
}