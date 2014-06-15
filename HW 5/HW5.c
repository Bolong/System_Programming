#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

char out[100];
void do_ls(char []);
void dostat(char *);
void show_file_info(char *,struct stat *);
void mode_to_letters(int,char []);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int ac,char *av[])
{
	if(ac==1)
        //if there is no parameter, ls.
		do_ls(".");
	else
		while(--ac)
		{
			printf("%s:\n",*++av);
			do_ls(*av);
		}

	return 0;
}

void do_ls(char dirname[])
{
	DIR *dir_ptr;
	struct dirent *direntp;


	if((dir_ptr=opendir(dirname))==NULL)
        //open wrong dir
		fprintf(stderr,"ls1: Cannot open %s\n",dirname);
	else
	{
	    //go over dir
		while((direntp=readdir(dir_ptr))!=NULL)
			//printf("%s\n",direntp->d_name);
			//list details
			dostat(direntp->d_name);
		closedir(dir_ptr);
	}
}

void dostat(char *filename)
{
	struct stat info;
	if(lstat(filename,&info)==-1)
		perror(filename);
	else
        //print details
		show_file_info(filename,&info);
}

void show_file_info(char *filename,struct stat *info_p)
{
	char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
	void mode_to_letters();
	char modestr[11];

    //file mode change
	mode_to_letters(info_p->st_mode,modestr);

	printf("%s",modestr);//protection
	printf("%4d",(int)info_p->st_nlink);//number of hard links
	printf("%-8s",uid_to_name(info_p->st_uid)); //user ID of owner
	printf("%-8s",gid_to_name(info_p->st_gid));//group ID of owner
	printf("%8ld",(long)info_p->st_size); //total size, in bytes
	printf("%.12s ",4+ctime(&info_p->st_mtime));//time of last modification
	printf("%s",filename);//filename
    if(S_ISLNK(info_p->st_mode))		//determine if it is link, if so, return true.
    {
        printf(" -> ");
        if(readlink(filename,out,100)==-1)
        {
            printf("readlink error\n");
        }
        printf("%s\n",out);
    }
    else
    {
        printf("\n");
    }
}

void mode_to_letters(int mode,char str[])
{
	strcpy(str,"----------");
	str[0]='?';
	if(S_ISREG(mode))//normal
        str[0]='-';
	if(S_ISDIR(mode))//dir
		str[0]='d';
	if(S_ISCHR(mode))//character
		str[0]='c';
	if(S_ISBLK(mode))//blank
		str[0]='b';
    if(S_ISFIFO(mode))//FIFO (named pipe)
        str[0]='p';
    if(S_ISLNK(mode))//Symbolic link
        str[0]='l';
    if(S_ISSOCK(mode))//Socket
        str[0]='s';

	if(mode & S_IRUSR)
		str[1]='r';
	if(mode & S_IWUSR);
		str[2]='w';
	if(mode & S_IXUSR)
		str[3]='x';

	if(mode & S_IRGRP)
		str[4]='r';
	if(mode & S_IWGRP)
		str[5]='w';
	if(mode & S_IXGRP)
		str[6]='x';

	if(mode & S_IROTH)
		str[7]='r';
	if(mode & S_IWOTH)
		str[8]='w';
	if(mode & S_IXOTH)
		str[9]='x';
}

#include <pwd.h>
char *uid_to_name(uid_t uid)
{
    //change uid to username
	struct passwd *getpwuid(),*pw_ptr;
	static char numstr[10];

	if((pw_ptr=getpwuid(uid))==NULL)
	{
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

#include <grp.h>
char *gid_to_name(gid_t gid)
{
    //change gid to name
	struct group *getgrgid(),*grp_ptr;
	static char numstr[10];

	if((grp_ptr=getgrgid(gid))==NULL)
	{
		sprintf(numstr,"%d",gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}

