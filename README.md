# esercizi_sistemioperativi
Esercizi con librerie pthread e apue per programmazione di sistema, thread, sincronizzazione e mutua esclusione di processi.

[Libreria apue](https://github.com/shichao-an/apue.3e)

## Compilazione e linking dei file 
- se richiede apue (#include "apue.h")
`$ gcc -o programma nomeprogramma.c -I path/to/apue.3e/include/ -L path/to/apue.3e/lib/ -lapue`
- se richiede pthread, semaphore, fcntl, sys/* etc,
`$gcc -o programma nomeprogramma.c -lpthread`

