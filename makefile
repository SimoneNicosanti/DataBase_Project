compile:
	gcc ./src/*.c -o ./out/main.out

sonarCompile:
	/home/simone/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc ./src/*.c -o ./out/main.out
