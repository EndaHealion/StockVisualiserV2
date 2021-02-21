#include "includes/graphs.h"

void generate_candle_graph(std::vector<DataPoint*>* datapoints) {
}

sf::VertexArray* generate_line_graph(std::vector<DataPoint*>* datapoints) {
    const unsigned int datapoints_size = datapoints->size();
    
    const float highest_point = 50;
    const float lowest_point = 1060;
    const float dx = 5;
    float current_x = 0;
    
     float max_value = 0;
    for (int i=0; i<datapoints_size; i++) {
        if ((*datapoints)[i]->open_price > max_value) {
            max_value = (*datapoints)[i]->open_price;
        }
    }
    
    sf::VertexArray* vs = new sf::VertexArray(sf::PrimitiveType::LineStrip, datapoints_size);
    for (int i=0; i<datapoints_size; i++) {
        const float y_pos = map((*datapoints)[i]->open_price, 0, max_value, lowest_point, highest_point);
        (*vs)[i] = sf::Vertex(sf::Vector2f(current_x, y_pos), sf::Color::Green);
        current_x += dx;
    }
    
    return vs;
}

void generate_bar_chart(std::vector<DataPoint*>* datapoints) {
}

// TODO(Enda): Fix this so that it uses triangle strip primitive or quad primitive to enable thickness...
sf::VertexArray* generate_line_vertex_data(float x1, float y1, float x2, float y2, float thickness, sf::Color color) {
    sf::VertexArray* verts = new sf::VertexArray(sf::PrimitiveType::Lines, 2);
    /*
    const float PI = cosf(-1);
    const float x = x2-x1;
    const float y = y2-y1;
    const float line_angle_rads = (float)atan2(y, x);
    const float thickness_angle_rads = line_angle_rads + (90 * (180/PI));
    const float dx = thickness*0.5f * (float)cosf(thickness_angle_rads);
    const float dy = thickness*0.5f * (float)sinf(thickness_angle_rads);
    
    (*verts)[0] = sf::Vertex(sf::Vector2f(x1+dx, y1-dy), color);
    (*verts)[1] = sf::Vertex(sf::Vector2f(x1-dx, y1+dy), color);
    (*verts)[2] = sf::Vertex(sf::Vector2f(x2+dx, y2-dy), color);
    (*verts)[3] = sf::Vertex(sf::Vector2f(x2-dx, y2+dy), color);
*/
    
    (*verts)[0] = sf::Vertex(sf::Vector2f(x1, y1), color);
    (*verts)[1] = sf::Vertex(sf::Vector2f(x2, y2), color);
    
    return verts;
}

float map(float value, float in_min, float in_max, float out_min, float out_max) {
    const float slope = (out_max-out_min) / (in_max-in_min);
    return out_min + slope*(value-in_min);
}
