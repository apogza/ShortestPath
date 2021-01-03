/*
 * A class that describes some of the inner workings
 * of a graph. I have added only what is necessary
 * for the given homework. This class does not describe
 * all the possible behaviors / functionalities of graphs
 *
 * The implementation follows the edge list approach.
 * The graph uses a std::map internally to keep track of
 * the edges of the nodes.
 *
 */

#include <map>
#include <iostream>
#include <graph.h>

namespace graph_algorithms
{
    graph::graph()
    {
        this->is_directed = false;
    }

    graph::graph(bool is_directed)
    {
        this->is_directed = is_directed;
    }

    graph::~graph()
    {
        clear();
    }

    int graph::node_count()
    {
        return node_edge_map.size();
    }

    int graph::edge_count()
    {
        int total_size = 0;
        for (auto& node_edge_pair : node_edge_map)
        {
            total_size += node_edge_pair.second.size();
        }

        return total_size;
    }

    void graph::add_node(int node_label)
    {
        if (!node_exists(node_label))
        {
            auto pair = make_pair(node_label, vector<graph_edge*>());
            node_edge_map.insert(pair);
        }
    }

    bool graph::node_exists(int node_label)
    {
        return node_edge_map.find(node_label) != node_edge_map.end();
    }

    /*
     * This is the method to be used for building edges
     */

    void graph::add_edge(double weight, int start_node, int dest_node)
    {
        graph_edge* edge = new graph_edge(weight, dest_node);
        add_edge(start_node, edge);
    }

    /*
     * Internal for the class methd to make things a bit easier
     */
    void graph::add_edge(int start_node, graph_edge* edge)
    {
        char dest_node = edge->get_dest_node();

        if (!node_exists(start_node))
        {
            add_node(start_node);
        }

        if (!node_exists(dest_node))
        {
            add_node(dest_node);
        }

        if (!edge_exists(start_node, edge))
        {
            node_edge_map[start_node].push_back(edge);

            // insert inverse edge for undirected graphs
            if (!is_directed)
            {
                graph_edge* inverse_edge = new graph_edge(edge->get_weight(), start_node);
                if (!edge_exists(dest_node, inverse_edge))
                {
                    node_edge_map[dest_node].push_back(inverse_edge);
                }
                else
                {
                    delete inverse_edge;
                }
            }
        }
        else
        {
            delete edge;
        }
    }

    void graph::print()
    {
        for (auto& pair : node_edge_map)
        {
            cout << "Node: " << pair.first << " -> ";
            for (graph_edge* e : pair.second)
            {
                cout << e->get_dest_node() << " ";
            }
            cout << endl;
        }
    }

    /*
     * A bit useless since the note_edge_map
     * contains everything: nodes and edges
     */

    vector<int> graph::get_nodes()
    {
        vector<int> nodes;

        for (auto& node_edges : node_edge_map)
        {
            nodes.push_back(node_edges.first);
        }

        // return by value
        return nodes;
    }

    /*
     * Returns the edges for a given node
     *
     */
    vector<graph_edge*>& graph::get_edges(int node)
    {
        // return by reference
        return node_edge_map[node];
    }

    /*
     * Internal method to check whether an edge
     * already exists for a node.
     * We do not want to duplicate edges.
     */

    bool graph::edge_exists(int start_node, graph_edge* edge)
    {
        if (!node_exists(start_node))
        {
            return false;
        }

        bool result = false;

        vector<graph_edge*> edges = node_edge_map[start_node];

        for (graph_edge* node_edge : edges )
        {
            if (edge->get_dest_node() == node_edge->get_dest_node())
            {
                result = true;
                break;
            }
        }

        return result;
    }

    /*
     * Used in the destructor to clear all edges
     * that are on the heap
     */

    void graph::clear()
    {
        for (auto& pair: node_edge_map)
        {
            vector<graph_edge*> edges = pair.second;
            for (graph_edge* edge : edges)
            {
                delete edge;
            }
        }
    }
}
