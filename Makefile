fade: src/fade.c
	distcc armv6j-hardfloat-linux-gnueabi-gcc -o obj/fade.o -c src/fade.c
	gcc --std=c89 -Wall -pedantic -o ./fade obj/fade.o -pthread -lwiringPi

clean:
	rm -f ./fade obj/*
