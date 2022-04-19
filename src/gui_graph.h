//
// Created by David Sullivan on 4/18/22.
//

#ifndef GRACEFULTOOLING_GUI_GRAPH_H
#define GRACEFULTOOLING_GUI_GRAPH_H

#include "graph_lite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>

#include <optional>

#include "color_definitions.h"

using graph_lite::EdgeDirection;

class GuiVertexData {
public:
    sf::Color m_color;
    std::optional<int> m_label;
    GuiVertexData(sf::Color color=app_colors::VERTEX_1, std::optional<int> label=std::nullopt);
};

class GuiEdgeData {
public:
    int m_length;
    sf::Color m_color;
    std::optional<int> m_label;
    GuiEdgeData(int length, sf::Color color=app_colors::EDGE_1,
                std::optional<int> label=std::nullopt);
};

class GuiDrawSettings {
public:
    float m_vertexRadius;
    float m_graphRadius;
    float m_edgeWidth;
    sf::Font m_vertexFont;
    GuiDrawSettings(float vertexRadius = 45.f, float graphRadius = 400.f, float edgeWidth = 20.f);
};

class GuiGraph {
private:
    graph_lite::Graph<int, GuiVertexData, GuiEdgeData, EdgeDirection::UNDIRECTED> m_graph;
public:
    GuiDrawSettings m_drawSettings;
    GuiGraph(int vertexCount, GuiDrawSettings drawSettings=GuiDrawSettings() );
    //the following methods all return true if the function was successful, but false
    //if the vertex or edge does not exist
    bool addEdge(int vertex1, int vertex2,
                 sf::Color color=app_colors::EDGE_1, std::optional<int> label=std::nullopt);
    bool addEdge(int vertex1, int vertex2,
                 float color[3], std::optional<int> label=std::nullopt);
    bool removeEdge(int vertex1, int vertex2);
    bool labelEdge(int vertex1, int vertex2, int label);
    bool unlabelEdge(int vertex1, int vertex2);
    bool colorEdge(int vertex1, int vertex2, sf::Color color);
    bool colorVertex(int vertex, sf::Color color);
    bool labelVertex(int vertex, int label);
    bool unlabelVertex(int vertex);
    void display(sf::RenderWindow& window);
};


#endif //GRACEFULTOOLING_GUI_GRAPH_H
