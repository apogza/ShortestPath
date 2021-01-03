/*
 * A simple data structure that holds
 * two essential pieces of information:
 *  - the destination node
 *  - the cost to get there
 */

#include <graph_edge.h>
#include <iostream>

using namespace std;

namespace graph_algorithms
{
    graph_edge::graph_edge(double weight, int dest_node)
    {
        this->weight = weight;
        this->dest_node = dest_node;
    }

    double graph_edge::get_weight() const
    {
        return weight;
    }

    int graph_edge::get_dest_node()
    {
        return dest_node;
    }

    /*
     * Can be used for printing
     *
     */
    std::ostream& operator<<(std::ostream& out, graph_edge& edge)
    {
        int dest_node = edge.get_dest_node();
        out << "Edge to " <<  dest_node;
        out << " -> " << edge.get_weight() << std::endl;

        return out;
    }

    /*
     * Can be used with sorting algorithms
     * or sorted data containers
     *
     */

    bool graph_edge::operator<(const graph_edge& edge) const
    {
        return this->get_weight() > edge.get_weight();
    }
}
