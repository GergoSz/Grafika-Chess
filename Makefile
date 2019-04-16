all:
	gcc -w -Iinclude/ src/list.c src/available.c src/board.c src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/texture.c src/utils.c -lSOIL -lobj -lopengl32 -lglu32 -lglut32 -lm -o chess.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/texture.c src/utils.c -lSOIL -lobj -lGL -lGLU -lglut -lm -o chess -Wall -Wextra -Wpedantic
