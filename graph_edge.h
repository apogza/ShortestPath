#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <iostream>

namespace graph_algorithms
{
    class graph_edge
    {
      public:
        graph_edge(double weight, int dest_node);
        double get_weight() const;
        int get_dest_node();

        // overload operator so that it can be used for printing
        friend std::ostream& operator<<(std::ostream& out, graph_edge& edge);

        // overload operator so that it can be used for sorting
        bool operator<(const graph_edge& edge) const;
      private:
        double weight;
        int dest_node;
    };
}

#endif // GRAPHEDGE_H
