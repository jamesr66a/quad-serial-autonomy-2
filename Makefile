CFLAGS:=--std=c89 -Wall -pedantic

parallel: src/parallel.c
	cpp $(CPPFLAGS) src/parallel.c -o temp/parallel.c
	distcc armv6j-hardfloat-linux-gnueabi-gcc -o obj/parallel.o -c temp/parallel.c
	gcc $(CFLAGS) -o ./parallel obj/parallel.o -pthread -lwiringPi

fade: src/fade.c
	cpp $(CPPFLAGS) src/fade.c -o temp/fade.c
	distcc armv6j-hardfloat-linux-gnueabi-gcc -o obj/fade.o -c temp/fade.c
	gcc $(CFLAGS) -o ./fade obj/fade.o -pthread -lwiringPi

clean:
	rm -f ./parallel ./fade obj/* temp/*
