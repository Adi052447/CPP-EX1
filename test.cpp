//adi.gamzu@msmail.ariel.ac.il


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"

#include "data_structures.hpp" // Stack, Queue, PriorityQueue, UnionFind
#include "graph.hpp"           // Graph class
#include "algorithms.hpp"      // BFS, DFS, Dijkstra, Prim, Kruskal
#include <stdexcept>         // לזריקת חריגות
#include <climits>           // לשימוש בINT_MAX (אם קיים)
#include <iostream>          // במידה ונרצה debug prints

using namespace graph;

//==========================================================================================
// כאן בקובץ אנחנו מריצים סדרה של TEST_CASE-ים דרך ספריית doctest
// כל TEST_CASE בודק פונקציונליות אחרת (מבני נתונים, פונקציות הגרף, אלגוריתמים, וכו').
// במקרים רבים, אנחנו גם בודקים מקרי קצה (Edge Cases) וחריגות (כגון std::out_of_range).
//==========================================================================================

// ============================
//     TESTS: DATA STRUCTURES
// ============================

TEST_CASE("Stack: Basic functionality") {
    // כאן נבדוק פונקציות בסיסיות של Stack: push, pop, peek, overflow.
    Stack s(3);
    CHECK(s.isEmpty() == true);

    s.push(10);
    s.push(20);
    CHECK(s.isEmpty() == false);

    CHECK(s.peek() == 20);
    CHECK(s.pop() == 20);
    CHECK(s.peek() == 10);
    CHECK(s.pop() == 10);

    // After popping everything
    CHECK(s.isEmpty() == true);

    // Test overflow
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK_THROWS_AS(s.push(4), std::overflow_error); // Stack is full
}

TEST_CASE("Stack: Edge case - capacity 0") {
    // מחסנית עם קיבולת 0: כל push אמור להיכשל באופן מיידי.
    Stack s0(0);
    CHECK(s0.isEmpty() == true);
    // כל push אמור להיכשל כי הקיבולת היא 0
    CHECK_THROWS_AS(s0.push(1), std::overflow_error);
    // pop צריך גם לזרוק שגיאה
    CHECK_THROWS_AS(s0.pop(), std::underflow_error);
}

TEST_CASE("Queue: Basic functionality") {
    // בדיקה בסיסית של Queue: enqueue, dequeue, overflow ו-underflow.
    Queue q(3);
    CHECK(q.isEmpty() == true);

    // Enqueue
    q.enqueue(11);
    q.enqueue(22);
    CHECK(q.isEmpty() == false);

    // Dequeue
    CHECK(q.dequeue() == 11);
    CHECK(q.dequeue() == 22);
    CHECK(q.isEmpty() == true);

    // Test underflow
    CHECK_THROWS_AS(q.dequeue(), std::underflow_error); // Queue is empty

    // Test overflow
    q.enqueue(33);
    q.enqueue(44);
    q.enqueue(55);
    CHECK_THROWS_AS(q.enqueue(66), std::overflow_error);
}

TEST_CASE("Queue: Edge case - capacity 0") {
    // תור עם קיבולת 0: אין אפשרות להכניס או להוציא אף איבר.
    Queue q0(0);
    CHECK(q0.isEmpty() == true);
    CHECK_THROWS_AS(q0.enqueue(1), std::overflow_error);
    CHECK_THROWS_AS(q0.dequeue(), std::underflow_error);
}

TEST_CASE("PriorityQueue: Basic functionality") {
    // בדיקה של insert, extractMin, decreaseKey, ועוד.
    PriorityQueue pq(4);
    CHECK(pq.isEmpty() == true);

    // Insert
    pq.insert(0, 10); 
    pq.insert(1, 5);
    pq.insert(2, 20);
    CHECK(pq.isEmpty() == false);

    // extractMin (צריך להוציא קודם את 1, כי priority=5 הכי קטנה)
    CHECK(pq.extractMin() == 1);

    // decreaseKey
    pq.decreaseKey(2, 1); // משנה את ה-priority של 2 ל-1
    CHECK(pq.extractMin() == 2);

    // מוציא את הנותר
    CHECK(pq.extractMin() == 0);
    CHECK(pq.isEmpty() == true);

    // extractMin מכאן אמור להחזיר INT_MAX (או 2147483647) כיוון שהוא ריק
    CHECK(pq.extractMin() == 2147483647);
}

