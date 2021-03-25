#ifndef __001_H

#define __001_H
#include <sys/stat.h>
int stat_i(char *arr);
char fileType(const struct stat res);
char *fileMode(const struct stat res);
long fileNlink(const struct stat res);
char *fileUidName(const struct stat res);
char *fileGidName(const struct stat res);
long fileSize(const struct stat res);
char *fileTime(const struct stat res);
int stat_l(char *arr);


#endif
