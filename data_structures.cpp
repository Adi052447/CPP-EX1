//adi.gamzu@msmail.ariel.ac.il 

#include "data_structures.hpp"
#include <stdexcept> // לשימוש בחריגות std::overflow_error, std::underflow_error
#include <iostream>  // לשימוש בהדפסות בתור העדיפויות (PriorityQueue)

namespace graph {

//
//  UNION-FIND SECTION (קודם)
//
UnionFind::UnionFind(int elementsCount) : size(elementsCount) {
    // מקצים מערכים parent ו-rank לכל האיברים
    parent = new int[size];
    rank   = new int[size];
    for (int i = 0; i < size; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int node) {
    // מימוש Path Compression
    if (parent[node] != node) {
        parent[node] = find(parent[node]);
    }
    return parent[node];
}

void UnionFind::unite(int u, int v) {
    // מוצאים את הנציגים של u ו-v
    int rootU = find(u);
    int rootV = find(v);

    if (rootU == rootV) {
        // כבר באותה קבוצה, אין צורך לאחד
        return;
    }

    // Union by rank
    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

void UnionFind::reset() {
    // מאתחל את כל האיברים כך שכל אינדקס הוא ההורה של עצמו
    for (int i = 0; i < size; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

//
//  STACK SECTION
//
Stack::Stack(int maxCapacity)
    : capacity(maxCapacity), top(-1), size(0)
{
    // מקצה מערך שלם (int) לפי הקיבולת
    data = new int[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(int value) {
    // אם אין מקום נוסף, נזרוק חריגה
    if (top >= capacity - 1) {
        throw std::overflow_error("Stack is full");
    }
    // מעלים את top ומציבים את האיבר
    data[++top] = value;
    size++;
}

int Stack::pop() {
    if (top == -1) {
        throw std::underflow_error("Stack is empty");
    }
    size--;
    return data[top--];
}

bool Stack::isEmpty() {
    // המחסנית ריקה אם size==0
    return (size == 0);
}

int Stack::peek() {
    if (top == -1) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top];
}

//
//  QUEUE SECTION
//
Queue::Queue(int maxCap)
    : capacity(maxCap), front(0), rear(0), size(0)
{
    // מקצה מערך לשמירת איברי התור
    data = new int[capacity];
}

Queue::~Queue() {
    delete[] data;
}

bool Queue::enqueue(int value) {
    // בודקים אם התור מלא
    if (size >= capacity) {
        throw std::overflow_error("Queue is full");
    }
    data[rear] = value;
    rear = (rear + 1) % capacity;
    size++;
    return true;
}

int Queue::dequeue() {
    // אם אין איברים, נזרוק underflow
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    int result = data[front];
    front = (front + 1) % capacity;
    size--;
    return result;
}

bool Queue::isEmpty() {
    return (size == 0);
}

//
//  PRIORITY QUEUE SECTION
//
PriorityQueue::PriorityQueue(int maxCap)
    : capacity(maxCap), size(0)
{
    heap = new HeapNode[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

void PriorityQueue::insert(int vertex, int priority) {
    // אם אין מקום, רק נדפיס - במימוש הנוכחי לא נזרקת חריגה
    if (size == capacity) {
        std::cout << "Priority Queue is full." << std::endl;
        return;
    }
    // מכניסים את הצומת והעדיפות בסוף
    heap[size] = { vertex, priority };
    heapifyUp(size);
    size++;
}

int PriorityQueue::extractMin() {
    // אם ריק, נדפיס ונחזיר ערך שמייצג \"אין\" (למשל INT_MAX)
    if (isEmpty()) {
        std::cout << "Priority Queue is empty." << std::endl;
        return 2147483647;
    }
    // לוקחים את 'המינימום' (ראש הערמה)
    int minVertex = heap[0].vertex;
    // מעבירים את האחרון לראש ומקטינים size
    heap[0] = heap[size - 1];
    size--;
    // משחזרים את תכונות הערימה
    heapifyDown(0);
    return minVertex;
}

void PriorityQueue::decreaseKey(int vertex, int newPriority) {
    // מחפשים את ה-vertex המבוקש
    for (int i = 0; i < size; i++) {
        if (heap[i].vertex == vertex) {
            // אם מצאנו, ונקבעה עדיפות חדשה יותר טובה (נמוכה),
            // נעדכן ונבצע heapifyUp על המיקום.
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

// פונקציית עזר לעלייה כלפי מעלה בערימה
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        // אם העדיפות של האב כבר קטנה/שווה, נעצור
        if (heap[parentIndex].priority <= heap[index].priority) {
            break;
        }
        // אחרת נחליף את האיבר הנוכחי עם האב
        std::swap(heap[parentIndex], heap[index]);
        index = parentIndex;
    }
}

// פונקציית עזר לירידה כלפי מטה בערימה
void PriorityQueue::heapifyDown(int index) {
    // כל עוד יש בן שמאלי
    while ((2 * index + 1) < size) {
        int left  = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if ((left < size) && (heap[left].priority < heap[smallest].priority)) {
            smallest = left;
        }
        if ((right < size) && (heap[right].priority < heap[smallest].priority)) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

} // namespace graph
