compile :
	gcc -Wall -Wextra ./src/code/config/*.c ./src/code/controller/*.c ./src/code/db/*.c ./src/code/main/*.c ./src/code/view/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/out/client.out
	./src/out/client.out

test_all :
	make test_environment
	make test_connection

test_environment :
	gcc -Wall -Wextra ./src/test/TestEnvironmentSetter.c ./src/code/utils/IOUtils.c ./src/code/config/EnvironmentSetter.c -o ./src/test/test.out
	./src/test/test.out

test_connection :
	gcc -Wall -Wextra ./src/test/TestConnector.c ./src/code/utils/IOUtils.c ./src/code/db/Connector.c ./src/code/config/EnvironmentSetter.c `mysql_config --cflags --include --libs` -o ./src/test/test.out
	./src/test/test.out

sonar_compile :
	/home/simone/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc ./src/*.c -o ./out/main.out
