
all:
	g++ ./cast.cpp -g -O0 -o cast
	arm-linux-gnueabi-g++ ./cast.cpp -O0 -g3 -std=c++11 -o cast-arm
	arm-linux-gnueabi-objdump -d  --section=.rodata --section=.data --section=.text -SCI --prefix=./  ./cast-arm  > cast.dis
	./cast

clean:
	rm -f *.dis *-arm cast *.class
