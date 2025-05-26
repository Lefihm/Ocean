/**
 * @file DAGraph.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Bitrix.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Primitives/Structures/Graph.hpp"

#include "Ocean/Primitives/DynamicArray.hpp"

#include "Ocean/Core/Exceptions.hpp"

// std
#include <queue>
#include <sstream>
#include <unordered_set>

template <class T>
class DirectedGraph : public Graph<T> {
public:
    using NodeID = u16;

    /**
     * @brief A graph node holding an ID and the user-defined data.
     */
    struct Node {
        NodeID id;

        T data;

    };  // Node

public:
    DirectedGraph() = default;
    DirectedGraph(const DirectedGraph& other) :
        m_Nodes(other.m_Nodes),
        m_Edges(other.m_Edges)
    { }
    DirectedGraph(DirectedGraph&& other) :
        m_Nodes(std::move(other.m_Nodes)),
        m_Edges(std::move(other.m_Edges))
    { }
    virtual ~DirectedGraph() = default;
    
    DirectedGraph& operator = (const DirectedGraph& rhs) {
        this->m_Nodes = rhs.m_Nodes;
        this->m_Edges = rhs.m_Edges;

        return *this;
    }
    DirectedGraph& operator = (DirectedGraph&& rhs) {
        this->m_Nodes = rhs.m_Nodes;
        this->m_Edges = rhs.m_Edges;

        rhs.m_Nodes.Clear();
        rhs.m_Edges.Clear();

        return *this;
    }

    /**
     * @brief Add a new node with associated data.
     * 
     * @param data The data to store.
     * @return NodeID A unique ID assigned to the node.
     */
    NodeID AddNode(const T& data) {
        NodeID id = static_cast<NodeID>(this->m_Nodes.Size());

        this->m_Nodes.EmplaceBack({ id, data });
        this->m_Edges.Reserve(id + 1, false);

        return id;
    }
    /**
     * @brief Removes a node and its associated edges.
     * 
     * @param id The node ID to remove.
     */
    void RemoveNode(NodeID id) {
        this->m_Nodes.Erase(id);

        Bitrix2D newEdges(this->m_Nodes.Size());

        for (NodeID from = 0; from < this->m_Nodes.Size() + 1; from++) {
            if (from == id)
                continue;

            for (NodeID to = 0; to < this->m_Nodes.Size() + 1; to++) {
                if (to == id)
                    continue;

                NodeID newFrom = (from > id) ? from - 1 : from;
                NodeID newTo = (to > id)     ? to - 1   : to;

                if (this->m_Edges.Get(from, to))
                    newEdges.Set(newFrom, newTo, true);
            }
        }

        this->m_Edges = std::move(newEdges);

        for (NodeID i = 0; i < this->m_Nodes.Size(); i++)
            this->m_Nodes[i].id = i;
    }

    /**
     * @brief Add a directed edge from one node to another.
     * 
     * @param from The source node ID.
     * @param to The destination node ID.
     */
    virtual void AddEdge(NodeID from, NodeID to) override {
        this->m_Edges.Set(from, to, true);
    }
    /**
     * @brief Remove a directed edge form the graph.
     * 
     * @param from The source node ID.
     * @param to The destination node ID.
     */
    virtual void RemoveEdge(NodeID from, NodeID to) override {
        this->m_Edges.Set(from, to, false);
    }
    /**
     * @brief Checks if an edge exists between two nodes.
     * 
     * @param from The source node ID.
     * @param to The destination node ID.
     * @return b8 True if edge exists, false otherwise.
     */
    virtual b8 HasEdge(NodeID from, NodeID to) override {
        return this->m_Edges.Get(from, to);
    }

    /**
     * @brief Gets the list of all nodes.
     * 
     * @return const DynamicArray<Node>& 
     */
    const DynamicArray<Node>& GetNodes() const { return this->m_Nodes; }
    DynamicArray<Node>& GetNodes() { return this->m_Nodes; }

    /**
     * @brief Gets all outgoing edges from a node.
     * 
     * @param from The node ID.
     * @return DynamicArray<NodeID> 
     */
    DynamicArray<NodeID> GetOutEdges(NodeID from) const {
        DynamicArray<NodeID> out;

        for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
            if (this->m_Edges.Get(from, to))
                out.EmplaceBack(to);

        return out;
    }
    /**
     * @brief Gets all incoming edges to a node.
     * 
     * @param to The node ID.
     * @return DynamicArray<NodeID> 
     */
    DynamicArray<NodeID> GetInEdges(NodeID to) const {
        DynamicArray<NodeID> in;

        for (NodeID from = 0; from < this->m_Nodes.Size(); from++)
            if (this->m_Edges.Get(from, to))
                in.EmplaceBack(from);

        return in;
    }

    /**
     * @brief Detects if the graph contains a cycle using Kahn's algorithm.
     * 
     * @return b8 True if a cycle is present, false otherwise.
     */
    b8 HasCycle() const {
        DynamicArray<u16> inDegree(this->m_Nodes.Size());

        for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
            for (NodeID from = 0; from < this->m_Nodes.Size(); from++)
                if (this->m_Edges.Get(from, to))
                    inDegree[to]++;

        std::queue<NodeID> q;
        for (NodeID i = 0; i < this->m_Nodes.Size(); i++)
            if (inDegree[i] == 0)
                q.push(i);

        u16 visitedCount = 0;
        while (!q.empty()) {
            NodeID node = q.front();
            q.pop();
            visitedCount++;

            for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
                if (this->m_Edges.Get(node, to))
                    if (--inDegree[to] == 0)
                        q.push(to);
        }

        return visitedCount != this->m_Nodes.Size();
    }

    /**
     * @brief Performs a topological sort on the graph.
     * 
     * @throws Ocean::Error::RUNTIME_ERROR if the graph contains a cycle.
     * 
     * @return DynamicArray<NodeID> 
     */
    DynamicArray<NodeID> TopologicalSort() const {
        DynamicArray<NodeID> result;
        DynamicArray<u16> inDegree(this->m_Nodes.Size());

        for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
            for (NodeID from = 0; from < this->m_Nodes.Size(); from++)
                if (this->m_Edges.Get(from, to))
                    inDegree[to]++;

        std::queue<NodeID> q;
        for (NodeID i = 0; i < this->m_Nodes.Size(); i++)
            if (inDegree[i] == 0)
                q.push(i);

        while (!q.empty()) {
            NodeID node = q.front();
            q.pop();
            result.EmplaceBack(node);

            for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
                if (this->m_Edges.Get(node, to))
                    if (--inDegree[to] == 0)
                        q.push(to);
        }

        if (result.Size() != this->m_Nodes.Size())
            throw Ocean::Exception(Ocean::Error::RUNTIME_ERROR, "Cycle detected, topological sort not possible.");

        return result;
    }

    /**
     * @brief Gets the graph as a list of parallel paths.
     * 
     * @throws Ocean::Error::RUNTIME_ERROR if cycles are detected.
     * 
     * @return DynamicArray<DynamicArray<NodeID>> 
     */
    DynamicArray<DynamicArray<NodeID>> GetParallelPaths() const {
        DynamicArray<u16> inDegree(this->m_Nodes.Size());

        for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
            for (NodeID from = 0; from < this->m_Nodes.Size(); from++)
                if (this->m_Edges.Get(from, to))
                    inDegree[to]++;

        DynamicArray<DynamicArray<NodeID>> stages;
        std::unordered_set<NodeID> visited;

        while (visited.size() < this->m_Nodes.Size()) {
            DynamicArray<NodeID> stage;

            for (NodeID i = 0; i < this->m_Nodes.Size(); i++) {
                if (inDegree[i] == 0 && visited.find(i) == visited.end()) {
                    stage.EmplaceBack(i);
                    visited.insert(i);
                }
            }

            for (NodeID node : stage) {
                for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
                    if (this->m_Edges.Get(node, to))
                        inDegree[to]--;
            }

            if (stage.Empty())
                throw Ocean::Exception(Ocean::Error::RUNTIME_ERROR, "Cycle detected during parallel path search.");

            stages.EmplaceBack(std::move(stage));
        }

        return stages;
    }

    /**
     * @brief Gets a string representation of the graph.
     * 
     * @return String of the graph in a readable format.
     * @todo Make ToString json format.
     */
    String ToString() const {
        std::ostringstream oss;

        oss << "DirectedGraph\n";
        oss << "Nodes (" << this->m_Nodes.Size() << "):\n";

        for (const Node& node : this->m_Nodes) {
            oss << "\t[" << node.id << "] = ";

            oss << node.data << "\n";
        }

        oss << "Edges:\n";

        for (NodeID from = 0; from < this->m_Nodes.Size(); from++)
            for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
                if (this->m_Edges.Get(from, to))
                    oss << "\t" << from << " -> " << to << "\n";

        return oss.str();
    }

private:
    /** @brief The list of nodes in the graph. */
    DynamicArray<Node> m_Nodes;
    /** @brief A matrix of edges in the graph. */
    Bitrix2D m_Edges;

};  // Graph
