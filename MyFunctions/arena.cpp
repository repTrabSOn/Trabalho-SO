#include "globais.h"

class Carro{
public:
	std::vector<rect> rodas_articuldas;
	std::vector<rect> rodas_estaticas;
	std::vector<rect> partes_estaticas;
	std::vector<rect> armas;
	std::vector<circ> details;
	std::vector<circ> tiros;
	std::vector<circ> fogs;
	std::vector<sensor> sensores;
	trans t_carro;
	float vel_carro, vel_tiro, range_tiro;
	void acelerar(unsigned char key, bool turbo, float rot, float l_inf, float l_sup, std::vector<circ> inimigos);
	void limpa_tiros(void);
	bool colisao(float new_x, float new_y, float rot, float l_inf, float l_sup, std::vector<circ> inimigos);
	float dist(float x1, float y1, float x2, float y2);
};

void Carro::acelerar(unsigned char key, bool turbo, float rot, float l_inf, float l_sup, std::vector<circ> inimigos){
	float desloc_x = vel_carro * cos((t_carro.rz + ANG_REF) * M_PI / 180.0);
	float desloc_y = vel_carro * sin((t_carro.rz + ANG_REF) * M_PI / 180.0);


	if(key == 'w'){//para frente
		if(turbo){
			desloc_x *= VEL_TURBO;
			desloc_y *= VEL_TURBO;
		}
		if(!colisao(desloc_x, desloc_y, rot, l_inf, l_sup, inimigos)){
			t_carro.tx += desloc_x;
			t_carro.ty += desloc_y;
			t_carro.rz += rot;
			for(int i = 0; i < sensores.size(); i++){
				sensores[i].x += desloc_x;
				sensores[i].y += desloc_y;
			}
		}
	}
	else if(key == 's'){//ré
		if(!colisao(-desloc_x, -desloc_y, rot, l_inf, l_sup, inimigos)){
			t_carro.tx -= desloc_x;
			t_carro.ty -= desloc_y;
			t_carro.rz += rot;
			for(int i = 0; i < sensores.size(); i++){
				sensores[i].x -= desloc_x;
				sensores[i].y -= desloc_y;
			}	
		}
	}
}

void Carro::limpa_tiros(void){
	if(!tiros.empty()){
		for(int i = 0; i < tiros.size(); i++){
			float d = sqrt(pow(tiros[i].t.tx - x_centro, 2) + pow(tiros[i].t.ty - y_centro, 2));
			if(d > raio_maior || d < raio_menor){
				tiros[i] = tiros[tiros.size() - 1];
				tiros.pop_back();
				i--;
			}

		}
	}
}

float Carro::dist(float x1, float y1, float x2, float y2){
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrt(dx*dx + dy*dy);
}


bool Carro::colisao(float new_x, float new_y, float rot, float l_inf, float l_sup, std::vector<circ> inimigos){
	//colisao com os limites da arena
			std::vector<sensor> s_aux = sensores;

	if(rot != 0){
		float c_ang = cos((rot) * M_PI / 180.0);
		float s_ang = sin((rot) * M_PI / 180.0);


		for(int i = 0; i < s_aux.size(); i++){
				float d_x = s_aux[i].x - t_carro.tx;
				float d_y = s_aux[i].y - t_carro.ty + dist_centro_rot_chassi;
				float aux_dx = d_x;
				float aux_dy = d_y;

				d_x = d_x*c_ang + d_y*-s_ang;
				d_y = aux_dx*s_ang + aux_dy*c_ang;

				d_x += t_carro.tx;
				d_y += t_carro.ty;

				s_aux[i].x = d_x;
				s_aux[i].y = d_y - dist_centro_rot_chassi;

		}
	}

	float r = (c_chassi/2.0 + c_canhao/2.0 + dist_centro_rot_canhao)* ESCALA;

	bool flagResp = false;

	for(int j = 0; j < s_aux.size(); j++){
		for(int i = 0; i < inimigos.size(); i++){
			float d = dist(s_aux[j].x + new_x, s_aux[j].y + new_y, inimigos[i].t.tx, inimigos[i].t.ty);
			if(inimigos[i].tipo == TIPO_PISTA){
				if(d - r < l_inf || d + r > l_sup){
					flagResp = true;
				}

			}
			else if(inimigos[i].tipo == TIPO_INIMIGO){
				if(d - r < inimigos[i].raio){
					flagResp  = true;
				}
			}
		}
	}

	if(!flagResp){
		sensores = s_aux;
	}

	return flagResp;
}

class Arena{
public:
	std::vector<circ> circs;
	std::vector<rect> rects;
	std::vector<Carro> cars;
	trans t_arena;
};

