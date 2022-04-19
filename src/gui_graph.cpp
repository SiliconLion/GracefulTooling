//
// Created by David Sullivan on 4/18/22.
//

#include "gui_graph.h"

#include <vector>
#include <array>
#include <math.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "graph_labeling_utilities.h"
#include "platform_configuration.h"

GuiVertexData::GuiVertexData(sf::Color color, std::optional<int> label) :
    m_color(color), m_label(label)
{}

GuiEdgeData::GuiEdgeData(int length, sf::Color color, std::optional<int> label) :
    m_length(length), m_color(color), m_label(label)
{}

GuiDrawSettings::GuiDrawSettings(float vertexRadius, float graphRadius, float edgeWidth) :
    m_vertexRadius(vertexRadius), m_graphRadius(graphRadius), m_edgeWidth(edgeWidth), m_vertexFont()
{
    m_vertexFont.loadFromFile(ARIAL_FONT_PATH);
}

GuiGraph::GuiGraph(int vertexCount, GuiDrawSettings settings):
    m_graph(), m_drawSettings(settings)
{
    graph_lite::Graph<int, GuiVertexData, GuiEdgeData, EdgeDirection::UNDIRECTED> t;
    for(int i = 0; i < vertexCount; i++) {
        m_graph.add_node_with_prop(i, GuiVertexData());
    }
}

bool GuiGraph::addEdge(int vertex1, int vertex2,
             sf::Color color, std::optional<int> label){
    GuiEdgeData data(vertex_distance(vertex1, vertex2, m_graph.size()), color, label);
    //ToDo: intercept the std::cerr output or verify the vertices are valid
    return bool( m_graph.add_edge_with_prop(vertex1, vertex2, data) );
}

bool GuiGraph::addEdge(int vertex1, int vertex2,
             float color[3], std::optional<int> label) {
    sf::Color c(
            sf::Uint8(color[0] * 255.f),
            sf::Uint8(color[1] * 255.f),
            sf::Uint8(color[2] * 255.f),
            255
            );
    GuiEdgeData data(vertex_distance(vertex1, vertex2, m_graph.size()), c, label);
    //ToDo: intercept the std::cerr output or verify the vertices are valid
    return bool( m_graph.add_edge_with_prop(vertex1, vertex2, data) );
}

bool GuiGraph::removeEdge(int vertex1, int vertex2){
    //ToDo: intercept the std::cerr output or verify the vertices are valid
    return bool( m_graph.remove_edge(vertex1, vertex2) );
}

bool GuiGraph::labelEdge(int vertex1, int vertex2, int label){
    bool edgeExists = m_graph.find_neighbor(vertex1, vertex2).first;
    if(edgeExists) {
        GuiEdgeData& prop = m_graph.edge_prop(vertex1, vertex2);
        prop.m_label = {label};
        return true;
    } else {
        return false;
    }
}

bool GuiGraph::unlabelEdge(int vertex1, int vertex2){
    bool edgeExists = m_graph.find_neighbor(vertex1, vertex2).first;
    if(edgeExists) {
        GuiEdgeData &prop = m_graph.edge_prop(vertex1, vertex2);
        prop.m_label = {std::nullopt};
        return true;
    } else {
        return false;
    }
}

bool GuiGraph::colorEdge(int vertex1, int vertex2, sf::Color color){
    bool edgeExists = m_graph.find_neighbor(vertex1, vertex2).first;
    if(edgeExists) {
        GuiEdgeData& prop = m_graph.edge_prop(vertex1, vertex2);
        prop.m_color = color;
        return true;
    } else {
        return false;
    }
}

bool GuiGraph::colorVertex(int vertex, sf::Color color){
    bool vertexExists = m_graph.has_node(vertex);
    if(vertexExists) {
        GuiVertexData& prop = m_graph.node_prop(vertex);
        prop.m_color = color;
        return true;
    } else {
        return false;
    }
}

bool GuiGraph::labelVertex(int vertex, int label){
    bool vertexExists = m_graph.has_node(vertex);
    if(vertexExists) {
        GuiVertexData& prop = m_graph.node_prop(vertex);
        prop.m_label = label;
        return true;
    } else {
        return false;
    }
}

bool GuiGraph::unlabelVertex(int vertex){
    bool vertexExists = m_graph.has_node(vertex);
    if(vertexExists) {
        GuiVertexData& prop = m_graph.node_prop(vertex);
        prop.m_label = {std::nullopt};
        return true;
    } else {
        return false;
    }
}

