ksat: ksat.cpp rand.cpp 
	g++ -o ksat ksat.cpp rand.cpp bitHelpers.cpp

run: ksat
	./ksat 100 64 .9 < test01.txt
	./ksat 100 64 .9 < test02.txt
	./ksat 100 64 .9 < test03.txt
	./ksat 100 64 .9 < test04.txt
	./ksat 500 128 .9 < test05.txt
	./ksat 500 128 .9 < test06.txt
	./ksat 1000 64 .9 < test07.txt
	./ksat 1000 64 0  < test07.txt

tar:
	tar -cvf pas3.tar ksat.cpp rand.cpp rand.h bitHelpers.h bitHelpers.cpp makefile

