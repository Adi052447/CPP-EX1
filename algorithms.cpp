//adi.gamzu@msmail.ariel.ac.il

#include "algorithms.hpp"
#include <climits>    // לשימוש ב-INT_MAX במקום 2147483647 במידת הצורך
#include <stdexcept>  // לזריקת חריגות
#include <iostream>   // במידה ונרצה להדפיס

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

namespace graph {

    // ============================
    //         BFS SECTION
    // ============================
    /**
     * @brief מבצע מעבר (traversal) בשיטת חיפוש לרוחב (Breadth-First Search)
     *        ומחזיר גרף חדש שמייצג את עץ ה-BFS: לכל צומת ששייך למעבר,
     *        תהיה קשת מכוונת מהורה לילד כפי שנגלה בשיטת BFS.
     * 
     * @param g גרף הקלט (לאו דווקא מכוון).
     * @param start הצומת שממנו מתחילים את המעבר.
     * @return Graph גרף חדש שבו קיימות רק הקשתות שמרכיבות את עץ ה-BFS.
     */
    Graph Algorithms::BFS(Graph& g, int start) {
        // בדיקה שהצומת ההתחלתי חוקי
        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Invalid start vertex in BFS");
        }

        // ניצור גרף חדש באותו גודל, שישמש כעץ ה-BFS
        Graph bfsTree(g.getNumVertices());

        // מערך visited: ייסמן עבור כל צומת אם ביקרנו בו או לא
        bool* visited = new bool[g.getNumVertices()];
        for (int i = 0; i < g.getNumVertices(); ++i) {
            visited[i] = false;
        }

        // משתמשים בתור (Queue) לניהול הצמתים בתור ה-FIFO
        Queue queue(g.getNumVertices());

        // מסמנים את הצומת ההתחלתי כ"ביקרנו" ודוחפים אותו לתור
        visited[start] = true;
        queue.enqueue(start);

        // ניקח מצביע לרשימת השכנים של הגרף המקורי
        Node** originalAdj = g.getAdjList();

