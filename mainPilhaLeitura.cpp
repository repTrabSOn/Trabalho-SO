
#include <stack>
#include "globais.h"
#include "parser.cpp"
#include "deadlock.cpp"


/// Funcao que inicializa um leitor
leitor *iniLeitor (void){
	leitor *novo = (leitor*)malloc(sizeof(leitor));
	if (novo != NULL){
		novo->a = EMPILHA;
		novo->index = 0;
		novo->flagV = 0;
		novo->comandos = new vector<comando>();
	}
	return novo;
}

/// Funcao de inicializacao do vetor de leitores
vector<leitor> iniVetLeitor (int qtd){
	int i;
	vector<leitor> novo;
	for(i = 0; i < qtd; i++){
		leitor *l = iniLeitor();
		novo.push_back(*l);
	}
	return novo;
}

/// Funcao que varre o vetor de comandos a partir de uma determinada posicao do ELSE em determinada tabulacao
int procuraElse (vector<comando> v, int index, int qtdTabs){
	int resp = -1, i;
	for (i = index; i < v.size(); i++){
		/// Verifica se e um comando else e se este e o correto pela tabulacao
		if (v[i].comando == ELSE && v[i].tabs == qtdTabs)
			resp = i;
	}
	return resp;
}

/// Funcao principal que le os comandos da estrutura de dados e testa varias combinacoes
bool leComandos (data d){
	int i,j,k;
	int tabAux = MAX;
	int termina = 0;
	bool deadlock = false;

	/// Vetor contendo uma pilha para cada thread do vetor de threads
	vector<leitor> leitores = iniVetLeitor(d.threads.size());

	for(k = 0; termina < d.threads.size() && !deadlock; k++){
		
		/// Percorre os vector para empilhar os processos		
		for (i = 0; i < leitores.size(); i++){
			
			printf("\nTHREAD %d\n", i+1);
			/// Verifica 
			if (leitores[i].index != MAX)
				j = leitores[i].index;
			else
				j = 0;

			//printf("valor teste:%d\n", d.threads[i].comandos[leitores[i].index].comando);

			for ( ; j < d.threads[i].comandos.size(); j++){
				// 2 casos principais, acao == empilha ou acao == desempilha
				if (leitores[i].a == EMPILHA && tabAux > d.threads[i].comandos[j].tabs){
					//printf("tab: %d\n", tabAux);
					if (d.threads[i].comandos[j].comando == IF || d.threads[i].comandos[j].comando == P){ //|| (*itComando).comando == V){
						leitores[i].comandos->push_back(d.threads[i].comandos[j]);
						leitores[i].index = j;
						//printf("%d/%d  %d-%d\n", j, (int)d.threads[i].comandos.size(), tabAux, d.threads[i].comandos[j].tabs);
						tabAux = MAX;
					}
					// Se for V
					else if (d.threads[i].comandos[j].comando == V){
						// Flag que indica se a pilha parou neste V
						// Se nao, entao seta o flag para 1
						if (leitores[i].flagV == 0){
							leitores[i].index = j;
							leitores[i].flagV = 1;
							//printf("\nAKI\n");
							break;
						}
						// Se sim, faz o ajuste no vector dos semaforos
						else{
							d.sem[d.threads[i].comandos[j].valor]++;
							leitores[i].flagV = 0;
							//printf("incrementou o vet\n");
						}
					}
					// Ignora os elses
					else{
						tabAux = d.threads[i].comandos[j].tabs+1;
					}
					// Verifica se os comandos acabaram
					if (j == d.threads[i].comandos.size()-1 && leitores[i].flagV == 0){
						leitores[i].a = DESEMPILHA;
						//printf("Desemp\n");
						break;
					}
				}
				else if (leitores[i].a == DESEMPILHA){
					
					//printf("tamanho desse caralho: %d\n", (int)leitores[i].comandos->size());
					while ( 0 < leitores[i].comandos->size()){
						//printf("\nAKI\n");
						// Desempilha ate encontrar um comando IF
						if (leitores[i].comandos->back().comando == IF){
							//printf("\nAKI\n");
							int indElse = procuraElse(d.threads[i].comandos, leitores[i].index, leitores[i].comandos->back().tabs);
							//printf("indElse: %d\n", indElse);
							if (indElse != -1){
								j = indElse;
								leitores[i].a = EMPILHA;
								leitores[i].index = j+1;
								tabAux = MAX;
							}
							else{
								j = d.threads[i].comandos.size()+1;
							}
							leitores[i].comandos->pop_back();
							break;
						}
						else{
							leitores[i].comandos->pop_back();
						}
					}
					if (leitores[i].comandos->size() == 0)
						termina++;

					//termina++;
				
				}
				else{
					printf("else ignorado\n");
				}
				if (j == d.threads[i].comandos.size()-1 && leitores[i].flagV == 0){
					if (tabAux != MAX)
						leitores[i].a = DESEMPILHA;
					break;
				}
/*
				// So imprime a zuera pra testar
				printf("comando: %d\n", leitores[i].comandos->back().comando);
				if (leitores[i].comandos->back().comando == IF || leitores[i].comandos->back().comando == ELSE)
					printf("%s\n", leitores[i].comandos->back().condicao);
				else
					printf("%d\n\n", leitores[i].comandos->back().valor);
				printf("\n\nmotherfuker\n\n");
*/				
			}
		}
		// Saindo deste for do demonio o vector de pilhas esta pronto pro primeiro teste de deadlock
		// INSIRA A FUNCAO DE TESTAR DEADLOCK AKI
		matriz m = cria_matriz_deteccao(leitores, d.sem.size());

		exibe_matriz(m);

		deadlock = percorre_matriz(m);


		if(deadlock){
			cout << "DEADLOCK DO CARALHO\n\n" << endl;
		}else{
			cout << "NAO tem deadlock nessa CARALHA\n\n" << endl;	
		}
	}

	// A intenção é fazer um while enquanto a função de deadlock der false ou acabar o vetor de comandos

	
	return true;
}

int main(void){
	data d = get_data();
	leComandos(d);

	return 0;
}