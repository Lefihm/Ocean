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

    struct Node {
        NodeID id;

        T data;

    };  // Node

public:
    DirectedGraph() = default;
    virtual ~DirectedGraph() = default;

    NodeID AddNode(const T& data) {
        NodeID id = static_cast<NodeID>(this->m_Nodes.Size());

        this->m_Nodes.EmplaceBack({ id, data });
        this->m_Edges.Reserve(id + 1, false);

        return id;
    }

    virtual void AddEdge(NodeID from, NodeID to) override {
        this->m_Edges.Set(from, to, true);
    }
    virtual void RemoveEdge(NodeID from, NodeID to) override {
        this->m_Edges.Set(from, to, false);
    }

    virtual b8 HasEdge(NodeID from, NodeID to) override {
        return this->m_Edges.Get(from, to);
    }

    const DynamicArray<Node>& GetNodes() const { return this->m_Nodes; }

    DynamicArray<NodeID> GetOutEdges(NodeID from) const {
        DynamicArray<NodeID> out;

        for (NodeID to = 0; to < this->m_Nodes.Size(); to++)
            if (this->m_Edges.Get(from, to))
                out.EmplaceBack(to);

        return out;
    }
    DynamicArray<NodeID> GetInEdges(NodeID to) const {
        DynamicArray<NodeID> in;

        for (NodeID from = 0; from < this->m_Nodes.Size(); from++)
            if (this->m_Edges.Get(from, to))
                in.EmplaceBack(from);

        return in;
    }

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
    DynamicArray<Node> m_Nodes;
    Bitrix2D m_Edges;

};  // Graph
