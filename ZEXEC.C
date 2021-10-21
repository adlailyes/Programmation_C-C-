/*ESI_1CS: Octobre 2017; : Processus Unix */
/* system("ps o stat,uid,pid,ppid,pri,start_time,comm"); */

/* creation de processus Zombis*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{ 	int p;
	char *ps[]={"ps","-o","stat,uid,pid,ppid,pri,start_time,comm",NULL};

    p=fork();   /* création du premier fils */

	if(p==0){ /* premier fils */
		printf("\n Fin du processus fils1 : %d; Pere : %d\n",getpid(),getppid());
		exit(0);
	}
	sleep(1); /* attendre 1 seconde */
	p=fork(); /* création d'un deuxième fils */

	if(p==0){ /* deuxième fils */
		int i=0;
	 	while(i<10000000) i++;
        printf("\n Fin du processus fils2 : %d; Pere : %d\n",getpid(),getppid());
        sleep(1);
        return 0;
   	}

	printf("\n ***** PS1 *****\n=========================================\n");

    p=fork(); /* création d'un troisième fils pour PS1 */
	if(p==0) execl("/bin/ps","/bin/ps","-o","stat,uid,pid,ppid,pri,start_time,comm",(char *)0);

    sleep(4);
    printf("\n ***** PS2 *****\n=========================================\n");

    p=fork(); /* création d'un quatrième fils pour PS2 */
	if(p==0) execlp("ps","ps","-o","stat,uid,pid,ppid,pri,start_time,comm",NULL);

   	sleep(4);
   	while(wait(NULL)!=-1);

   	sleep(2);
   	printf("\n ***** PS3 *****\n=========================================\n");

    /* Le père change de programme et exécute PS3 */

	execvp("ps",ps);
}


/* résultat
bs@debian9:~/1cs/TPS1/Processus_c$ cc -o Zexec Zexec.c
bs@debian9:~/1cs/TPS1/Processus_c$ ./Zexec

 Fin du processus fils1 : 12891; Pere : 12890

 ***** PS1 *****
=========================================
STAT   UID   PID  PPID PRI START COMMAND
Ss    1000  9893  9889  19 oct.08 bash
S+    1000 12890  9893  19 02:45 Zexec
Z+    1000 12891 12890  19 02:45 Zexec <defunct>
R+    1000 12892 12890  19 02:45 Zexec
R+    1000 12893 12890  19 02:45 ps

 Fin du processus fils2 : 12892; Pere : 12890

 ***** PS2 *****
=========================================
STAT   UID   PID  PPID PRI START COMMAND
Ss    1000  9893  9889  19 oct.08 bash
S+    1000 12890  9893  19 02:45 Zexec
Z+    1000 12891 12890  19 02:45 Zexec <defunct>
Z+    1000 12892 12890  19 02:45 Zexec <defunct>
Z+    1000 12893 12890  19 02:45 ps <defunct>
R+    1000 12894 12890  19 02:46 ps

 ***** PS3 *****
=========================================
STAT   UID   PID  PPID PRI START COMMAND
Ss    1000  9893  9889  19 oct.08 bash
R+    1000 12890  9893  19 02:45 ps
bs@debian9:~/1cs/TPS1/Processus_c$

*/
