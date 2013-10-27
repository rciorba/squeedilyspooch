all: build

build:
	-g++ -Wall -o remote remote.cpp network.cpp -lX11 -lXtst

.PHONY : clean
clean:
	-rm *.o
