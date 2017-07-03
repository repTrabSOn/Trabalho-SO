#include "parser.cpp"


typedef int t_data;


typedef struct pt{
	unsigned x, y;
}pt;


typedef vector<vector <t_data> > matriz;

matriz aloca_matriz(int l, int c);


void exibe_matriz(matriz m);

//funcao que pega uma pilha de comandos e monta a matriz para o Caio detectar o deadlock
matriz cria_matriz_deteccao(vector<stack<comando> > threads, unsigned int qdt_recursos);

int main(int argc, char * argv[]){

	data d = get_data();

	matriz m = aloca_matriz(d.threads.size(), d.sem.size());


	for(int i = 0; i < d.threads.size(); i ++){
		for(int j= 0; j < d.threads[i].comandos.size(); j++){
			tipo t = d.threads[i].comandos[j].comando;
			if(t == IF || t == V){
				d.threads[i].last_index = j;
				//break;
			}else{
				if(t == P){
					m[i][d.threads[i].comandos[j].valor]++;
				}
			}
		}
	
	}

	exibe_matriz(m);

	cout << endl << endl;



	return 0;
}

void exibe_matriz(matriz m){
	for(int i = 0; i < m.size(); i++){
		for(int j = 0; j < m[i].size(); j++){
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}
}

matriz aloca_matriz(int l, int c){
	matriz m(l, vector<t_data>(c));
	int i, j;
	for(i = 0; i < l; i++){
		for(j = 0; j < c; j++){
			m[i][j] = 0;
		}
	}
	return m;
}

matriz cria_matriz_deteccao(vector<leitor > threads, unsigned int qdt_recursos){
	//a criação da matriz conta a disposição dos recursos e processos como uma matriz de adjacências
	unsigned int tam = threads.size() + qdt_recursos;
	matriz resp = aloca_matriz(tam, tam);

	int i;
	for(i = 0; i < threads.size(); i++){
		while(!(*threads[i].comandos).empty()){
			comando c = (*threads[i].comandos).top();
			//marcando a solicitação do recurso
			resp[i][c.valor] = 1;
			resp[c.valor][i] = 1;
			(*threads[i].comandos).pop();
		}
	}
	return resp;
}

bool detecta_deadlock(matriz m, int x, int y){
	int cont = 0;
	int i, x_ref = y;
	vector<pt> pts;
	
	for(i = 0; i < m[x_ref].size(); i++){
		if(m[x_ref][i] != 0 && x_ref != i){
			cont++;
			x_ref = i;
			if(cont >= 4 && i == x){//condicao que aparenta o menor deadlock possível
				//tem deadlock nessa porra
				return true;
			}
		} 
	}
	return false;
}

bool percorre_matriz(matriz m){
	int i, j;
	bool deadlock = false;
	for(i = 0; i < m.size(); i++){
		for(j = 0; j < m[i].size(); j++){
			if(m[i][j] == 1){
				deadlock = detecta_deadlock(m, i, j);
				if(deadlock){
					return deadlock;
				}
			}

		}
	}
	return deadlock;
}



