compile:
	gcc ./src/main.c -o ./out/main.out

sonarCompile:
	/home/edmond-dantes/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc ./src/main.c -o ./out/main.out
