todo: main.cpp
	g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o todo

clean:
	rm -f todo tasks.txt
