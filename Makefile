all: test clean
	@mkdir build
	@cmake -S . -B build
	@cmake --build build

test: clean
	@mkdir build
	@cmake -S . -B build
	@cmake --build build --target tests

clean:
	@rm -rf build