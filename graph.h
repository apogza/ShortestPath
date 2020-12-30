#ifndef GRAPH_H
#define GRAPH_H

#include <graph_edge.h>
#include <map>
#include <vector>

using namespace std;

namespace shortest_path
{
    class graph
    {
      public:
        graph();
        graph(bool is_directed);

        ~graph();

        int node_count();
        int edge_count();

        void add_node(int node_label);
        void add_edge(double weight, int start_node, int dest_node);
        void print();

        vector<int> get_nodes();
        vector<graph_edge*>& get_edges(int node);

      private:
        map<int, vector<graph_edge*>> node_edge_map;
        bool is_directed;

        void add_edge(int start_node, graph_edge* edge);
        bool edge_exists(int node_label, graph_edge* edge);

        bool node_exists(int node_label);
        void clear();
    };
}

#endif // GRAPH_H
