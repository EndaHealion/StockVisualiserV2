
#include <vector>
#include <SFML/Graphics.hpp>

#include "includes/datapoint.h"
#include "includes/IO.h"

int main() {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600, 1), "VisuStock V2!");
    
    auto stock_data = parse_datapoints_from_file("../res/stock_data/daily_prices100k.csv");
    
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
    
    return 0;
}