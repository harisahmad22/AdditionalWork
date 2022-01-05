TARGET = myProg
TEST = todo_test 
MODULES = todo.o ioutil.o todo_list.o
TESTMODULES = test_todo.o todo_list.o
CPPFLAGS = -ansi -pedantic-errors -Wall -Wconversion
GTFLAGS = -lgtest -lgtest_main

$(TARGET): $(MODULES)
	g++ $(MODULES) -o $(TARGET)
	$(TARGET)

$(TEST):$(TESTMODULES)
	g++ $(GTFLAGS) $(TESTMODULES) -o $(TEST)
	$(TEST)

clean:
	/bin/rm -f *~ *.g *.o *.gch *.gcov *.gcno *.gcda $(TARGET) $(TEST)

all:	clean $(TARGET) $(TEST)

main:	clean $(TARGET)

test:	clean $(TEST)

todo.o: todo.cpp
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c todo.cpp

ioutil.o: ioutil.cpp
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c ioutil.cpp 

todo_list.o: todo_list.cpp
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c todo_list.cpp

test_todo.o: test_todo.cpp ioutil.h todo_list.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c test_todo.cpp
