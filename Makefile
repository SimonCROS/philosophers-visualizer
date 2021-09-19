all:
	clang++ src/*.cpp -I includes -o visualizer

clean:
	rm visualizer
