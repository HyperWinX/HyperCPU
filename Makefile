all: clean
	@mkdir build
	@cmake -S . -B build
	@cmake --build build

clean:
	@rm -rf build