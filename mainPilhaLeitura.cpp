
#include <stack>
#include "globais.h"
#include "parser.cpp"


//Futura função que verificara o deadlock
void verificaDeadLock(void);


leitor *iniLeitor(){
	leitor *novo = (leitor*)malloc(sizeof(leitor));
	if (novo != NULL){
		novo->a = EMPILHA;
		novo->index = 0;
		novo->comandos = new stack<comando>();
	}
	return novo;
}

vector<leitor> iniVetLeitor(int qtd){
	int i;
	vector<leitor> novo;
	for(i = 0; i < qtd; i++){
		leitor *l = iniLeitor();
		novo.push_back(*l);
	}
	return novo;
}

int procuraElse (vector<comando> v){

}

bool leComandos (data d){
	int i,j,k;
	int tabAux = -1;
	int termina = 0;

	// Vetor contendo uma pilha para cada thread do vetor de threads
	vector<leitor> leitores = iniVetLeitor(d.threads.size());

	// Percorre os vector para empilhar os processos
	vector<leitor>::iterator itLeitor;
	vector<thread>::iterator itThread;
	vector<comando>::iterator itComando;
	for (i = 0, itLeitor = leitores.begin(), itThread = d.threads.begin(); itLeitor < leitores.end(); i++, itThread++, itLeitor++){
		printf("\nTHREAD %d\n", i+1);
		for (j = 0, itComando = (*itThread).comandos.begin(); itComando < (*itThread).comandos.end(); j++, itComando++){
			printf("tab: %d\n", tabAux);
			// 2 casos principais, acao == empilha ou acao == desempilha
			if ((*itLeitor).a == EMPILHA && tabAux != (*itComando).tabs){
				if ((*itComando).comando == IF || (*itComando).comando == P || (*itComando).comando == V){
					(*itLeitor).comandos->push((*itComando));
					(*itLeitor).index = j;
					tabAux = -1;
				}
				// Se for V
				else if ((*itComando).comando == V){
					(*itLeitor).index = j+1;
					// Termina a recursão nessa pilha
				}
				// Ignora os elses
				else{
					tabAux = (*itComando).tabs+1;
					printf("\nhere\n");
					break;
				}
			}
			else if ((*itLeitor).a == DESEMPILHA){

			}
			else{
				continue;
			}
			printf("comando: %d\n", (*itLeitor).comandos->top().comando);
			if ((*itLeitor).comandos->top().comando == IF || (*itLeitor).comandos->top().comando == ELSE)
				printf("%s", (*itLeitor).comandos->top().condicao);
			else
				printf("%d\n", (*itLeitor).comandos->top().valor);
		}
	}
	
	return true;
}

int main(void){
	data d = get_data();
	leComandos(d);

	return 0;
}