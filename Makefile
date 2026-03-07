all:
	@mkdir -p build
	@gcc test.c -c -o ./build/test.o -g -nostdlib
	@as art0.s -g -o ./build/art0.o
	@as string.s -g -o ./build/string.o
	@as helpers.s -g -o ./build/helpers.o
	@ld ./build/art0.o ./build/test.o ./build/string.o ./build/helpers.o -o test

clean:
	@rm -rf build
