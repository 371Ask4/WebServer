#ifndef __CONFIG__H_
#define __CONFIG__H_

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <dirent.h>

#define MAX_CONFIG_LINE 80
#define PORT 0
#define PATH 1
#define THREADS 2

char** config;
void initFromConfig(char**);
#endif
