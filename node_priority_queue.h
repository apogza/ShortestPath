#ifndef NODEPRIORITYQUEUE_H
#define NODEPRIORITYQUEUE_H

#include <unordered_map>

using namespace std;

namespace graph_algorithms
{
    class node_priority_queue
    {
    public:
        node_priority_queue();
        void enqueue(int node, double weight);
        bool has_node(int node);
        void try_update(int node, double weight);
        pair<int, double> dequeue();
        void clear();
    private:
        unordered_map<int, double> node_weight_map;
        int min_weight_node;
        double min_weight;
        void update_min_weight();
    };
}

#endif // NODEPRIORITYQUEUE_H
