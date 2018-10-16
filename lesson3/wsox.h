#ifndef __WSOX__H__
#define __WSOX__H__

typedef void(*FN1)(int);
typedef void(*FN2)(int,char*);

#include <string.h>
#include <stdio.h>

void wsox(FN1 opnfn, FN2 msgfn, FN1 clsfn);

int wconn(char* url);
void wsend(int ws, char* data);
void wclose(int ws);

#endif//__WSOX__H__
