secure_bank_management_system: bank.o majorfunction.o inputValidation.o loan.o util.o
	gcc bank.o majorfunction.o inputValidation.o loan.o util.o -o secure_bank_management_system

bank.o: bank.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c bank.c

majorfunction.o: majorfunction.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c majorfunction.c

inputValidation.o: inputValidation.c
	gcc -c inputValidation.c

loan.o: loan.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c loan.c

util.o: util.c data.h inputValidation.h majorfunction.h utilFunctions.h
	gcc -c util.c

clean:
	rm *.o secure_bank_management_system