CC = gcc
SOURCE = ./src/postivoS.c ./src/postivoService.c ./src/data/clientsData.c ./src/serverLogs.c ./src/serverOptions.c ./src/server.c ./src/documentFile.c ./src/shipments.c
SORUCE_LIB = ./src/base64/base64Decode.c ./src/soap/soapC.c ./src/soap/soapClient.c ./src/soap/soapServer.c ./src/soap/stdsoap2.c
PARAMETERS = -o postivoServer -DWITH_OPENSSL -std=gnu99 -I./include -L./lib
LIBS = -lgsoapssl -lssl -lcrypto -pthread -lrt

	
all:	$(SOURCE) $(SORUCE_LIB)
		$(CC) $(PARAMETERS) $(SOURCE) $(SORUCE_LIB) $(LIBS)

	