TEST_CASE("PriorityQueue: Overflow edge case") {
    // אם תור העדיפויות מלא, המימוש הנוכחי פשוט מדפיס הודעה ולא זורק חריגה.
    PriorityQueue pq(2);
    pq.insert(5, 5);
    pq.insert(10, 10);
    // הכנסה נוספת כבר "מלאה"
    CHECK_NOTHROW(pq.insert(20, 20)); // מדפיס "Priority Queue is full."
}

TEST_CASE("UnionFind: Basic functionality") {
    // בדיקה של find ו-unite + reset במבנה האיחוד-חיפוש.
    UnionFind uf(5);
    // התחלה: כל צומת הוא הנציג של עצמו
    for (int i = 0; i < 5; i++) {
        CHECK(uf.find(i) == i);
    }
    
    uf.unite(0, 1);
    uf.unite(2, 3);

    // 0 ו-1 באותה קבוצה
    CHECK(uf.find(0) == uf.find(1));
    // 2 ו-3 באותה קבוצה
    CHECK(uf.find(2) == uf.find(3));
    // 4 עדיין קבוצה נפרדת
    CHECK(uf.find(4) == 4);

    // איחוד של 1 עם 3 גורם לכך ש-0,1,2,3 כולם באותה קבוצה
    uf.unite(1, 3);
    CHECK(uf.find(0) == uf.find(2));
    CHECK(uf.find(3) == uf.find(1));

    uf.reset();
    for (int i = 0; i < 5; i++) {
        CHECK(uf.find(i) == i);
    }
}

TEST_CASE("UnionFind: Edge case - size=0") {
    // אין אלמנטים כלל
    UnionFind uf0(0);
    // בקריאה ל-find(0) עשוי להיות undefined, אז רק נבדוק שלא קורס
    CHECK_NOTHROW(uf0.reset());
}

// ============================
//     TESTS FOR GRAPH CLASS
// ============================

TEST_CASE("Graph: add/remove edges") {
    // בדיקות הוספה והסרה של קשתות, כולל חריגות למקרים שונים.
    Graph g(5);

    // הוספת קשת בסיסית
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    // הסרת קשת תקינה
    CHECK_NOTHROW(g.removeEdge(0, 1));
    // הסרה שנייה של אותה קשת - אמור לזרוק חריגה
    CHECK_THROWS_AS(g.removeEdge(0, 1), std::runtime_error);

    // הוספת קשת על אינדקס לא תקין
    CHECK_THROWS_AS(g.addEdge(-1, 2, 3), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(10, 2, 3), std::out_of_range);

    // הסרה על אינדקס לא תקין
    CHECK_THROWS_AS(g.removeEdge(1, 9), std::out_of_range);
}

