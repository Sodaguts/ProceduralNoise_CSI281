all:
	g++ src/glad.c -I src/include -L src/lib -o NoiseGen project/main.cpp -lmingw32 -lSDL2main -lSDL2