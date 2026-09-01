main: in2post.o
	g++ -o main in2post.o

in2post.o: in2post.cpp stack.hpp
	g++ -c in2post.cpp

clean:
	rm -f main test_stack1.o in2post.o