CFLAGS:=--std=c89 -Wall -pedantic

fade: src/fade.c
	cpp $(CPPFLAGS) src/fade.c -o temp/fade.c
	distcc armv6j-hardfloat-linux-gnueabi-gcc -o obj/fade.o -c temp/fade.c
	gcc $(CFLAGS) -o ./fade obj/fade.o -pthread -lwiringPi

clean:
	rm -f ./fade obj/* temp/*
