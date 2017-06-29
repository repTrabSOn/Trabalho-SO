#include "globais.h"


vector<estrutura> get_estruturas(void);
int conta_caracter(char * str, char c);

int main(int argc, char * argv[]){

	vector<estrutura> e = get_estruturas();

	return 0;
}

int conta_caracter(char * str, char c){
	int cont = 0;
	for(; *str; str++){
		if(*str == c){
			cont++;
		}
	}
	return cont;
}

vector<estrutura> get_estruturas(void){
	char text[200];
	vector<estrutura> v;
	
	//representa a quantidade de tabs de cada if que surge no codigo
	vector<int> if_tabs;
	//representa a quantidade de tabs de cada else que surge no codigo
	vector<int> else_tabs;

	int cont = 0;

	//fazer a leitura dos semaforos




	//leitura dos comandos
	while(!feof(stdin)){
		gets(text);
		char * cadeia_simbolos, var_auxiliar;

		var_auxiliar = text;
		cadeia_simbolos = strtok(text, " \n\t");

		int qtd_tabs = conta_caracter(var_auxiliar, '\t');


		if(!strcmp(cadeia_simbolos, "thread")){
			c comando;
			comando.comando = THREAD;
		}


		if(!strcmp(cadeia_simbolos, "if")){
			//novo if encontrado
			//+ 1 pq a identacao dos comandos internos deverao estar com mais uma tab
			if_tabs.push_back(qtd_tabs + 1);
		}
		else if(!if_tabs.empty()){
			if(if_tabs.back() == (qtd_tabs + 1)){
				//é um comando aninhando dentro do ultimo if


			}else{
				//terminou o ultimo comando if
				if_tabs.pop_back();
			}
		}

		if(!strcmp(cadeia_simbolos, "else")){
			else_tabs.push_back(qtd_tabs + 1);

		}
		else if(!else_tabs.empty()){
			if(else_tabs.back() == (qtd_tabs + 1)){
				//comando a pertencente de else
			}else{
				//fim deste comando else
				else_tabs.pop_back();
			}
		}


		while(cadeia_simbolos != NULL){
			//cout << cadeia_simbolos << endl;
			cadeia_simbolos = strtok(NULL, " \n\t");
			cont++;
		}
		cout << endl;
	}

	cout << cont << " argumentos " << endl;
	return v;
}




/*

#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}

*/