compile:
	gcc -Wall -Wextra ./src/code/main/main.c -o ./src/out/client.out
	./src/out/client.out

test_all :
	make test_environment
	make test_connection

test_environment :
	gcc -Wall -Wextra ./src/test/TestEnvironmentSetter.c ./src/test/TestUtils.c ./src/code/config/EnvironmentSetter.c -o ./src/test/test.out
	./src/test/test.out

test_connection :
	gcc -Wall -Wextra ./src/test/TestConnector.c ./src/test/TestUtils.c ./src/code/db/Connector.c ./src/code/config/EnvironmentSetter.c `mysql_config --cflags --include --libs` -o ./src/test/test.out
	./src/test/test.out

sonarCompile:
	/home/simone/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc ./src/*.c -o ./out/main.out