TEST_CASE("Graph: addDirectedEdge test") {
    // בדיקת קשת מכוונת + חריגות על אינדקסים לא תקינים.
    Graph g(3);
    CHECK_NOTHROW(g.addDirectedEdge(0, 1, 2));

    // הוספת קשת לא חוקית
    CHECK_THROWS_AS(g.addDirectedEdge(-1, 2, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addDirectedEdge(0, 5, 1), std::out_of_range);
}

TEST_CASE("Graph: Edge cases - single vertex, no edges") {
    // גרף עם צומת אחד בלבד
    Graph single(1);
    CHECK(single.getNumVertices() == 1);
    // ניסיונות להוסיף קשת שאמורה לזרוק חריגה
    CHECK_THROWS_AS(single.addEdge(0, 1, 1), std::out_of_range);
    // וידוא שאין קריסה בהדפסה
    CHECK_NOTHROW(single.print_graph());
    
    // הסרה עם אינדקס לא תקין
    CHECK_THROWS_AS(single.removeEdge(0, 0), std::runtime_error);
}

TEST_CASE("Graph: Edge cases - zero vertices") {
    // graph(0) -> ללא צמתים כלל.
    Graph emptyGraph(0);
    CHECK(emptyGraph.getNumVertices() == 0);
    // בדיקת הדפסה שלא קורסת
    CHECK_NOTHROW(emptyGraph.print_graph());
    // כל addEdge אמור לזרוק חריגה
    CHECK_THROWS_AS(emptyGraph.addEdge(0, 0, 1), std::out_of_range);
}

// ============================
//   TESTS FOR ALGORITHMS (BFS, DFS, Dijkstra, Prim, Kruskal)
// ============================

TEST_CASE("BFS: Basic correctness + out_of_range") {
    // נבדוק גם חריגות וגם שהתוצאות נכונות (0->1, 0->2, 1->3).
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);

    // בדיקת חריגה
    CHECK_THROWS_AS(Algorithms::BFS(g, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::BFS(g, 10), std::out_of_range);

    // BFS מ-0
    Graph bfsTree = Algorithms::BFS(g, 0);
    // אמורות להיות קשתות 0->1, 0->2, 1->3
    Node** treeAdj = bfsTree.getAdjList();

    bool found01 = false, found02 = false;
    Node* c = treeAdj[0];
    while (c) {
        if (c->vertex == 1) found01 = true;
        if (c->vertex == 2) found02 = true;
        c = c->next;
    }
    CHECK(found01 == true);
    CHECK(found02 == true);

    bool found13 = false;
    c = treeAdj[1];
    while (c) {
        if (c->vertex == 3) found13 = true;
        c = c->next;
    }
    CHECK(found13 == true);
}

TEST_CASE("BFS: Edge case - disconnected graph") {
    // גרף מנותק: שני רכיבים, נתחיל BFS מ-0.
    Graph dg(4);
    dg.addEdge(0, 1, 5);
    dg.addEdge(2, 3, 5);

    // BFS מ-0 יראה רק את 0->1
    Graph bfsTree = Algorithms::BFS(dg, 0);

    // נבדוק שלעץ BFS יש רק קשת אחת: 0->1
    int edgeCount = 0;
    Node** adjList = bfsTree.getAdjList();
    for (int i = 0; i < 4; i++) {
        Node* tmp = adjList[i];
        while (tmp) {
            edgeCount++;
            tmp = tmp->next;
        }
    }
    CHECK(edgeCount == 1); // 0->1 בלבד
}

TEST_CASE("DFS: Basic correctness + out_of_range") {
    // בדיקה שה-DFS עובר על הצמתים כנדרש, פלוס בדיקת out_of_range.
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);

    CHECK_THROWS_AS(Algorithms::DFS(g, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::DFS(g, 4), std::out_of_range);

    // DFS מ-0 (עץ מכוון אמור להכיל 3 קשתות בסופו)
    Graph dfsTree = Algorithms::DFS(g, 0);
    int edgeCount = 0;
    Node** adj = dfsTree.getAdjList();
    for (int i = 0; i < 4; i++) {
        Node* cur = adj[i];
        while (cur != nullptr) {
            edgeCount++;
            cur = cur->next;
        }
    }
    CHECK(edgeCount == 3);
}

TEST_CASE("DFS: Edge case - single vertex graph") {
    // גרף עם צומת אחד; אין קשתות כלל.
    Graph single(1);
    Graph dfsTree = Algorithms::DFS(single, 0);

    // לא אמורות להיות קשתות
    int edges = 0;
    Node** adj = dfsTree.getAdjList();
    for (int i = 0; i < single.getNumVertices(); i++) {
        Node* tmp = adj[i];
        while (tmp) {
            edges++;
            tmp = tmp->next;
        }
    }
    CHECK(edges == 0);
}

TEST_CASE("Dijkstra: small graph") {
    // גרף עם 5 צמתים, בודקים שהאלגוריתם יוצר עץ פורש של 4 קשתות.
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 3);
    g.addEdge(2, 1, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 7);

    CHECK_THROWS_AS(Algorithms::dijkstra(g, -1), std::out_of_range);
    Graph spTree = Algorithms::dijkstra(g, 0);

    // עץ פורש מכוון צפוי עם 4 קשתות.
    int edgeCounter = 0;
    Node** adj = spTree.getAdjList();
    for (int i = 0; i < 5; i++) {
        Node* c = adj[i];
        while (c) {
            edgeCounter++;
            c = c->next;
        }
    }
    CHECK(edgeCounter == 4);
}

