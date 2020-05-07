output: bank.o fakeC.o inputValidation.o loan.o util.o
	gcc bank.o fakeC.o inputValidation.o loan.o util.o -o output

bank.o: bank.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c bank.c

fakeC.o: fakec.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c fakeC.c

inputValidation.o: inputValidation.c
	gcc -c inputValidation.c

loan.o: loan.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c loan.c

util.o: util.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c util.c

clean:
	rm *.o output