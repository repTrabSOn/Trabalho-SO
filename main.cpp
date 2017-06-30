#include "parser.cpp"


typedef int t_data;

typedef vector<vector <t_data> > matriz;

matriz aloca_matriz(int l, int c);


int main(int argc, char * argv[]){

	data d = get_data();

	matriz m = aloca_matriz(d.threads.size(), d.sem.size());


	for(int i = 0; i < d.threads.size(); i ++){
		for(int j= 0; j < d.sem.size(); j++){
			 m[i][j]= 1;
		}
	
	}

	cout << "vetor de recursos: " << endl << "| ";
	for(int i = 0; i < d.sem.size(); i++){
		cout << d.sem[i] << " | ";
	}
	cout << endl;
	cout << "Matriz de recursos: " << endl;
	for(int i = 0; i < d.threads.size(); i ++){
		cout << "| ";
		for(int j= 0; j < d.sem.size(); j++){
			cout << " " << m[i][j] << " |";
		}
		cout << endl;
	}	

	return 0;
}


matriz aloca_matriz(int l, int c){
	matriz m(l, vector<t_data>(c));
	return m;
}

