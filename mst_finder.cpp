#include <algorithm>

#include "mst_finder.h"

using namespace std;

namespace graph_algorithms
{
    mst_finder::mst_finder(graph* g)
    {
        this->g = g;
    }

    /*
     *
     * Implementation of the Jarnik-Prim algorithm
     *
     */
    pair<double, vector<int>> mst_finder::find_mst()
    {
        closed_set.clear();
        vector<int> visited_nodes;

        unsigned node_count = g->node_count();
        double total_weight = 0;

        // start the mst from any node
        // pick the first one for convenience
        int current_node = g->get_nodes().at(0);

        closed_set.insert(current_node);
        visited_nodes.push_back(current_node);

        add_node_edges_to_queue(current_node);

        while (!edge_queue.empty() && closed_set.size() < node_count)
        {
            graph_edge min_edge = edge_queue.top();
            edge_queue.pop();

            if (closed_set.count(min_edge.get_dest_node()) == 0)
            {
                total_weight += min_edge.get_weight();

                int current_node = min_edge.get_dest_node();

                closed_set.insert(current_node);
                visited_nodes.push_back(current_node);

                add_node_edges_to_queue(current_node);
            }
        }

        if ((closed_set.size() != node_count))
        {
            total_weight = -1;
        }

        return make_pair(total_weight, visited_nodes);
    }

    /*
     * For each new visited node, add its edges
     * to the priority queue
     *
     */
    void mst_finder::add_node_edges_to_queue(int node)
    {
        vector<graph_edge*> edges = g->get_edges(node);

        for (graph_edge* edge : edges)
        {
            edge_queue.push(*edge);
        }
    }
}
