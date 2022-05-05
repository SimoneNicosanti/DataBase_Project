compile :
	gcc -Wall -Wextra ./src/code/config/*.c ./src/code/controller/*.c ./src/code/db/*.c ./src/code/main/*.c ./src/code/view/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/out/client.out
	./src/out/client.out

test_all :
	make test_environment
	make test_connection
	make test_login
	make test_administration 

test_environment :
	gcc -Wall -Wextra ./src/test/TestEnvironmentSetter.c ./src/code/utils/*.c ./src/code/config/EnvironmentSetter.c -o ./src/test/test.out
	./src/test/test.out

test_connection :
	gcc -Wall -Wextra ./src/test/TestConnector.c ./src/code/utils/*.c ./src/code/db/*.c ./src/code/config/*.c `mysql_config --cflags --include --libs` -o ./src/test/test.out
	./src/test/test.out

test_login :
	gcc -Wall -Wextra ./src/test/TestLogin.c ./src/code/db/*.c ./src/code/config/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/test/test.out
	./src/test/test.out

test_administration :
	gcc -Wall -Wextra ./src/test/TestAdministration.c ./src/code/db/*.c ./src/code/config/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/test/test.out
	./src/test/test.out

test_secretary :
	gcc -Wall -Wextra ./src/test/TestSecretary.c ./src/code/db/*.c ./src/code/config/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/test/test.out
	./src/test/test.out

sonar_compile :
	/home/simone/SonarScanner/BuildWrapper/buildWrapper --out-dir bw-output gcc -Wall -Wextra ./src/code/config/*.c ./src/code/controller/*.c ./src/code/db/*.c ./src/code/main/*.c ./src/code/view/*.c ./src/code/utils/*.c `mysql_config --cflags --include --libs` -o ./src/out/client.out
