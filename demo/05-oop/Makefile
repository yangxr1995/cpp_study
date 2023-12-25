
all:
	g++ ./oop.cpp -O0 -g3 -o oop -std=c++11
	g++ ./vir.cpp -O0 -g3 -o vir -std=c++11
	arm-linux-gnueabi-g++ ./vir.cpp -O0 -g3 -std=c++11 -o vir-arm
	arm-linux-gnueabi-objdump -d  --section=.rodata --section=.data --section=.text -SCI --prefix=./  ./vir-arm  > vir.dis
	./vir

clean:
	rm -f ./oop ./vir ./vir.dis ./vir-arm
