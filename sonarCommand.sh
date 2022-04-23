export SONAR_TOKEN=fe649effdffc39c9971b8d741ba8dd7ca1914e5f
make sonarCompile
/home/edmond-dantes/SonarScanner/bin/sonar-scanner -Dsonar.organization=simonenicosanti -Dsonar.projectKey=SimoneNicosanti_DataBase_Project -Dsonar.sources=. -Dsonar.cfamily.build-wrapper-output=bw-output -Dsonar.host.url=https://sonarcloud.io  