void GuiGraph::display(sf::RenderWindow& window){
    unsigned int window_width = window.getSize().x;
    unsigned int window_height = window.getSize().y;

    unsigned int window_center_x = window_width / 2;
    unsigned int window_center_y = window_height / 2;

    int vertexCount = m_graph.size();

    sf::Font vertexFont = m_drawSettings.m_vertexFont;
    float vertexRadius = m_drawSettings.m_vertexRadius;
    float graphRadius = m_drawSettings.m_graphRadius;

    if (vertexCount <= 0) {
        std::cout << "drawing empty graph" << std::endl;
        return;
    }

    float angle_increment = 2.0 * M_PI / float(vertexCount);

    std::vector<sf::CircleShape> vertices;
    std::vector<sf::Text> vertLabels;
//    std::vector<std::array<sf::Vertex, 2>> edges;
    std::vector<sf::RectangleShape> edges;
    std::vector<sf::Text> edgeLabels;

    int i = 0;
    for(auto itt = m_graph.begin(); itt != m_graph.end(); itt++) {
        auto nodeProp = m_graph.node_prop(itt);
//the -pi/2 makes it so the 0'th vertex is always at the top of the cirlce
        float angle = (i * angle_increment) - M_PI_2;
        float vertex_center_x = (cos(angle) * graphRadius) + window_center_x;
        float vertex_center_y = (sin(angle) * graphRadius) + window_center_y;

        vertices.emplace_back(sf::CircleShape(vertexRadius));
        sf::CircleShape& vertex = vertices.at(i);
        vertex.setOrigin(vertexRadius / 2.0, vertexRadius / 2.0);
        vertex.setPosition(vertex_center_x, vertex_center_y);
        vertex.setFillColor(nodeProp.m_color);
        i++; //need this because i is not incrimented by the for loop.
    }

    for(i = 0; i < vertexCount; i++){
        vertLabels.emplace_back(sf::Text(std::to_string(i), vertexFont));
        sf::Text& vertexLabel = vertLabels.at(i);
//        vertexLabel.setOrigin(vertexLabel.getLocalBounds().width/ 2.f, vertexLabel.getLocalBounds().height / 2.f);
        vertexLabel.setPosition(vertices.at(i).getPosition());
        vertexLabel.setFillColor(app_colors::VERTEX_TEXT);
    }

    //TODO: make it so this doesn't include every edge twice.
    i = 0;
    for(auto itt = m_graph.begin(); itt != m_graph.end(); itt++) {
        int currentVertex = *itt;
        auto neighbors = m_graph.neighbors(itt);
        while(neighbors.first != neighbors.second) {
            auto neighborVertex = (*(neighbors.first)).first;
//            std::array line = {sf::Vertex(vertices.at(currentVertex).getPosition()),
//                               sf::Vertex(vertices.at(neighbor).getPosition())};
//            edges.push_back(line);
            sf::Vector2 startPos = vertices.at(currentVertex).getPosition();
            sf::Vector2 endPos = vertices.at(neighborVertex).getPosition();
            float lineLength = sqrt( pow(startPos.x - endPos.x, 2.f) + pow(startPos.y - endPos.y, 2.f));
            float angle =
                    atan( (startPos.x - endPos.x)/(startPos.y - endPos.y)) * (-180.f / M_PI);

            sf::RectangleShape line(sf::Vector2(m_drawSettings.m_edgeWidth, lineLength));
            line.setOrigin(line.getSize().x / 2.f, line.getSize().y / 2.f);
            line.setPosition( (startPos + endPos) / 2.f);
            line.setRotation(angle);
            line.setFillColor(app_colors::EDGE_1);

            auto prop = m_graph.edge_prop(currentVertex, neighborVertex);
            sf::Text label = (sf::Text(std::to_string(prop.m_length), vertexFont));
            label.setOrigin(label.getLocalBounds().width/ 2.f, label.getLocalBounds().height / 2.f);
            label.setPosition(line.getPosition());
            label.setFillColor(app_colors::EDGE_TEXT);

            edges.push_back(line);
            edgeLabels.push_back(label);

            neighbors.first++;
        }
    }


//    for (auto edge: edges) {
//        window.draw(edge.data(), 2, sf::Lines);
//    }
    for(auto edge: edges) {window.draw(edge);}
    for(auto vertex: vertices) {window.draw(vertex);}
    for(auto label: vertLabels) {window.draw(label);}
    for(auto label: edgeLabels) {window.draw(label);}

}




