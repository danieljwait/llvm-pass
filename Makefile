.PHONY: all clean

all:
		mkdir -p build
		cd build; \
		cmake ..; \
		make; \
		cd ..

clean:
		rm -rf build *.bc
