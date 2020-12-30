/*
 * This is an auxiliary data structure that ensures
 * that we have the closest unvisited node on hand
 * and we are able to update its weight as the algorithm runs.
 *
 * The structure uses a std::map internally,
 * so that lookups and updates are fast.
 *
 */

#include <node_priority_queue.h>

using namespace std;

namespace shortest_path
{
    node_priority_queue::node_priority_queue()
    {
        min_weight = 0;
        min_weight_node = 0;
    }

    void node_priority_queue::enqueue(int node, double weight)
    {
        auto pair = make_pair(node, weight);
        node_weight_map.insert(pair);

        if (weight < min_weight
                || min_weight == 0)
        {
            min_weight = weight;
            min_weight_node = node;
        }
    }

    /*
     * Update the weight of a node, only if necessary:
     * only of the new weight is less that the old one
     *
     */
    void node_priority_queue::try_update(int node, double new_weight)
    {
        double old_weight = node_weight_map[node];

        if (new_weight < old_weight)
        {
            node_weight_map[node] = new_weight;

            // see if that is our new min_weight node
            // if so, remember it so that we can use it
            if (new_weight < min_weight)
            {
                min_weight = new_weight;
                min_weight_node = node;
            }
        }
    }

    bool node_priority_queue::has_node(int node)
    {
        return node_weight_map.find(node) != node_weight_map.end();
    }

    /*
     * Scan the map
     */
    void node_priority_queue::update_min_weight()
    {
        min_weight = 0;
        min_weight_node = 0;
        for (auto pair : node_weight_map)
        {
            if (pair.second < min_weight || min_weight == 0)
            {
                min_weight = pair.second;
                min_weight_node = pair.first;
            }
        }
    }

    pair<int, double> node_priority_queue::dequeue()
    {
        pair<int, double> result = make_pair(min_weight_node, min_weight);

        node_weight_map.erase(min_weight_node);
        update_min_weight();

        return result;
    }

    void node_priority_queue::clear()
    {
        min_weight = 0;
        min_weight_node = 0;

        node_weight_map.clear();
    }
}
