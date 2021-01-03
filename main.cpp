#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <numeric>

#include <graph.h>
#include <path_finder.h>
#include <mst_finder.h>

using namespace std;
using namespace graph_algorithms;

/*
 *
 * Gives a random number between
 * the specified boundaries
 *
 */

int get_random_number(int low, int high)
{
    return low + rand() % (high - low);
}

/*
 *
 * Randomnly generate a graph according to the specs
 *  - keep in mind the given density
 *  - each edge varies between 1 and 10
 *
 */

graph* generate_graph(int num_nodes, double density)
{
    graph* g = new graph();

    for (int i = 0; i < num_nodes; i++)
    {
        g->add_node(i);
    }

    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = i + 1; j < num_nodes; j++)
        {
            double random_prob = get_random_number(0, 100);

            // generate the edge only if it is less than the
            // specified density

            if (random_prob < density)
            {
                double rand_weight = get_random_number(1, 10);
                g->add_edge(rand_weight, i, j);
            }

        }
    }

    return g;
}

void print_node_vector(vector<int>& nodes)
{
    for (int i : nodes)
    {
        cout << i << " ";
    }
}

/*
 *
 * Find the average path of a graph
 * by generating and calculating all
 * possible shortest paths
 *
 */

double average_path(graph* g)
{
    path_finder path_finder(g);

    vector<double> weights;

    // generate all possible pairs of nodes
    // and find the path between them

    for (int i = 0; i < g->node_count(); i++)
    {
        for (int j = i + 1; j < g->node_count(); j++)
        {
            auto path_result = path_finder.find_path(i, j);

            cout << "From " << i << " to " << j << " is ";

            if (path_result.first > 0)
            {
                cout << path_result.first << " -> ";

                print_node_vector(path_result.second);
            }
            else
            {
                cout << "none";
            }

            cout << endl;

            // we might get a -1 if there is no path
            // between the given nodes

            if (path_result.first > 0)
            {
                weights.push_back(path_result.first);
            }
        }
    }

    double average = accumulate(weights.begin(), weights.end(), 0.0) / weights.size();

    return average;
}

void find_average_path()
{
    const int num_nodes = 50;

    graph* g_20 = generate_graph(num_nodes, 20);
    cout << "Nodes: " << g_20->node_count() << " Edges: " << g_20->edge_count() << endl;
    double average_path_20 = average_path(g_20);
    cout << "Average path for density 20: " << average_path_20 << endl << endl;

    graph* g_40 = generate_graph(num_nodes, 40);
    cout << "Nodes: " << g_40->node_count() << " Edges: " << g_40->edge_count() << endl;
    double average_path_40 = average_path(g_40);
    cout << "Average path for density 40: " << average_path_40 << endl;
}

void build_graph_from_file(graph* g)
{
    ifstream mst_file("mst_data.txt");
    istream_iterator<string> start(mst_file), end;
    vector<string> words(start, end);

    int start_node = -1, end_node = -1;
    double weight = -1;

    for (auto it = words.begin() + 1; it != words.end(); it++)
    {
        if (start_node == -1)
        {
            start_node = stoi(*it);
            continue;
        }

        if (end_node == -1)
        {
            end_node = stoi(*it);
            continue;
        }

        if (weight == -1)
        {
            weight = stod(*it);
        }

        if (start_node != -1
                && end_node != -1
                && weight != -1)
        {
            g->add_edge(weight, start_node, end_node);

            start_node = -1, end_node = -1;
            weight = -1;
        }

    }
}

void find_mst(graph* g)
{
    build_graph_from_file(g);

    mst_finder mst(g);

    auto result = mst.find_mst();

    cout << "MST Weight: " << result.first << endl;

    cout << "Node sequence -> ";
    print_node_vector(result.second);
    cout << endl;
}

int main()
{    
    graph* g = new graph();
    build_graph_from_file(g);

    find_mst(g);
    return 0;
}
