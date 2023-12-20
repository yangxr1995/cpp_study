all:
	arm-linux-gnueabi-g++ main.cpp -g -c -O0 -o main.o
	arm-linux-gnueabi-objdump --no-show-raw-insn -SI --prefix=./  ./main.o  > main.dis
	g++ main.cpp -o a.out
	./a.out

clean:
	rm -rf a.out main.o main.dis
