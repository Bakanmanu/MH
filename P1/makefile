#Autor: Manuel Zafra Mota


all: bin/main

obj/MDD.o: src/MDD.cpp include/MDD.h
	g++ -o obj/MDD.o -c src/MDD.cpp -I./include 

obj/main.o: src/main.cpp include/MDD.h
	g++ -o obj/main.o -c src/main.cpp -I./include

bin/main: obj/MDD.o obj/main.o
	g++ -o bin/main obj/*.o 




exec:
	./bin/main datos_MDD/GKD-b_10_n25_m7.txt


clear: 
	rm obj/*.o bin/*
