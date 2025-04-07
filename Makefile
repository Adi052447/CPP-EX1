##adi.gamzu@msmail.ariel.ac.il 

########################################################
#               Makefile for Graph Project             #
#    Targets:                                          #
#       make Main      - compile & run main.cpp        #
#       make test      - compile & run test (doctest)  #
#       make valgrind  - run valgrind on Main          #
#       make clean     - remove binary/object files    #
########################################################

# קומפיילר ודגלי קומפילציה בסיסיים
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# אם רוצים רגישות ל-Debug, אפשר להוסיף: -g
# CXXFLAGS += -g

# רשימת קבצי המקור (CPP)
SOURCES = data_structures.cpp Graph.cpp Algorithms.cpp
HEADERS = data_structures.hpp Graph.hpp Algorithms.hpp

# יוצרים קבצי אובייקט (.o) מקבצי המקור
OBJS = data_structures.o Graph.o Algorithms.o

# כברירת מחדל, נרצה לקמפל את התכנית הראשית
all: Main

############################################
# חוקים ליצירת קבצי אובייקט
############################################
data_structures.o: data_structures.cpp data_structures.hpp
	$(CXX) $(CXXFLAGS) -c data_structures.cpp

Graph.o: Graph.cpp Graph.hpp data_structures.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp data_structures.hpp
	$(CXX) $(CXXFLAGS) -c Algorithms.cpp

############################################
#  מקמפל ומריץ את התכנית הראשית (Main)
############################################
main.o: main.cpp Graph.hpp Algorithms.hpp data_structures.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Main: $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o Main main.o $(OBJS)
	./Main

############################################
#  מקמפל ומריץ את הבדיקות 
############################################
test.o: test.cpp Graph.hpp Algorithms.hpp data_structures.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

test: $(OBJS) test.o
	$(CXX) $(CXXFLAGS) -o test test.o $(OBJS)
	./test

############################################
# בדיקת זליגות זיכרון עם Valgrind
############################################
valgrind: Main
	valgrind --leak-check=full ./Main

############################################
#  ניקוי קבצי בינארי/אובייקטים
############################################
clean:
	rm -f *.o Main test