TEST_CASE("Dijkstra: disconnected graph edge case") {
    // גרף מנותק: (0,1) ו(2,3), מפעילים דייקסטרה מ-0.
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);

    Graph djTree = Algorithms::dijkstra(g, 0);

    // לצמתים 2 ו-3 אין דרך מ-0, אז אין קשתות שמגיעות אליהם.
    int countEdges = 0;
    Node** adj = djTree.getAdjList();
    for (int i = 0; i < 4; i++) {
        Node* tmp = adj[i];
        while (tmp) {
            countEdges++;
            tmp = tmp->next;
        }
    }
    CHECK(countEdges == 1); // רק 0->1
}

TEST_CASE("Prim: basic MST test") {
    // גרף קטן, בדיקה שהאלגוריתם פרים מניב עץ עם 4 קשתות (5 צמתים).
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);

    Graph mst = Algorithms::prim(g);

    // MST של 5 צמתים -> 4 קשתות, בגרף לא מכוון כל קשת נספרת פעמיים.
    int countEdges = 0;
    Node** adj2 = mst.getAdjList();
    for (int i = 0; i < 5; i++) {
        Node* c = adj2[i];
        while (c) {
            countEdges++;
            c = c->next;
        }
    }
    CHECK(countEdges == 8);
}

TEST_CASE("Prim: disconnected graph edge case") {
    // גרף עם שתי קומפוננטות, פרים לרוב מכסה רק את הרכיב של הצומת ההתחלתי.
    Graph g(5);
    g.addEdge(0, 1, 5);
    g.addEdge(2, 3, 6);

    Graph mst = Algorithms::prim(g);

    // נקבל כנראה רק קשת אחת 0-1; 2,3,4 לא מקושרים.
    int countEdges = 0;
    Node** adj2 = mst.getAdjList();
    for (int i = 0; i < 5; i++) {
        Node* tmp = adj2[i];
        while (tmp) {
            countEdges++;
            tmp = tmp->next;
        }
    }
    CHECK(countEdges == 2); // קשת אחת נספרת פעמיים
}

TEST_CASE("Kruskal: basic MST test") {
    // בדיקה פשוטה: 4 צמתים, MST אמור להכיל 3 קשתות.
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(0, 3, 10);

    Graph mst = Algorithms::kruskal(g);

    int edgeCount = 0;
    Node** adj3 = mst.getAdjList();
    for (int i = 0; i < 4; i++) {
        Node* cur = adj3[i];
        while (cur) {
            edgeCount++;
            cur = cur->next;
        }
    }
    CHECK(edgeCount == 6); // 3 קשתות בגרף לא מכוון -> נספרות פעמיים
}

TEST_CASE("Kruskal: disconnected graph edge case") {
    // גרף עם 5 צמתים, שני רכיבים: (0-1) ו(2-3), והצומת 4 בודד.
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);

    Graph mst = Algorithms::kruskal(g);
    // נקבל 2 קשתות ב-MST (0-1, 2-3) כי 4 נפרד.
    int edgeCount = 0;
    Node** adj4 = mst.getAdjList();
    for (int i = 0; i < 5; i++) {
        Node* tmp = adj4[i];
        while (tmp) {
            edgeCount++;
            tmp = tmp->next;
        }
    }
    // 2 קשתות מוכפל ב-2 -> 4
    CHECK(edgeCount == 4);
}
