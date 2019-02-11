ex: link
	./.run
link: main bigint
	g++ -std=c++17 -w -o .run .bigint.o .main.o 
main:
	g++ -std=c++17 -c -w -o .main.o multiply.cpp
bigint: ../../bigint.cpp ../../bigint.hpp
	g++ -std=c++17 -c -w -o .bigint.o ../../bigint.cpp

