all:
	@echo "Building tests..."
	@mkdir -p build
	@gcc test.c -c -o ./build/test.o -g -nostdlib
	@as art0.s -g -o ./build/art0.o
	@as string.s -g -o ./build/string.o
	@ld ./build/art0.o ./build/test.o ./build/string.o -o test
	@echo "done."

clean:
	@echo "Deleting ./build"
	@rm -rf build
