//
// Created by David Sullivan on 4/18/22.
//

#include "graph_labeling_utilities.h"

#include <algorithm>

int vertex_distance(int vertex1, int vertex2, int vertexCount) {
    return std::min(
            std::abs(vertex1 - vertex2) % vertexCount,
            std::abs(vertex2 - vertex1) % vertexCount
            );
}