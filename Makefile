build:
	gcc -o tema2 main.c functii.c
run:
	./tema2
clean:
	rm tema2
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema2