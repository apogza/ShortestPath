/*
 *
 * Implementation of the Dijkstra's algorithm.
 * The path is computed for a graph that is
 * specified in the constructor as the object
 * is initialized.
 *
 */

#include <path_finder.h>

using namespace std;

namespace graph_algorithms
{
    path_finder::path_finder(graph* g)
    {
        this->g = g;
    }

    /*
     * Dijkstra's algorithm
     *
     */
    pair<double, vector<int>> path_finder::find_path(int start_node, int end_node)
    {
        open_set.clear();
        closed_set.clear();
        vector<int> visited_nodes;

        int current_node = start_node;
        double total_weight = 0;

        while (current_node != end_node)
        {
            closed_set.insert(current_node);
            visited_nodes.push_back(current_node);

            vector<graph_edge*> current_node_edges = g->get_edges(current_node);
            update_open_set(current_node, current_node_edges, total_weight);

            // the shortest edge is at the top of the set
            // we get its weight and the node itself
            auto closest_node = open_set.dequeue();

            // if no closest node, then stop
            // probably the graph is not connected
            if (closest_node.first == 0)
            {
                total_weight = -1;

                closed_set.clear();
                visited_nodes.clear();

                break;
            }

            total_weight += closest_node.second;
            current_node = closest_node.first;
        }

        if (total_weight > 0)
        {
            closed_set.insert(current_node);
            visited_nodes.push_back(current_node);
        }

        return make_pair(total_weight, visited_nodes);
    }

    /*
     * Add newly encountered nodes to the open set,
     * update, if necessary, those we have already found before
     *
     */

    void path_finder::update_open_set(int& current_node, vector<graph_edge*>& edges, double& total_weight)
    {
        for (graph_edge* e : edges)
        {
            int node = e->get_dest_node();
            int weight = e->get_weight();

            // make sure we are not adding edges that lead to already visited nodes
            if (closed_set.count(node) == 0)
            {

                if (open_set.has_node(node))
                {
                    open_set.try_update(current_node, total_weight + weight);
                }
                else
                {
                    open_set.enqueue(node, weight);
                }
            }
        }
    }
}
