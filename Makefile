object=main.o mysqlCon.o userDAO.o goodsDAO.o

test:$(object)
	g++ -o test $(object) -lmysqlclient -L/usr/lib64/mysql -std=c++11 -Wall

main.o:main.cpp mysqlCon.c userDAO.c goodsDAO.c
	g++ -c main.cpp  -lmysqlclient -L/usr/lib64/mysql -std=c++11
userDAO.o:userDAO.c userDAO.h
	g++ -c userDAO.c
goodsDAO.o:goodsDAO.c goodsDAO.h
	g++ -c goodsDAO.c
mysqlCon.o:mysqlCon.c mysqlCon.h
	g++ -c mysqlCon.c



#test:$(object)
#	gcc -o test $(object) -lmysqlclient -L/usr/lib64/mysql -Wall
#main.o:
#sqlHandle.o:
#mysqlCon.o:
clear:
	rm $(object) test
