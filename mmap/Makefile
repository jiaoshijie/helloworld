hello: hello-as
	cc -o hello main.c -g

hello-i: hello.s
	nasm -o hello.o hello.s

# https://stackoverflow.com/questions/1647359/is-there-a-way-to-get-gcc-to-output-raw-binary
hello-as:
	gcc -o hello-gas hello-gas.s -nostdlib -no-pie -fno-pic
	objcopy -O binary -j .text hello-gas hello.o

clean:
	rm -rf hello *.o hello-gas
