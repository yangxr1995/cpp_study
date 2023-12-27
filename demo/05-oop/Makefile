
all:
	g++ ./vir.cpp -g -O0 -o vir
	#g++ -fdump-class-hierarchy vir.cpp
	arm-linux-gnueabi-g++ ./vir.cpp -O0 -g3 -std=c++11 -o vir-arm
	arm-linux-gnueabi-objdump -d  --section=.rodata --section=.data --section=.text -SCI --prefix=./  ./vir-arm  > vir.dis
	arm-linux-gnueabi-objdump -d   ./vir-arm  > vir.dis2
	./vir

clean:
	rm -f ./oop ./vir ./vir.dis ./vir-arm *.class
