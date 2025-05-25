#pragma once

/**
 * @file Graph.hpp
 * @author Evan F.
 * @brief The header of the abstract Graph container.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"

#include "Ocean/Primitives/Structures/Container.hpp"

/**
 * @brief The abstract Graph container.
 * 
 * @tparam T The data type.
 */
template <class T>
class Graph : public Container {
public:
    using NodeID = u16;

public:
    virtual ~Graph() = default;

    /**
     * @brief Adds an edge from vertex to vertex.
     * 
     * @param from A unique index of the starting vertex.
     * @param to A unique index of the ending vertex.
     */
    virtual void AddEdge(NodeID from, NodeID to) = 0;
    /**
     * @brief Removes an edge from vertex to vertex.
     * 
     * @param from A unique index of the starting vertex.
     * @param to A unique index of the ending vertex.
     */
    virtual void RemoveEdge(NodeID from, NodeID to) = 0;

    /**
     * @brief Determines if the given vertex's share an edge.
     * 
     * @param from A unique index of the starting vertex.
     * @param to A unique index of the ending vertex.
     * @return b8
     */
    virtual b8 HasEdge(NodeID from, NodeID to) = 0;

};  // Graph
