# Indice esercizi

## [Esercizio 1](es1.c)
Scrivere un programma che intercetta CTRL-C ed invece di terminare scrive su stdout "non voglio terminare"

## [Esercizio 2](es2.c)
Scrivere un programma C che riceva in input da tastiera due numeri interi, a e b, ne stempi a video:
- la somma "a+b" solo quando riceve il segnale SIGUSR2
- la differenza "a-b" quando riceve il segnale SIGUSR1
- Il programma esce quando riceve SIGINT
