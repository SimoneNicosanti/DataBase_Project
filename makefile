compile :
	gcc -Wall -Wextra ./src/code/config/*.c ./src/code/controller/*.c ./src/code/db/*.c ./src/code/main/*.c ./src/code/view/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/out/client.out

run :
	make
	./src/out/client.out

sonar_compile :
	/home/simone/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc -Wall -Wextra ./src/code/config/*.c ./src/code/controller/*.c ./src/code/db/*.c ./src/code/main/*.c ./src/code/view/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/out/client.out
