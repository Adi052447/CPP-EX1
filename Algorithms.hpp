//adi.gamzu@msmail.ariel.ac.il 


#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"           // נדרש עבור המחלקה Graph ו-Node
#include "data_structures.hpp" // נדרש עבור Queue, Stack, PriorityQueue, UnionFind

#include <stdexcept> // זריקת חריגות

namespace graph {

    /**
     * @brief מבנה עזר לייצוג קשת עבור Kruskal.
     */
    struct Edge {
        int src;
        int dst;
        int weight;
    };

    /**
     * @brief מחלקה סטטית/מרחב שמות המכילה את כל האלגוריתמים: BFS, DFS, Dijkstra, Prim, Kruskal.
     */
    class Algorithms {
    public:
        static Graph BFS(Graph& g, int start);
        static Graph DFS(Graph& g, int start);

        static Graph dijkstra(Graph& g, int start);
        static Graph prim(Graph& g);
        static Graph kruskal(Graph& g);

    private:
        // מתודה עזר לדייקסטרה
        static void relax(int u, int v, int weight, int* distances, int* parent, PriorityQueue& pq);
    };

} // namespace graph

#endif // ALGORITHMS_HPP
