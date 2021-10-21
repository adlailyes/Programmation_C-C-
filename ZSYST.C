/*ESI_1CS: Octobre 2017; : Processus Unix */

/* Creation de processus Zombis*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int p;
    p=fork(); /* création d'un premier fils */
	if(p==0){
		printf("\n Fin du processus fils1 : %d; Pére : %d\n",getpid(),getppid());
		exit(0);
	}
	sleep(1); /* attendre 1 seconde */

	p=fork(); /* création d'un deuxième fils */
	if(p==0){
            int i=0;
            while(i<10000000) i++;
            printf("\n Fin du processus fils2 : %d; Pére : %d\n",getpid(),getppid());
            sleep(1);
            return 0;
   	}

	printf("\n ***** PS1 *****\n=========================================\n");
	system("ps o stat,uid,pid,ppid,pri,start_time,comm");
    sleep(4);

    printf("\n ***** PS2 *****\n=========================================\n");
    system("ps o stat,uid,pid,ppid,pri,start_time,comm");

    while(wait(NULL)!=-1);

    printf("\n ***** PS3 *****\n=========================================\n");
    system("ps o stat,uid,pid,ppid,pri,start_time,comm");

    return 0;
}

/* resultats
bs@debian9:~/1cs/TPS1/Processus_c$ cc -o Zsyst Zsyst.c
bs@debian9:~/1cs/TPS1/Processus_c$ ./Zsyst

 Fin du processus fils1 : 12386; Pere : 12385

 ***** PS1 *****
=========================================
STAT   UID   PID  PPID PRI START COMMAND
Ss    1000  9893  9889  19 oct.08 bash
S+    1000 12385  9893  19 01:22 Zsyst
Z+    1000 12386 12385  19 01:22 Zsyst <defunct>
R+    1000 12387 12385  19 01:22 Zsyst
S+    1000 12388 12385  19 01:22 sh
R+    1000 12389 12388  19 01:22 ps

 Fin du processus fils2 : 12387; Pere : 12385

 ***** PS2 *****
=========================================
STAT   UID   PID  PPID PRI START COMMAND
Ss    1000  9893  9889  19 oct.08 bash
S+    1000 12385  9893  19 01:22 Zsyst
Z+    1000 12386 12385  19 01:22 Zsyst <defunct>
Z+    1000 12387 12385  19 01:22 Zsyst <defunct>
S+    1000 12390 12385  19 01:22 sh
R+    1000 12391 12390  19 01:22 ps

 ***** PS3 *****
=========================================
STAT   UID   PID  PPID PRI START COMMAND
Ss    1000  9893  9889  19 oct.08 bash
S+    1000 12385  9893  19 01:22 Zsyst
S+    1000 12392 12385  19 01:22 sh
R+    1000 12393 12392  19 01:22 ps


*/
