#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <graph_edge.h>
#include <graph.h>
#include <node_priority_queue.h>
#include <vector>
#include <unordered_set>


using namespace std;

namespace graph_algorithms
{
    class path_finder
    {

    public:
        path_finder(graph* g);

        // returns the total cost and the path of nodes
        pair<double, vector<int>> find_path(int start_node, int end_node);

    private:
        graph* g;

        // a set to keep track of all the nodes that have been reached
        unordered_set<int> closed_set;

        // a set to keep track of all the available edges
        // from all the nodes that we have reached
        // the shortest edge is at the top
        node_priority_queue open_set;

        void update_open_set(int& current_node, vector<graph_edge*>& edges, double& total_weight);
        vector<int> closed_set_to_vector();
    };
}

#endif // SHORTESTPATH_H
