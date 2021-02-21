/* date = February 17th 2021 3:52 pm */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "datapoint.h"

#define M_PI 3.14159265358979323846

void generate_candle_graph(std::vector<DataPoint*>* datapoints);
sf::VertexArray* generate_line_graph(std::vector<DataPoint*>* datapoints);
void generate_bar_chart(std::vector<DataPoint*>* datapoints);

sf::VertexArray* generate_line_vertex_data(float x1, float x2, float y1, float y2, float thickness, sf::Color color);

float map(float value, float in_min, float in_max, float out_min, float out_max);

#endif // GRAPH_H
