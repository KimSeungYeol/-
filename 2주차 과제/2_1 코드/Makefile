help:
	echo "make all"
	echo "make clean"


all:
	gcc -c CLinkedList.c CLinkedList.h
	gcc -c CLinkedListMain.c CLinkedList.h

	gcc -o main CLinkedListMain.o CLinkedList.o CLinkedList.h

clean:
	rm *.o
	rm main


