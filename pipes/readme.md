# Indice Esercizi

## [Esercizio 1](es1.c)
Un programma prende in input un intero. Crea un processo figlio che incrementa questo valore di 5 e lo passa al padre. (pipe anonime)
Il padre verifica se questo valore è < 10 oppure no e stampa qualcosa a video
## [Esercizio 2](es2.c)
Scrivere un programma che esegue il comando di shell "ls -R | grep <pat>" dove "<pat>" è inserito dall'utente (pipe anonime)
## [Esercizio 3](es3.c)
Scrivere un programma che esegua il comando shell "ls | sort | grep <pat>" con tre processi distinti (pipe anonime)
## [Esercizio 4](es4.c)
Scrivere un programma che gestisce il comportamento di un padre e due figli (fdispari e fpari): il padre legge numeri da tastiera finché non incontra -1.
Se il numero è pari lo manda a fpari, altrimenti lo manda a fdispari. I figli effettuano le somme parziali e poi lo rispediscono al padre che effettua la somma totale.
Edit: [grazie!](http://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html)
  
## [Esercizio 5](es5.c)
 Realizzare un programma che riceve 2 nomi di file da riga di comando, e genera 1 processo figlio. 
 Il padre legge dal primo file e scrive quello che legge in una pipe, il figlio legge dalla pipe e scrive quello che legge nel secondo file.
 Il tutto termina quando il padre non ha altro da leggere.
 Il secondo file deve essere creato, se non esiste, con permessi di lettura e scrittura per il proprietario e per il gruppo.
