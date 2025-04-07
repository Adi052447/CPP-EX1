# CPP-EX1

## פרטי המגישה: 
שם: עדי גם זו לטובה    
 תז:  211602222     
 מייל: adi.gamzu@gmail.com   


## תיאור הפרויקט

פרויקט זה מדגים מימוש מבני נתונים ואלגוריתמים בסיסיים בתחום הגרפים:

- **מבני נתונים**:
  1. מחסנית (Stack)
  2. תור (Queue)
  3. תור עדיפויות (Priority Queue)
  4. איחוד-חיפוש (Union-Find)
- **גרף (Graph)** – עם רשימות שכנים, ופעולות להוספה/הסרה/הדפסה.
- **אלגוריתמים** (במחלקת `Algorithms`):
  1. BFS (חיפוש לרוחב)
  2. DFS (חיפוש לעומק)
  3. Dijkstra (מסלולים קצרים)
  4. Prim (עץ פורש מינימלי)
  5. Kruskal (עץ פורש מינימלי)

בנוסף, קיים קוד הדגמה (`main.cpp`) להצגת שימוש וכן קובץ בדיקות (`test.cpp`) עם doctest.

---

## מבנה התיקיות והקבצים

```plaintext
.
├── data_structures.hpp        # כותרות למבני הנתונים
├── data_structures.cpp        # מימוש מבני הנתונים
├── Graph.hpp                  # כותרות למחלקת הגרף
├── Graph.cpp                  # מימוש הגרף
├── Algorithms.hpp             # כותרות לאלגוריתמים על גרפים
├── Algorithms.cpp             # מימוש האלגוריתמים
├── main.cpp                   # תוכנית הרצה (דוגמה)
├── test.cpp                   # בדיקות יחידה (doctest)
├── doctest.hpp                # ספריית doctest (header-only)
├── Makefile                   # קובץ make
└── README.md                  # קובץ הוראות זה
```

---

## דרישות והתקנות


 **Valgrind** להרצת בדיקת זיכרון
   ```bash
   sudo apt-get install valgrind
   ```
3. ספריית `doctest` כבר כלולה (`doctest.hpp`).

---

## קומפילציה והרצה

### מטרות Makefile

- **make Main**

  - מקמפל את כל ה־cpp ויוצר קובץ הרצה בשם `Main`, מריץ אותו.

- **make test**

  - מקמפל את קובץ test.cpp בעזרת doctest, יוצר קובץ בשם `test` ומריץ את הבדיקות.

- **make valgrind**

  - מקמפל (אם צריך) ומריץ את `valgrind --leak-check=full ./Main`.

- **make clean**

  - מוחק קבצי אובייקט והרצות בינאריות.

### דוגמה להרצה:

```bash
make Main      # קומפילציה והרצה רגילה
make test      # קומפילציה והרצת הבדיקות
make valgrind  # בדיקת דליפות זיכרון
make clean     # ניקיון
```

---

## הסבר קצר על הקוד

1. **data\_structures** – מכיל את Stack, Queue, PriorityQueue, UnionFind.
2. **Graph** – מחלקת Graph עם פעולות להוספה/הסרה/קשת מכוונת/הדפסה.
3. **Algorithms** – אלגוריתמים על הגרף (BFS, DFS, Dijkstra, Prim, Kruskal).
4. **main.cpp** – דוגמה של בניית גרף והרצת האלגוריתמים.
5. **test.cpp** – בדיקות יחידה (doctest) למבני הנתונים והאלגוריתמים.

