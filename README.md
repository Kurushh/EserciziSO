# esercizi_sistemioperativi
Esercizi di preparazione all'esame di Sistemi Operativi.
Gli esercizi vanno da quelli più facili a quelli più complessi e fanno uso delle librerie pthread e apue.

## Prerequisiti:
- [Libreria apue](https://github.com/shichao-an/apue.3e)

## Compilazione e linking dei file 
- se richiede apue (#include "apue.h")

`$ gcc -o programma nomeprogramma.c -I path/to/apue.3e/include/ -L path/to/apue.3e/lib/ -lapue`
- se richiede pthread (#include pthread.h, semaphore.h, fcntl.h, sys/\*.h, e così via)

`$gcc -o programma nomeprogramma.c -lpthread`

