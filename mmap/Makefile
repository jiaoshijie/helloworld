hello: hello-i
	cc -o hello main.c

hello-i: hello.s
	nasm -o hello.o hello.s

clean:
	rm -rf hello *.o
