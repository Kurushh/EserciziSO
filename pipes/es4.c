#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define fpari "./fpari" 
#define fdispari "./fdispari" 
#define fsomma "./fsomma"

int main(){
	char buf[sizeof(int)];
	int pid=0;
	int a=0;
	int b=0;
	int fpp=0, fppp=0, fpc=0, fpcc = 0;
	int v=0,r=0,z=0;
	int to_read=0;
	int totsum=0;
	int fp1=0,fp2=0, fp3=0;

	if (access(fpari,F_OK) == -1)
		mkfifo(fpari, 0777);

	if ((a=fork()) != 0 &&  (b=fork())!=0 ){
		fpp=open(fpari,O_WRONLY);
		fppp=open(fdispari,O_WRONLY);
		
		do{
			fgets(buf,sizeof(int),stdin);
			v = atoi(buf);
			if(v%2==0){
				write(fpp,&v,sizeof(v));
			}else{
				write(fppp,&v,sizeof(v));
			}
		}while(v > -1);
		close(fpp);
		close(fppp);
		if (access(fsomma,F_OK) == -1)
			mkfifo(fsomma, 0777);
		fp1=open(fsomma,O_RDONLY);
		read(fp1,&v,sizeof(v));
		totsum+=v;
		read(fp1,&v,sizeof(v));
		totsum+=v;
		printf("Somma totale: %d",totsum);


	}else if(a==0){
		int sum=0;
		fpc=open(fpari,O_RDONLY);
		do{
			to_read = read(fpc, &r,sizeof(r));
			if(r>0)
				sum=sum+r;

		}while(to_read > 0);
		printf("Sum pari: %d\n",sum);
		fp2=open(fsomma,O_WRONLY);
		write(fp2,&sum,sizeof(sum));

	}else if(b==0){
		int sum2=0;
		fpcc = open(fdispari,O_RDONLY);
		do{
			to_read= read(fpcc,&z,sizeof(z)); 
			if(z>0)
				sum2=sum2+z;
		}while(to_read > 0);
		printf("Sum dispari: %d\n",sum2);
		fp3=open(fsomma,O_WRONLY);
		write(fp3,&sum2,sizeof(sum2));

	}
	close(fpp);
	close(fppp);

};
