#include "header.h"

string pos_as_string(casa start){
	return ( to_string(start.posX) + to_string(start.posY) );
}

casa mov_Esquerda(casa start){
	casa aux;
	aux = start;
	aux.posY -= start.jump_steps;
	return aux;
}

casa mov_Direita(casa start){
	casa aux;
	aux = start;
	aux.posY += start.jump_steps;
	return aux;
}

casa mov_Cima(casa start){
	casa aux;
	aux = start;
	aux.posX -= start.jump_steps;
	return aux;
}

casa mov_Baixo(casa start){
	casa aux;
	aux = start;
	aux.posX += start.jump_steps;
	return aux;
}

