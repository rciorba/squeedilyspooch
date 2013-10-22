all: build

build:
	-g++ -Wall -o remote remote.cpp -lX11 -lXtst

.PHONY : clean
clean:
	-rm *.o
