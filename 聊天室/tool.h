#ifndef TOOL_H
#define TOOL_H

#include <stdio.h>
#include "all.h"

char *getCurentTime(char *str);
void splitStringByCh(char *str,char ch,char *pre,char *next);
int handleString(char *str,char (*person)[MINSIZE],char *msg);

int checkFileIsExist(char *fileName);
#endif /* TOOL_H */