CXX=clang++

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

main: main.o table.o obj.o
	${CXX} $^ -o $@

clean: 
	rm *.o