compile:
	gcc -Wall -Wextra ./src/code/main/main.c -o ./src/out/client.out
	./src/out/client.out
 
sonarCompile:
	/home/simone/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc ./src/*.c -o ./out/main.out
