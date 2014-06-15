#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
int main( int argc, char** argv )
{
    DIR *dirptr = NULL;
    struct dirent *entry;
    struct stat buf;
    if( argc != 2 )
    {
        fprintf( stderr, "Usage: ./prog /some/path\n" );
        return 1;

    }
    // do something with argv[ 1 ] which contains "/some/path"
    dirptr = opendir(argv[1]);
    while (entry = readdir(dirptr))
    {
        //printf("name:%s\n", entry->d_name);
        stat(entry->d_name,&buf);
        if(S_ISDIR(buf.st_mode))
        {
            //count++;
        }
        else
        {
            printf("file name:%s\n",entry->d_name);
        }
    }
    closedir(dirptr);


    return 0;
}
