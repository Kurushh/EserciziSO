# esercizi_sistemioperativi
Esercizi con librerie pthread e apue per programmazione di sistema, thread, sincronizzazione e mutua esclusione di processi.
Gli esercizi vanno da quelli più facili a quelli più complessi.

## Prerequisiti:
- [Libreria apue](https://github.com/shichao-an/apue.3e)

## Compilazione e linking dei file 
- se richiede apue (#include "apue.h")

`$ gcc -o programma nomeprogramma.c -I path/to/apue.3e/include/ -L path/to/apue.3e/lib/ -lapue`
- se richiede pthread (#include pthread.h, semaphore.h, fcntl.h, sys/\*.h, e così via)

`$gcc -o programma nomeprogramma.c -lpthread`

