# Indice esercizi

## [Esercizio 1](es1.c)
Scrivere un programma che intercetta CTRL-C ed invece di terminare scrive su stdout "non voglio terminare"

## [Esercizio 2](es2.c)
Scrivere un programma C che riceva in input da tastiera due numeri interi, a e b, ne stempi a video:
- la somma "a+b" solo quando riceve il segnale SIGUSR2
- la differenza "a-b" quando riceve il segnale SIGUSR1
- Il programma esce quando riceve SIGINT

## [Esercizio 3](es3.c)
Si realizzi un programma in C sotto Linux che preso un intero N come parametro da 
riga di comando compreso tra 1 e 100, 
Scrivere un programma C che prende in input un intero N come parametro da riga di comando, compreso
tra 1 e 100, e genera due figli che si comportano come segue:

Se il parametro N è pari, il programma invia il segnale SIGUSR1 al figlio f1 
che calcola la somma tra il valore del suo PID e quello del processo padre. 
Il processo f2 stamperà solo il suo PID.

Se il parametro N è dispari, il programma invia SIGUSR2 al figlio 2 che calcola 
la differenza tra il valore del PID del processo padre e il suo PID. 
Il processo f1 stamperà solo il suo PID.

Alla fine, il processo principale calcolerà e stamperà il prodotto dei PID dei due processi figli f1 e f2 e terminetà stampando un messaggio di saluto.
