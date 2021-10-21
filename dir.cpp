# include <sys/types.h> 	
# include <dirent.h>
# include <stdio.h>
#define MAX_BUF 256
int main ( int argc , char **argv )
{
DIR *dirp ;
 struct dirent *dp ;
char buf [MAX_BUF] ;
// montrer l e é rpe r t o i r e a c tue l
getcwd ( buf , MAX_BUF) ;
printf ( "éRpe r toi r e a c tue l : % s\n" , buf ) ;
// ouvre l e é rpe r t o i r e épass comme argument
dirp = opendir ( buf ) ;
if ( dirp == NULL)
{
printf ( "Ne peut pas l ' ouvr i r %s\n" , buf ) ;
}
else
{
// l i t é ent r e à é ent r e
while ( ( dp = readdir ( dirp ) ) != NULL)
printf ("%s\n" , dp->d_name ) ;
closedir ( dirp ) ;
}
}
