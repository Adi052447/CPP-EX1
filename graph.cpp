//adi.gamzu@msmail.ariel.ac.il

#include "graph.hpp"

namespace graph {

    Graph::Graph(int vertices)
        : numVertices(vertices)
    {
        this->adjList = new Node*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjList[i] = nullptr;
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < numVertices; i++) {
            Node* current = adjList[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;
    }

    int Graph::getNumVertices() {
        return this->numVertices;
    }

    Node** Graph::getAdjList() {
        return this->adjList;
    }

    void Graph::print_graph() {
        std::cout << "Graph adjacency list: \n";
        for (int i = 0; i < this->numVertices; i++) {
            std::cout << i << " ---> ";
            Node* temp = adjList[i];
            while (temp != nullptr) {
                std::cout << "(" << temp->vertex 
                          << ", weight = " << temp->weight << ") ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }

    void Graph::addEdge(int src, int dst, int weight) {
        if (src < 0 || src >= numVertices || dst < 0 || dst >= numVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }

        // הוספה מרשימה של src
        Node* edge1 = new Node(dst, weight);
        edge1->next = adjList[src];
        adjList[src] = edge1;

        // הוספה מרשימה של dst (לגרף לא מכוון)
        Node* edge2 = new Node(src, weight);
        edge2->next = adjList[dst];
        adjList[dst] = edge2;
    }

    void Graph::removeEdge(int src, int dst) {
        if (src < 0 || src >= numVertices || dst < 0 || dst >= numVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }

        bool found = false;

        // מחיקה מתוך רשימת src
        Node* curr = adjList[src];
        Node* prev = nullptr;

        while (curr != nullptr && curr->vertex != dst) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != nullptr) {
            found = true;
            if (prev == nullptr) {
                // אם האלמנט למחיקה היה בראש הרשימה
                adjList[src] = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
        }

        // מחיקה מתוך רשימת dst (לגרף לא מכוון)
        curr = adjList[dst];
        prev = nullptr;

        while (curr != nullptr && curr->vertex != src) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != nullptr) {
            if (prev == nullptr) {
                adjList[dst] = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
        }

        if (!found) {
            throw std::runtime_error("Edge does not exist.");
        }
    }

    void Graph::addDirectedEdge(int src, int dst, int weight) {
        if (src < 0 || src >= numVertices || dst < 0 || dst >= numVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        Node* edge = new Node(dst, weight);
        edge->next = adjList[src];
        adjList[src] = edge;
    }

    

} // namespace graph
