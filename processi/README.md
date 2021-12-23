# Indice esercizi
## Esercizio 1
Programma che crea una catena di processi tramite la chiamata fork()

Spiegazione del codice:
```C
for (i = 1; i< n; i++){
		if (childpid = fork()){
			break;
		}
}
```
Un ciclo for parte da `i=1` per comodità, ma funziona con qualsiasi indice, dentro al ciclo for c'è un costrutto if che richiama la system call fork, che crea un nuovo processo virtualmente identico al padre. Dopo di ché, se la chiamata fork è andata a buon fine allora il processo che l'ha richiamata si interrompe.

Il processo figlio inizia una nuova esecuzione a partire da questa fork, ignorando il codice che è stato scritto prima.
Supponiamo che l'input sia 10, al passo 2 dell'algoritmo, si parte con `i=2` in memoria, il figlio a questo punto è ancora nel ciclo for perché `i=2 < n=10`, quindi effettua una nuova chiamata `fork()`, che crea un altro processo figlio. Il processo con `i=2` viene terminato dal break, il nuovo processo incrementa i che ora vale `i=3` e ripete i passaggi.

Al passo 9, abbiamo che `i=9`, i viene incrementato e vale 10, il processo P(10) non crea un ulteriore figlio poiché esce dal ciclo for.

L'output assomiglia a qualcosa del genere:
```bash
i: 1 processo ID:49063 padre ID:47343 figlio ID:49064
i: 2 processo ID:49064 padre ID:49063 figlio ID:49065
i: 3 processo ID:49065 padre ID:49064 figlio ID:49066
i: 4 processo ID:49066 padre ID:49065 figlio ID:49067
i: 5 processo ID:49067 padre ID:49066 figlio ID:49068
i: 6 processo ID:49068 padre ID:49067 figlio ID:49069
i: 7 processo ID:49069 padre ID:49068 figlio ID:49070
i: 8 processo ID:49070 padre ID:49069 figlio ID:49071
i: 9 processo ID:49071 padre ID:49070 figlio ID:49072
i: 10 processo ID:49072 padre ID:49071 figlio ID:0
```

Da notare come l'ultimo processo non ha figli, childpid è la variabile che raccoglie l'id del processo figlio, inizialmente è inizializzata a 0.
Ogni processo P(i) ha l'ID pari a P(i-1) + 1

___

## Esercizio 2
Programma che crea un albero binario (completo) di processi.

```C
for (i=0; i<n-1; i++){
                if ( ( childpid_2=fork() ) && ( childpid_1=fork() ) ) {
                        break;
                }
        }
```

## Esercizio 3
Programma che crea un albero n-ario completo di processi

```C
flag = 0;
//at the end of the 2th for cicle:
//flag == 0 if child ,flag == 1 if parent

for (i=0; i<h; i++){
	for(j=0;j<n;j++){
		if ( (t=fork()) == 0){ //child
			flag = 1;
                        break;
                }else{ //parent
                        wait(NULL);
                }

         }
         if ( flag == 0){
         //if a parent, terminate because you already created all the son you had to
         	break;
          }
}
```
