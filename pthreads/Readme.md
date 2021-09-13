# Indice esercizi

## [Esercizio 1](es1.c)
Scrivi un programma che accetta un intero da riga di comando, crea N thread poi aspetta che finiscano tutti.
Ogni thread aspetta un numero di secondi casuale da 1 a 10, poi incrementa il valore di una variabile locale.
Infine il processo padre stampa il valore di questa variabile.

## [Esercizio 2](es2.c)
Si realizzi un programma che lancia n thread che cercano in una matrice nxn, ogni thread in una riga diversa, un carattere c che si trova in questa matrice. Il processo che lo trova segnala agli altri che lo ha trovato e tutti i thread terminano.

## [Esercizio 3](es3.c)
Produttore-Consumatore, 1 buffer.

## [Esercizio 4](es4.c)
Si realizzi un programma in C e Posix sotto Linux che con l'ausilio della libreria pthread lancia m thread per
calcolare il prodotto di due matrici di dimensione mxn e nxp. 
Devono essere allocate dinamicamente.
Non appena sarà calcolata la matrice prodotto, un m+1-esimo thread che era in attesa stampa la matrice risultato.
(Usare i semafori con nome)
