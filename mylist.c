#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string.h>

typedef int64_t intmax_t;

void _ls(char *dir)
{
    struct dirent *d;
    struct stat fileStat;
    DIR *dh = opendir(dir);

    if(!dh) {
        if (errno == ENOENT) {

            perror("Directory does not exist");
        }
        else {
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }

    char file_names[100][100];
    int j = 0;

    while ( (d = readdir(dh)) != NULL) {

        if (d->d_name[0] == '.') continue;

        strcpy(file_names[j],d->d_name);
        j++;

    }

    char temp[100];
    int i,m;
    for(i=0;i<j;i++)
    {
        for(m=i;m<j;m++)
        {
            if(strcmp(file_names[i],file_names[m])>0)
            {
                strcpy(temp,file_names[i]);
                strcpy(file_names[i],file_names[m]);
                strcpy(file_names[m],temp);
            }
        }
    }

    for(i=0;i<j;i++)
    {
        printf("%s  ",file_names[i]);

    }
    printf("\n");
    closedir(dh);
}

void _ls_a(char *dir)
{
    struct dirent *d;
    struct stat fileStat;
    DIR *dh = opendir(dir);

    if(!dh) {
        if (errno == ENOENT) {

            perror("Directory does not exist");
        }
        else {
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }

    char file_names[100][100];
    int j = 0;

    while ( (d = readdir(dh)) != NULL) {

        strcpy(file_names[j],d->d_name);
        j++;

    }

    char temp[100];
    int i,m;
    for(i=0;i<j;i++)
    {
        for(m=i;m<j;m++)
        {
            if(strcmp(file_names[i],file_names[m])>0)
            {
                strcpy(temp,file_names[i]);
                strcpy(file_names[i],file_names[m]);
                strcpy(file_names[m],temp);
            }
        }
    }

    for(i=0;i<j;i++)
    {
        printf("%s  ",file_names[i]);

    }
    printf("\n");
    closedir(dh);
}

void _ls_t(char *dir)
{
    struct dirent *d;
    struct stat fileStat;
    DIR *dh = opendir(dir);

    if(!dh) {
        if (errno == ENOENT) {

            perror("Directory does not exist");
        }
        else {
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }

    int file_count = 0;

    while ( (d = readdir(dh)) != NULL) {
        stat(d->d_name, &fileStat);
        if (d->d_name[0] == '.') continue;
        file_count++;
    }
    closedir(dh);
    struct arr {
        char fileName[80];
        time_t time;
    }fs[file_count];

    int a = 0;
    DIR *dl = opendir(dir);

    while ( (d = readdir(dl)) != NULL) {

        if (d->d_name[0] == '.') continue;
        stat(d->d_name, &fileStat);
        strcpy(fs[a].fileName, d->d_name);
        fs[a].time = fileStat.st_mtime;
        a++;
    }
    closedir(dl);
    int i, j;
    for (i = 0; i < file_count - 1; i++) {
        for (j = 0; j < (file_count - 1 - i); j++) {

            if (fs[j].time < fs[j+1].time) {
                char name_temp[20];
                strcpy(name_temp, fs[j].fileName);
                time_t time_temp = fs[j].time;
                strcpy(fs[j].fileName, fs[j+1].fileName);
                fs[j].time = fs[j+1].time;
                strcpy(fs[j+1].fileName, name_temp);
                fs[j+1].time = time_temp;
            }
        }
    }

    char mod_time[80];

    for (i = 0; i < file_count; i++) {
        printf("%s  ", fs[i].fileName);
        //strftime(mod_time, 80, "%B\t%d %H:%M", localtime(&fs[i].time));
        //printf("%s\n", mod_time);
    }
    printf("\n");

}

void _ls_l(const char *dir) {

    struct dirent *d;
    struct stat fileStat;
    struct passwd *pwd;
    struct group *grp;
    struct tm dt;
    DIR *dh = opendir(dir);

    if(!dh) {
        if (errno == ENOENT) {

            perror("Directory does not exist");
        }
        else {
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }

    while ( (d = readdir(dh)) != NULL) {

        if (d->d_name[0] == '.') continue;

        //FILE PERMISSIONS
        stat(d->d_name, &fileStat);
        int fileMode = fileStat.st_mode;
        printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf( ((fileMode & S_IRUSR) && (fileMode & S_IREAD)) ? "r" : "-");
        printf( ((fileMode & S_IWUSR) && (fileMode & S_IWRITE)) ? "w" : "-");
        printf( ((fileMode & S_IXUSR) && (fileMode & S_IEXEC)) ? "x" : "-");
        printf( ((fileMode & S_IRGRP) && (fileMode & S_IREAD)) ? "r" : "-");
        printf( ((fileMode & S_IWGRP) && (fileMode & S_IWRITE)) ? "w" : "-");
        printf( ((fileMode & S_IXGRP) && (fileMode & S_IEXEC)) ? "x" : "-");
        printf( ((fileMode & S_IROTH) && (fileMode & S_IREAD)) ? "r" : "-");
        printf( ((fileMode & S_IWOTH) && (fileMode & S_IWRITE)) ? "w" : "-");
        printf( ((fileMode & S_IXOTH) && (fileMode & S_IEXEC)) ? "x" : "-");
        printf(" ");

        //NUMBER OF LINKS
        printf("%ld", (long) fileStat.st_nlink);
        printf(" ");

        //OWNER
        if ( (pwd = getpwuid(fileStat.st_uid)) != NULL) {
            printf("%-s", pwd->pw_name);
        }
        else {
            printf("%-d", fileStat.st_uid);
        }
        printf(" ");

        //GROUP OWNER
        if ((grp = getgrgid(fileStat.st_gid)) != NULL)
            printf("%-s ", grp->gr_name);
        else
            printf("%-d ", fileStat.st_gid);
        //printf(" ");

        //FILE SIZE
        printf("%5jd ", (intmax_t)fileStat.st_size);

        char mod_time[80];
        strftime(mod_time, 80, "%B\t%d %H:%M", localtime(&fileStat.st_mtime));
        printf("%s ", mod_time);

        //FILE or DIRECTORY NAME
        printf("%s", d->d_name);
        printf("\n");
    }
    closedir(dh);
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        _ls(".");
    }
    else if (argc == 2) {

        if (argv[1][0] == '-') {

            int op_a = 0, op_l = 0, op_t = 0;
            char *p = argv[1] + 1;

            if (*p == 'a') _ls_a(".");
            else if (*p == 't') _ls_t(".");
            else if (*p == 'l') _ls_l(".");

            else {
                perror("Unknown option error");
                //exit("EXIT_FAILURE");
            }
        }

        else {
            perror("Command not available");
            //exit("EXIT_FAILURE");
        }
    }

    return 0;
}

