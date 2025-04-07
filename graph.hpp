#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.hpp"  

#include <stdexcept>  // לצורך שימוש בחריגות

namespace graph {

    /**
     * @brief מבנה נתונים לייצוג קשת ברשימת השכנים (vertex + weight + מצביע).
     */
    struct Node {
        int vertex;
        int weight;
        Node* next;

        Node(int v, int w)
            : vertex(v), weight(w), next(nullptr) {}
    };

    /**
     * @brief מחלקה לייצוג גרף עם רשימת שכנים.
     */
    class Graph {
    private:
        int numVertices;
        Node** adjList; 

    public:
        /**
         * @brief בונה גרף בעל מספר צמתים נתון.
         */
        Graph(int vertices);

        /**
         * @brief הורס את הגרף ומשחרר את הזיכרון.
         */
        ~Graph();

        /**
         * @brief מחזיר את מספר הצמתים בגרף.
         */
        int getNumVertices();

        /**
         * @brief מחזיר את מערך רשימות השכנים (adjList).
         */
        Node** getAdjList();

        /**
         * @brief מוסיף קשת (undirected) בין שני צמתים עם משקל נתון (ברירת מחדל 1).
         */
        void addEdge(int src, int dst, int weight = 1);

        /**
         * @brief מסיר קשת (undirected) בין שני צמתים.
         */
        void removeEdge(int src, int dst);

        /**
         * @brief מוסיף קשת מכוונת (directed) מ-src ל-dst עם משקל נתון.
         */
        void addDirectedEdge(int src, int dst, int weight);

        /**
         * @brief מדפיס את רשימת השכנים של כל צומת.
         */
        void print_graph();
    };

} // namespace graph

#endif // GRAPH_H
