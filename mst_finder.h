#ifndef MST_FINDER_H
#define MST_FINDER_H

#include <vector>
#include <queue>
#include <unordered_set>

#include <graph.h>
#include <graph_edge.h>

using namespace std;

namespace graph_algorithms
{
    class mst_finder
    {
    public:
        mst_finder(graph* g);
        pair<double, vector<int>> find_mst();
    private:
        graph *g;
        priority_queue<graph_edge, vector<graph_edge>> edge_queue;
        unordered_set<int> closed_set;

        void add_node_edges_to_queue(int node);
        vector<int> closed_set_to_vector();
    };
}

#endif // MST_FINDER_H
