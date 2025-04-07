#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>

/**
 * @brief מרחב השמות graph מכיל את כל מבני הנתונים והגרף.
 */
namespace graph {

    // ============================
    //         STACK
    // ============================
    class Stack {
    private:
        int* data;
        int capacity;
        int top;
        int size;

    public:
        /**
         * @brief בונה מחסנית עם קיבולת נתונה.
         */
        Stack(int capacity);

        /**
         * @brief מפרק את המחסנית ומפנה את הזיכרון.
         */
        ~Stack();

        /**
         * @brief מכניס איבר לראש המחסנית.
         */
        void push(int vertex);

        /**
         * @brief מוציא ומחזיר את האיבר מראש המחסנית.
         */
        int pop();

        /**
         * @brief מחזיר האם המחסנית ריקה.
         */
        bool isEmpty();

        /**
         * @brief מציץ לראש המחסנית ללא הוצאת האיבר.
         */
        int peek();
    };

    // ============================
    //         QUEUE
    // ============================
    class Queue {
    private:
        int* data;
        int capacity;
        int front;
        int rear;
        int size;

    public:
        /**
         * @brief בונה תור עם קיבולת נתונה.
         */
        Queue(int capacity);

        /**
         * @brief מפרק את התור ומפנה את הזיכרון.
         */
        ~Queue();

        /**
         * @brief מכניס איבר לסוף התור (enqueue).
         */
        bool enqueue(int vertex);

        /**
         * @brief מוציא ומחזיר את האיבר מראש התור (dequeue).
         */
        int dequeue();

        /**
         * @brief מחזיר האם התור ריק.
         */
        bool isEmpty();
    };

    // ============================
    //     PRIORITY QUEUE
    // ============================
    struct HeapNode {
        int vertex;
        int priority;
    };

    class PriorityQueue {
    private:
        HeapNode* heap;
        int capacity;
        int size;

        void heapifyUp(int index);
        void heapifyDown(int index);

    public:
        /**
         * @brief בונה תור עדיפויות עם קיבולת נתונה.
         */
        PriorityQueue(int capacity);

        /**
         * @brief מפרק את תור העדיפויות ומפנה את הזיכרון.
         */
        ~PriorityQueue();

        /**
         * @brief מכניס איבר (vertex) עם עדיפות (priority).
         */
        void insert(int vertex, int priority);

        /**
         * @brief מחלץ ומחזיר את האיבר עם העדיפות הגבוהה ביותר (עדיפות=מספר קטן יותר).
         */
        int extractMin();

        /**
         * @brief משנה עדיפות של איבר קיים לקטנה יותר (משמש באלגוריתמים של דייקסטרה/פרים).
         */
        void decreaseKey(int vertex, int newPriority);

        /**
         * @brief מחזיר האם התור ריק.
         */
        bool isEmpty();
    };

    // ============================
    //     UNION-FIND (DSU)
    // ============================
    class UnionFind {
    private:
        int* parent;
        int* rank;
        int size;

    public:
        /**
         * @brief בונה איחוד-חיפוש עם כמות איברים נתונה.
         */
        UnionFind(int size);

        /**
         * @brief הורסת את מבנה האיחוד-חיפוש ומפנה זיכרון.
         */
        ~UnionFind();

        /**
         * @brief מחזיר את הנציג של הקבוצה בה נמצא node.
         */
        int find(int node);

        /**
         * @brief מאחד את הקבוצות בהן נמצאים u ו-v.
         */
        void unite(int u, int v);

        /**
         * @brief מאתחל מחדש את המבנה כך שכל איבר יהיה מייצג של עצמו.
         */
        void reset();
    };

} // namespace graph

#endif // DATA_STRUCTURES_H
