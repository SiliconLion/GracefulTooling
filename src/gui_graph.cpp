//
// Created by David Sullivan on 4/18/22.
//

#include "gui_graph.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "graph_labeling_utilities.h"
#include "platform_configuration.h"

GuiVertexData::GuiVertexData(sf::Color color, std::optional<int> label) :
    m_color(color), m_label(label)
{}

GuiEdgeData::GuiEdgeData(int length, sf::Color color, std::optional<int> label) :
    m_length(length), m_color(color), m_label(label)
{}

GuiDrawSettings::GuiDrawSettings(float vertexRadius, float graphRadius) :
    m_vertexRadius(vertexRadius), m_graphRadius(graphRadius), m_vertexFont()
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

//draw the vertices
    for(int i = 0; i < vertexCount; i++) {
        sf::Text vertexLabel(std::to_string(i), vertexFont);

//the -pi/2 makes it so the 0'th vertex is always at the top of the cirlce
        float angle = (i * angle_increment) - M_PI_2;
        float vertex_center_x = (cos(angle) * graphRadius) + window_center_x;
        float vertex_center_y = (sin(angle) * graphRadius) + window_center_y;

        sf::CircleShape vertex = sf::CircleShape(vertexRadius);
        vertex.setOrigin(vertexRadius/2.0, vertexRadius/2.0);


        vertex.setPosition(vertex_center_x, vertex_center_y);
        vertex.setFillColor(app_colors::VERTEX_1);

//this will look somewhat off as origin is top left centered, not center centered
        vertexLabel.setPosition(vertex_center_x, vertex_center_y);
        vertexLabel.setFillColor(app_colors::VERTEX_TEXT);

        window.draw(vertex);
        window.draw(vertexLabel);
    }
}




