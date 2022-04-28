date/4/26/22
author: andrew marshall
file: inode.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>



int main()
{
    char path[100];
    printf("Enter source file path: ");
    scanf("%s", path);
    DIR *directory;
    struct dirent *file;
    struct stat info;
    int entries = 0 ;

    // entering the directory
    directory = opendir(path);
    if ( directory == NULL )
    {
        perror("the directory couldn't be accessed or does not exist");
        return(2);
    }


    printf("No   type           name          size      blocks inode       links     TimeStamp \n\n");
    while((file = readdir(directory)))
    {
        if( file->d_name[0] == '.' )
        { // then hidden file, so leave hidden
            continue;
        }

        entries++;

        char buffer[1024];
        strcpy( buffer, path );
        strcat( buffer, file->d_name );
        if (stat( buffer, &info ) == -1)
        {
            perror( buffer );
            continue;
        }
	int i=0;
	i++;
	//makeing the .gv file output
	FILE *fp = fopen("inodes.gv", "a");
	fprintf(fp,"digraph sample_flow{\n");
	fprintf(fp,"rankdir=LR\n");
	fprintf(fp,"node [shape=circle];\n");
	fprintf(fp,"%20s",file->d_name);
	fprintf(fp,"=");
	fprintf(fp,"%10ld",info.st_size);
	fprintf(fp,",");
	fprintf(fp,"%10ld",info.st_blocks);
	fprintf(fp,",");
	fprintf(fp,"%10ld", info.st_ino);
	fprintf(fp,",");
	fprintf(fp,"%10ld", info.st_nlink);
	fprintf(fp,";");
	fprintf(fp,"%20s\n",file->d_name);
	fprintf(fp,"->");
	fprintf(fp,"%20s\n",file->d_name);
	
	fclose(fp);
	
        // show the number of the entry
        printf("%2d  ",entries);

        // determine if file or directory
        if(S_ISDIR(info.st_mode))
            printf("Dir ");
        else
            printf("File");

        // display the name of the file
        printf("%20s",file->d_name);

        // display the size of the file
        printf("%10ld",info.st_size);
	//allocated blocks 
	printf("%10ld",info.st_blocks);
	//i-node number 
	printf("%10ld",info.st_ino);
	//number of links 
	printf("%10ld",info.st_nlink);
	


        // show the last modified time
        if(!(S_ISDIR(info.st_mode)))
            printf("%30s\n",ctime(&info.st_mtime));
        else puts("\n");

    }
    return(0);
}





