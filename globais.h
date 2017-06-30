#ifndef GLOBAIS_H
#define GLOBAIS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define _THREAD "thread"
#define _IF "if"
#define _ELSE "else"
#define _P "P"
#define _V "V"
#define SEPARADOR_FULL " \t"
#define SEPARADOR_TAB '\t'
#define TAM_MAX 200


typedef enum {IF, ELSE, P, V}tipo;

using namespace std;

typedef struct Thread thread;
typedef struct Comandos comando;
typedef struct Data data;

//thread
struct Comandos{
	char condicao[20];
	tipo comando;
	//esse valor vai fazer sentido dependendo do comando
	unsigned int tabs;
	//semaforo
	unsigned char valor;
};

struct Thread{
	char nome[20];
	unsigned int last_index;
	vector<comando> comandos;
};

struct Data{
	vector<thread> threads;
	vector<int> sem;
};

#endif
