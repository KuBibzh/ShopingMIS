object=main.o sqlHandle.o mysqlCon.o


test:$(object)
	gcc -o test $(object) -lmysqlclient -L/usr/lib64/mysql -Wall

main.o:
sqlHandle.o:
mysqlCon.o:
clear:
	rm $(object) test
