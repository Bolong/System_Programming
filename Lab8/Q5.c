#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
void listDir(char *path);

int main( int argc, char** argv )
{

    if( argc != 2 )
    {
        fprintf( stderr, "Usage: ./prog /some/path\n" );
        return 1;

    }
    listDir(argv[1]);
    return 0;
}

void listDir(char *path)
{
    DIR              *pDir ;  //a pointer of Dir
    struct dirent    *entry  ;
    int               i=0  ;
    char              childpath[512];  //define an array as the path
    struct stat buf;
    pDir=opendir(path); //  open the path directory and turn to pDir pointer
    memset(childpath,0,sizeof(childpath)); //set all the elements in this array "0"


    while((entry=readdir(pDir))!=NULL) //if it is not null, do the loop
    {
        stat(entry->d_name,&buf);
        if(S_ISDIR(buf.st_mode))
        {

            if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
                //if d_name = . or .. , means load the current directory or last directory
                continue;

            sprintf(childpath,"%s/%s",path,entry->d_name);  //if it is not . or .., then turn the path and filename "d_name" to childpath, and printf
            printf("path:%s\n",childpath);

            listDir(childpath);

        }
        else  //if load not directory but file, then output d_name directly
        {
            printf("file:%s\n",entry->d_name);
        }
    }

}
