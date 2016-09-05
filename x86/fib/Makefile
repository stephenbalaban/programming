all:
	nasm -f elf fib.asm
	gcc -m32 -o fib fib.o
	clang -Ofast -m32 -o fib_c fib.c

test:
	time ./fib
	time ./fib_c

clean:
	rm fib fib.o
