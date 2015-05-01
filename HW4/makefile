decipher: decipher.cpp rand.cpp 
	g++ -o decipher decipher.cpp rand.cpp 

run: decipher 
	./decipher < i603.code


tar:
	tar -cvf pas4.tar decipher.cpp rand.cpp rand.h makefile wang.pdf freq1.txt

answer:
	cat ans.txt