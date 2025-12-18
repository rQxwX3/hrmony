build:
	cmake -S. -Bbuild
	cmake --build build

clean: 
	rm -rf build

rebuild: clean build

run: build
	./build/hrmony
