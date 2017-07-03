
#include <stack>
#include "globais.h"
#include "parser.cpp"
#include "deadlock.cpp"


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
			// 2 casos principais, acao == empilha ou acao == desempilha
			if ((*itLeitor).a == EMPILHA && tabAux != (*itComando).tabs){
				printf("tab: %d\n", tabAux);
				if ((*itComando).comando == IF || (*itComando).comando == P){ //|| (*itComando).comando == V){
					(*itLeitor).comandos->push((*itComando));
					(*itLeitor).index = j;
					tabAux = -1;
				}
				// Se for V
				else if ((*itComando).comando == V){
					(*itLeitor).index = j+1;
					break;
				}
				// Ignora os elses
				else{
					tabAux = (*itComando).tabs+1;
				}
			}
			else if ((*itLeitor).a == DESEMPILHA){
				
			}
			else{
				continue;
			}
			// So imprime a zuera pra testar
			printf("comando: %d\n", (*itLeitor).comandos->top().comando);
			if ((*itLeitor).comandos->top().comando == IF || (*itLeitor).comandos->top().comando == ELSE)
				printf("%s\n", (*itLeitor).comandos->top().condicao);
			else
				printf("%d\n\n", (*itLeitor).comandos->top().valor);
		}
	}
	// Saindo deste for do demonio o vector de pilhas esta pronto pro primeiro teste de deadlock
	// INSIRA A FUNCAO DE TESTAR DEADLOCK AKI
	matriz m = cria_matriz_deteccao(leitores, d.sem.size());

	exibe_matriz(m);

	bool resp = percorre_matriz(m);


	if(resp){
		cout << "DEADLOCK DO CARALHO" << endl;
	}else{
		cout << "NAO tem deadlock nessa CARALHA" << endl;	
	}

	// A intenção é fazer um while enquanto a função de deadlock der false ou acabar o vetor de comandos

	
	return true;
}

int main(void){
	data d = get_data();
	leComandos(d);

	return 0;
}