        // כל עוד התור לא ריק, נשלוף צומת ונעבור על שכניו
        while (!queue.isEmpty()) {
            int current = queue.dequeue();
            Node* neighbor = originalAdj[current];

            // עוברים על כל השכנים של הצומת הנוכחי
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                // אם עוד לא ביקרנו ב-v
                if (!visited[v]) {
                    visited[v] = true;
                    // מוסיפים קשת מכוונת ל-tree מ-current ל-v
                    bfsTree.addDirectedEdge(current, v, neighbor->weight);
                    // דוחפים את v לתור כדי לעבד גם אותו
                    queue.enqueue(v);
                }
                neighbor = neighbor->next;
            }
        }

        // שחרור הזיכרון של מערך visited
        delete[] visited;

        return bfsTree;
    }

    // ============================
    //         DFS SECTION
    // ============================
    /**
     * @brief מבצע מעבר בשיטת חיפוש לעומק (Depth-First Search) על גרף,
     *        ומחזיר גרף חדש שמייצג את עץ ה-DFS (כאן מוספים קשת מכוונת מהורה לילד).
     * 
     * @param g גרף הקלט.
     * @param start צומת ההתחלה של ה-DFS.
     * @return Graph גרף חדש שבו קיימות הקשתות של עץ ה-DFS.
     */
    Graph Algorithms::DFS(Graph& g, int start) {
        // בדיקה שהצומת חוקי
        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Invalid start vertex in DFS");
        }

        int n = g.getNumVertices();
        
        // גרף חדש לאחסון תוצאות ה-DFS
        Graph dfsTree(n);

        // מערך ביקור
        bool* visited = new bool[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }

        // מחסנית (Stack)
        Stack stack(n);
        stack.push(start);
        visited[start] = true;

        // מצביע לרשימת השכנים של הגרף
        Node** originalAdj = g.getAdjList();

        // לולאת DFS (ללא רקורסיה)
        while (!stack.isEmpty()) {
            int current = stack.pop();
            Node* neighbor = originalAdj[current];

            // נעבור על השכנים של current
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                // אם עוד לא בקרנו בצומת v
                if (!visited[v]) {
                    visited[v] = true;
                    // עץ ה-DFS: מוסיפים קשת מכוונת current -> v
                    dfsTree.addDirectedEdge(current, v, neighbor->weight);
                    stack.push(v);
                }
                neighbor = neighbor->next;
            }
        }

        delete[] visited;
        return dfsTree;
    }

    // ============================
    //       DIJKSTRA SECTION
    // ============================

    /**
     * @brief פונקציית עזר לדייקסטרה: מבצעת "הקלה" (relax) על הקשת (u->v) בעלת משקל weight.
     *        אם מצאנו דרך קצרה יותר להגיע ל-v דרך u, נעדכן את המרחק ואת ההורה, ונדחוף ל-Queue העדיפויות.
     * 
     * @param u הצומת הנוכחי
     * @param v צומת שכן של u
     * @param weight משקל הקשת (u->v)
     * @param distances מערך מרחקים מהמקור לכל צומת
     * @param parent מערך הורים – בו נשמר מאיזה צומת הגענו למינימום מרחק
     * @param pq תור עדיפויות לבחירת הצומת עם המרחק הקטן ביותר בכל שלב
     */
    void Algorithms::relax(int u, int v, int weight, int* distances, int* parent, PriorityQueue& pq) {
        // אם הדרך דרך u משפרת את המרחק ל-v, נעדכן
        if (distances[u] + weight < distances[v]) {
            distances[v] = distances[u] + weight;
            parent[v] = u;
            // מכניסים (או מעדכנים) את הצומת v בתור העדיפויות
            pq.insert(v, distances[v]);
        }
    }

    /**
     * @brief אלגוריתם דייקסטרה לחישוב מסלולים קצרים מצומת התחלתי אחד לכל שאר הצמתים.
     *        מחזיר גרף מכוון המייצג את "עץ המסלולים הקצרים" (Shortest Paths Tree).
     * 
     * @param g גרף הקלט (משקלים לא-שליליים).
     * @param start צומת ההתחלה.
     * @return Graph עץ המסלולים הקצרים (מכוון), שבו קשתות מצביעות מהורה לילד.
     */
    Graph Algorithms::dijkstra(Graph& g, int start) {
        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Invalid start vertex in Dijkstra");
        }
        int n = g.getNumVertices();

        // הקצאת מערכים
        int* dist = new int[n];     // מרחק מינימלי מהצומת ההתחלתי
        int* parent = new int[n];   // עוקב מי "הורה" של כל צומת
        bool* visited = new bool[n]; // סמן אם כבר "ננעל" הצומת

        // אתחול ערכי ברירת מחדל
        for (int i = 0; i < n; i++) {
            dist[i] = INT_MAX;  
            parent[i] = -1;
            visited[i] = false;
        }
        // המרחק לצומת ההתחלה הוא 0
        dist[start] = 0;

        // תור עדיפויות למימוש האלגוריתם – המפתח הוא ערך המרחק
        PriorityQueue pq(n);
        pq.insert(start, 0);

        // כל עוד יש צמתים בתור העדיפויות
        while (!pq.isEmpty()) {
            // מוציאים את הצומת עם המרחק הקטן ביותר
            int u = pq.extractMin();
            
            // אם כבר ביקרנו בצומת זה, נדלג
            if (visited[u]) {
                continue;
            }
            visited[u] = true;

            // עבור כל שכן של u, ננסה לבצע relax
            Node* neighbor = g.getAdjList()[u];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                relax(u, v, neighbor->weight, dist, parent, pq);
                neighbor = neighbor->next;
            }
        }

        // יוצרים גרף חדש שמייצג את עץ המסלולים הקצרים
        Graph shortestPathsTree(n);
        for (int i = 0; i < n; i++) {
            // אם יש הורה, ניצור קשת מהורה לילד
            if (parent[i] != -1) {
                // נחשב את המשקל = dist[child] - dist[parent]
                int w = dist[i] - dist[parent[i]];
                shortestPathsTree.addDirectedEdge(parent[i], i, w);
            }
        }

        // שחרור משאבים
        delete[] dist;
        delete[] parent;
        delete[] visited;

        return shortestPathsTree;
    }

    // ============================
    //         PRIM SECTION
    // ============================
    /**
     * @brief אלגוריתם פרים (Prim) לחישוב עץ פורש מינימלי (MST) בגרף לא מכוון.
     *        מתחיל מצומת 0 (ניתן לשנות), מוסיף קשתות הקלות ביותר שלא יוצרות מעגל.
     * 
     * @param g גרף הקלט (לא מכוון, עם משקלים).
     * @return Graph עץ פורש מינימלי כגרף לא מכוון.
     */
    Graph Algorithms::prim(Graph& g) {
        int V = g.getNumVertices();
        // נכין גרף חדש לאחסון ה-MST
        Graph mst(V);

        // מערכים:
        // key – המשקל המינימלי של קשת ש"מחברת" את הצומת למסט
        // parent – מיהו הצומת שממנו מגיעה הקשת
        // inMST – האם הצומת כבר נמצא ב-MST
        int* key = new int[V];
        int* parent = new int[V];
        bool* inMST = new bool[V];

        for (int i = 0; i < V; i++) {
            key[i] = INT_MAX;
            parent[i] = -1;
            inMST[i] = false;
        }

        // נבחר את הצומת 0 כצומת התחלתי
        key[0] = 0;
        PriorityQueue pq(V);
        pq.insert(0, 0);

        // כל עוד יש צמתים בתור העדיפויות
        while (!pq.isEmpty()) {
            // מוציאים את הצומת עם ה-key הקטן ביותר
            int u = pq.extractMin();
            inMST[u] = true;

            // עוברים על השכנים של u
            Node* neighbor = g.getAdjList()[u];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                int w = neighbor->weight;

                // אם v עוד לא ב-MST, ונמצאה קשת קלה יותר 
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.insert(v, key[v]);
                }
                neighbor = neighbor->next;
            }
        }

        // בניית עץ MST לתוך האובייקט mst
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1) {
                // כי זה עץ לא מכוון, נוסיף משני הצדדים
                mst.addEdge(parent[i], i, key[i]);
            }
        }

        delete[] key;
        delete[] parent;
        delete[] inMST;

        return mst;
    }

    // ============================
    //       KRUSKAL SECTION
    // ============================
    /**
     * @brief אלגוריתם קרוסקל (Kruskal) לחישוב עץ פורש מינימלי (MST). 
     *        אוסף את כל הקשתות, ממיין אותן מהקל לכבד, ואז מוסיף לפי הסדר
     *        קשתות שלא יוצרות מעגל (בדיקה ע"י Union-Find).
     * 
     * @param g גרף הקלט (לא מכוון, עם משקלים).
     * @return Graph עץ פורש מינימלי כגרף לא מכוון.
     */
    Graph Algorithms::kruskal(Graph& g) {
        int V = g.getNumVertices();
        // גרף חדש לאיחסון עץ ה-MST
        Graph mst(V);

        // נאסוף את הקשתות של הגרף לתוך מערך edges
        Edge* edges = new Edge[V * V]; // הקצאה מקסימלית
        int edgeCount = 0;

        Node** adjList = g.getAdjList();
        for (int u = 0; u < V; u++) {
            Node* nbr = adjList[u];
            while (nbr != nullptr) {
                int v = nbr->vertex;
                // כדי לא להוסיף קשת פעמיים, נבדוק רק כש-u < v
                if (u < v) {
                    edges[edgeCount++] = {u, v, nbr->weight};
                }
                nbr = nbr->next;
            }
        }

        // מיון הקשתות לפי משקל (כאן, שימוש ב-Selection Sort לדוגמה)
        for (int i = 0; i < edgeCount - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < edgeCount; j++) {
                if (edges[j].weight < edges[minIdx].weight) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                Edge temp = edges[i];
                edges[i] = edges[minIdx];
                edges[minIdx] = temp;
            }
        }

        // יצירת מבנה Union-Find למניעת מעגלים
        UnionFind uf(V);

        // נעבור על הקשתות מהמקל אל הכבד
        for (int i = 0; i < edgeCount; i++) {
            int setU = uf.find(edges[i].src);
            int setV = uf.find(edges[i].dst);

            // אם אינם באותה קבוצה, הוספת הקשת לא יוצרת מעגל
            if (setU != setV) {
                mst.addEdge(edges[i].src, edges[i].dst, edges[i].weight);
                uf.unite(setU, setV);
            }
        }

        // שחרור מערך הקשתות
        delete[] edges;

        return mst;
    }

} // namespace graph
