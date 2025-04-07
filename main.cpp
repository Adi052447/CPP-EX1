#include <iostream>
#include "graph.hpp"       // כולל את המחלקה Graph
#include "algorithms.hpp"  // כולל את האלגוריתמים BFS, DFS, וכו'

using namespace graph;

/**
 * @brief פונקציה פשוטה להדפסת כותרת מודגשת כדי להפריד בין פלטי האלגוריתמים
 */
void printSectionTitle(const std::string& section) {
    std::cout << "\n=== " << section << " ===\n";
}

int main() {
    // נבנה גרף בעל 6 צמתים
    Graph g(6);

    // נוסיף קשתות (לא מכוון) עם משקלים שונים
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 4);
    g.addEdge(4, 5, 2);
    g.addEdge(1, 5, 10);

    printSectionTitle("Original Graph");
    g.print_graph();

    // BFS החל מהצומת 0
    Graph bfsTree = Algorithms::BFS(g, 0);
    printSectionTitle("BFS Tree (start=0)");
    bfsTree.print_graph();

    // DFS החל מהצומת 0
    Graph dfsTree = Algorithms::DFS(g, 0);
    printSectionTitle("DFS Tree (start=0)");
    dfsTree.print_graph();

    // Dijkstra החל מהצומת 2
    Graph dijkstraResult = Algorithms::dijkstra(g, 2);
    printSectionTitle("Dijkstra Tree (start=2)");
    dijkstraResult.print_graph();

    // Prim לחישוב MST (נניח שמתחיל מצומת 0 בפנים)
    Graph primMST = Algorithms::prim(g);
    printSectionTitle("Prim MST");
    primMST.print_graph();

    // Kruskal לחישוב MST
    Graph kruskalMST = Algorithms::kruskal(g);
    printSectionTitle("Kruskal MST");
    kruskalMST.print_graph();

    return 0;
}
