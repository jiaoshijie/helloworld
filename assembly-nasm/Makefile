all: hello

hello: hello-o
	ld -o hello hello.o

hello-o: hello.s
	nasm -o hello.o -felf64 hello.s

clean:
	rm -rf hello *.o
