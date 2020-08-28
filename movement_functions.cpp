#include "header.h"

string pos_as_string(casa start){
	// Underline evita que sejam geradas chaves iguais para casas diferentes no tabuleiro (i.e. x=1;y=21 -> 1_21 || x=12;y=1 -> 12_1
	return ( to_string(start.posX) + "_" + to_string(start.posY) );
}

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

