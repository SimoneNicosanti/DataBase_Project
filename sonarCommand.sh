export SONAR_TOKEN=9c150853ff0987845e8fc6654bc759ad27f94e9b
make sonarCompile
/home/simone/SonarScanner/bin/sonar-scanner -Dsonar.organization=simonenicosanti -Dsonar.projectKey=SimoneNicosanti_DataBase_Project -Dsonar.sources=. -Dsonar.cfamily.build-wrapper-output=bw-output -Dsonar.host.url=https://sonarcloud.io  

