#include "globais.h"
#include "arena.cpp"

#define PATH_CONFIG "config.xml"

using namespace std;

Arena load_config_file(char * path); 				//OK
Arena get_arena_svg(char * path, float vel_tiro); 	//OK

/////////////////////////////////////////////////////////////////////
Arena load_config_file(char * path){
	TiXmlDocument doc;

	Arena arena;

	if(path != NULL){
		strcat(path, PATH_CONFIG);
		if(!doc.LoadFile(path))
			return arena;
	}else{
		if(!doc.LoadFile(PATH_CONFIG))
			return arena;
	}

	//tag principal do arquivo xml
	TiXmlElement* root = doc.FirstChildElement();

	//tag arquivoDaArena
	TiXmlElement* principal = root->FirstChildElement();

	string nameTag = principal->Value();
	if(nameTag == "arquivoDaArena"){
		const char * nome_arq = principal->Attribute("nome");
		const char * tipo_arq = principal->Attribute("tipo");
		const char * caminho_arq = principal->Attribute("caminho");

		principal = principal -> NextSiblingElement();

		const char * vel_tiro = principal->Attribute("velTiro");

		char local_arq[500];
		if(caminho_arq != NULL){
			strcpy(local_arq, caminho_arq);
			strcat(local_arq, nome_arq);
			strcat(local_arq, ".");
			strcat(local_arq, tipo_arq);
		}else{
			strcpy(local_arq, nome_arq);
			strcat(local_arq, ".");
			strcat(local_arq, tipo_arq);
		}
		
		return get_arena_svg(local_arq, atof(vel_tiro));
	}

	doc.Clear();

	return arena;
}

Arena get_arena_svg(char * path, float vel_tiro){

	Arena arena;

	TiXmlDocument doc;

	if(path != NULL){
		if(!doc.LoadFile(path))
			return arena;
	}else{
		return arena;
	}	
	
	//tag principal == svg
	TiXmlElement* root = doc.FirstChildElement();

	if(root == NULL){
		doc.Clear();
		return arena;
	}

	const char * cx, * cy, * r, * fill_c, * id_c; //circle
	const char * x, * y, * altura, * largura, * fill_r, * id_r; // rect

	//primeira tag dentro do svg, CIRCLE
	TiXmlElement* principal = root->FirstChildElement();

	do{
		string elemName = principal->Value();

		if(elemName == "circle"){
			fill_c = principal->Attribute("fill");
			cx = principal->Attribute("cx");
			cy = principal->Attribute("cy");
			r = principal->Attribute("r");
			id_c = principal->Attribute("id");
		
			if(!strcmp(id_c, "Pista")){ //itens da arena
				circ c;
				c.raio = atof(r);
				c.t.tx = atof(cx); //desenhos feitos no centro..
				c.t.ty = atof(cy);
				c.c.r = 0.0; c.c.g = 0.0; c.c.b = 1.0;
				c.tipo = TIPO_PISTA;
				arena.circs.push_back(c);

			}
			else if(!strcmp(id_c, "Inimigo")){
				circ c;
				c.raio = atof(r);
				c.t.tx = atof(cx); //desenhos feitos no centro..
				c.t.ty = atof(cy);
				c.c.r = 1.0; c.c.g = 0.0; c.c.b = 0.0;
				c.tipo = TIPO_INIMIGO;
				arena.circs.push_back(c);
			}
			else if(!strcmp(id_c, "Jogador")){
				ESCALA = atof(r)/(dist_centro_rot_canhao + (c_canhao/2.0) + (c_chassi/2.0));				
				Carro c;
				c.vel_tiro = vel_tiro;
				c.t_carro.tx = atof(cx);
				c.t_carro.ty = atof(cy);
				arena.cars.push_back(c);
			}
		}
		else if(elemName == "rect"){
			x = principal->Attribute("x");
			y = principal->Attribute("y");
			altura = principal->Attribute("height");
			largura = principal-> Attribute("width");
			fill_r = principal->Attribute("fill");
			id_r = principal->Attribute("id");
			
			rect r;
			r.tipo = TIPO_LARG_CHEGADA;
			r.comp = atof(altura);
			r.larg = atof(largura);
			r.t.tx = atof(x) + r.larg / 2.0;
			r.t.ty = atof(y) + r.comp / 2.0;
			arena.rects.push_back(r);
		}
		principal = principal -> NextSiblingElement();

	}while(principal != NULL);

    doc.Clear();
    return arena;
}
