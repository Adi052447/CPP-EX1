//adi.gamzu@msmail.ariel.ac.il


#include "data_structures.hpp"
#include <stdexcept> // לצורך שימוש בחריגות

namespace graph {

    // ============================
    //         STACK
    // ============================
    Stack::Stack(int capacity) 
        : capacity(capacity), top(-1), size(0)
    {
        this->data = new int[capacity];
    }

    Stack::~Stack() {
        delete[] data;
    }

    void Stack::push(int vertex) {
        if (this->top >= this->capacity - 1) {
            throw std::overflow_error("Stack is full");
        }
        this->data[++top] = vertex;
        size++;
    }

    int Stack::pop() {
        if (top != -1) {
            size--;
            return this->data[top--];
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

    bool Stack::isEmpty() {
        return (this->size == 0);
    }

    int Stack::peek() {
        if (top != -1) {
            return this->data[top];
        } else {
            throw std::underflow_error("Stack is empty"); 
        }
    }

    // ============================
    //         QUEUE
    // ============================
    Queue::Queue(int capacity) 
        : capacity(capacity), front(0), rear(0), size(0)
    {
        this->data = new int[capacity];
    }

    Queue::~Queue() {
        delete[] data;
    }

    bool Queue::enqueue(int vertex) {
        if (size < capacity) {
            this->data[rear] = vertex;
            this->rear = (this->rear + 1) % this->capacity;
            this->size++;
            return true;
        } else {
            throw std::overflow_error("Queue is full");
        }
    }

    int Queue::dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        int firstVer = this->data[front];
        this->front = (this->front + 1) % this->capacity;
        this->size--;
        return firstVer;
    }

    bool Queue::isEmpty() {
        return (this->size == 0);
    }

    // ============================
    //     PRIORITY QUEUE
    // ============================
    PriorityQueue::PriorityQueue(int capacity)
        : capacity(capacity), size(0)
    {
        this->heap = new HeapNode[capacity];
    }

    PriorityQueue::~PriorityQueue() {
        delete[] heap;
    }

    void PriorityQueue::insert(int vertex, int priority) {
        if (size == capacity) {
            std::cout << "Priority Queue is full." << std::endl;
            return;
        }
        heap[size] = {vertex, priority};
        heapifyUp(size);
        size++;
    }

    int PriorityQueue::extractMin() {
        if (isEmpty()) {
            std::cout << "Priority Queue is empty." << std::endl;
            return 2147483647; // INT_MAX
        }
        int minVertex = heap[0].vertex;
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return minVertex;
    }

    void PriorityQueue::decreaseKey(int vertex, int newPriority) {
        for (int i = 0; i < size; i++) {
            if (heap[i].vertex == vertex) {
                if (newPriority < heap[i].priority) {
                    heap[i].priority = newPriority;
                    heapifyUp(i);
                }
                break;
            }
        }
    }

    bool PriorityQueue::isEmpty() {
        return (size == 0);
    }

    void PriorityQueue::heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].priority <= heap[index].priority) {
                break;
            }
            std::swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void PriorityQueue::heapifyDown(int index) {
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left].priority < heap[smallest].priority) {
                smallest = left;
            }
            if (right < size && heap[right].priority < heap[smallest].priority) {
                smallest = right;
            }
            if (smallest == index) {
                break;
            }
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

    // ============================
    //         UNION-FIND
    // ============================
    UnionFind::UnionFind(int size) : size(size) {
        parent = new int[size];
        rank = new int[size];
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    UnionFind::~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void UnionFind::unite(int u, int v) {
        int uRoot = find(u);
        int vRoot = find(v);

        if (uRoot == vRoot)
            return;

        if (rank[uRoot] < rank[vRoot]) {
            parent[uRoot] = vRoot;
        } else if (rank[uRoot] > rank[vRoot]) {
            parent[vRoot] = uRoot;
        } else {
            parent[vRoot] = uRoot;
            rank[uRoot]++;
        }
    }

    void UnionFind::reset() {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

} // namespace graph
