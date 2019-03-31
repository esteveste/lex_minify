#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

extern int yylex();
extern void yyset_in(FILE *_in_str);
extern YY_BUFFER_STATE yy_scan_buffer(char *, size_t);

extern char* FILE_TYPE;
extern FILE *yyout;
extern void yyset_out(FILE *_out_str);

extern int errno;


const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}


void processFile(char *path, char *path_out)
{
    FILE *fd_in, *fd_out;
    puts(path);
    fd_in = fopen(path, "r");

    if (fd_in == NULL)
    {
        printf("Error while opening %s\n", path);
        return;
    }

    fd_out = fopen(path_out, "w");

    if (fd_out == NULL)
    {
        printf("Error while opening write file to %s\n", path_out);
        return;
    }

    yyset_in(fd_in);
    yyset_out(fd_out);
    yylex();

    fclose(fd_in);
}

void tree(char *basePath, char *baseOutPath)
{
    char path[1000],outPath[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if (strcmp(get_filename_ext(dp->d_name), FILE_TYPE) == 0)
            {
                char filePath[1000];
                sprintf(filePath, "%s/%s", basePath, dp->d_name);

                char fileOutPath[1000];
                sprintf(fileOutPath, "%s/%s", baseOutPath, dp->d_name);

                mkdir(baseOutPath,0755);
                processFile(filePath, fileOutPath);
            }

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            strcpy(outPath, baseOutPath);
            strcat(outPath, "/");
            strcat(outPath, dp->d_name);
            
            tree(path, outPath);
        }
    }

    closedir(dir);
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("minify '/input/folder' '/output/folder'\n");
        printf("\nminifies files of type %s\n",FILE_TYPE);
        return -1;
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        printf("ERROR PATHS ARE EQUAL\n");

        return -1;
    }
    mkdir(argv[2],0755);
    tree(argv[1], argv[2]);

    return 0;
}
