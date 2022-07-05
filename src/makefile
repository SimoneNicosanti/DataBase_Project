compile :
	reset
	gcc -Wall -Wextra ./code/config/*.c ./code/controller/*.c ./code/db/*.c ./code/main/*.c ./code/view/*.c ./code/utils/*.c `mysql_config --cflags --include --libs` -o ./client.out

run :
	make
	reset
	./client.out
