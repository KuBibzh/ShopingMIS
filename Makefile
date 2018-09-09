object=main.o sqlHandle.o mysqlCon.o


test:$(object)
	g++ -o test $(object) -lmysqlclient -L/usr/lib64/mysql -std=c++11 -Wall

main.o:main.cpp mysqlCon.c sqlHandle.c
	g++ -c main.cpp  -lmysqlclient -L/usr/lib64/mysql -std=c++11
sqlHandle.o:sqlHandle.c sqlHandle.h
	g++ -c sqlHandle.c
mysqlCon.o:mysqlCon.c mysqlCon.h
	g++ -c mysqlCon.c



#test:$(object)
#	gcc -o test $(object) -lmysqlclient -L/usr/lib64/mysql -Wall
#main.o:
#sqlHandle.o:
#mysqlCon.o:
clear:
	rm $(object) test
