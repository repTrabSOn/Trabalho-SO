#ifndef GLOBAIS_H
#define GLOBAIS_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

typedef enum {THREAD, IF, ELSE}tipo;

using namespace std;

typedef struct Celula c;
struct Celula{
	tipo classe;
	vector<int> p;
	vector<int> v;
	vector<*c> filhos;
};

/*

//comandos p's e v's
typedef struct pv{
	char c, local;
}pv;

//////// ESTRUTURAS DE DADOS
typedef struct c{
	char arg[20], comando;
	vector<struct c> comandos_internos;
	vector<pv>
}c;


typedef struct estrutura{
	vector<c> comandos;
	vector<int> sem;
}estrutura;

*/





#endif
