#include "header.h"

casa mov_Esquerda(casa start){
	casa aux;
	aux = start;
	aux.posY -= start.jump_steps;
	aux.pos = pos_as_string(aux);
	return aux;
}

casa mov_Direita(casa start){
	casa aux;
	aux = start;
	aux.posY += start.jump_steps;
	aux.pos = pos_as_string(aux);
	return aux;
}

casa mov_Cima(casa start){
	casa aux;
	aux = start;
	aux.posX -= start.jump_steps;
	aux.pos = pos_as_string(aux);
	return aux;
}

casa mov_Baixo(casa start){
	casa aux;
	aux = start;
	aux.posX += start.jump_steps;
	aux.pos = pos_as_string(aux);
	return aux;
}

