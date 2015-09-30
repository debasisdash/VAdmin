CC=/usr/bin/g++
CFLAG=-c -wall

all:
	$(CC) moniterServer.C parse.h tcpUtil.h dbProxy.C dbProxy.h -pthread -o moniterServer -l sqlite3
	$(CC) nodeClient.C parse.h util.h -o nodeClient
	$(CC) loadBalance/loadBalancer.C loadBalance/util.h -pthread -o loadBalance/loadBalancer

clean:
	rm -rf moniterServer nodeClient ipaddr.txt output.txt df.txt loadBalance/loadBalancer *.gch
