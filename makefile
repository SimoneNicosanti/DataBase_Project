compile :
	gcc -Wall -Wextra ./src/code/config/*.c ./src/code/controller/*.c ./src/code/db/*.c ./src/code/main/*.c ./src/code/view/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/out/client.out

run :
	make
	reset
	./src/out/client.out