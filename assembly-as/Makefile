all: hello

hello: hello.s
	gcc -o hello hello.s -nostdlib -no-pie -fno-pic

clean:
	rm -rf hello
