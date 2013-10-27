all: build

build:
	-g++ -Wall -o remote *.cpp -lX11 -lXtst

.PHONY : clean
clean:
	-rm *.o
check-syntax:
	-g++ -Wall -o nul -S ${CHK_SOURCES}
