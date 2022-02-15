# EserciziSO
Anno: 2021/2022

Esercizi di preparazione all'esame di Sistemi Operativi sulla programmazione UNIX.
Gli esercizi vanno da quelli più facili a quelli più complessi e fanno uso di alcune librerie tra cui pthread.

La [Libreria apue](https://github.com/shichao-an/apue.3e) può essere rimpiazzata con varie librerie C più aggiornate. 
Per sapere quali si può fare (da riga di comando, provato su linux): `man <function>` dove function è la function desiderata, per esempio "getpid()" si trova in "<unistd.h>"

## Compilazione e linking dei file 
- se richiede apue (#include "apue.h"):

`$ gcc -o programma nomeprogramma.c -I path/to/apue.3e/include/ -L path/to/apue.3e/lib/ -lapue`


- se richiede pthread (#include pthread.h, semaphore.h):

`$gcc -o programma nomeprogramma.c -lpthread`

