#include "header.h"

string pos_as_string(int posX,int posY){
	// Underline evita que sejam geradas chaves iguais para casas diferentes no tabuleiro (i.e. x=1;y=21 -> 1_21 || x=12;y=1 -> 12_1
	return ( to_string(posX) + "_" + to_string(posY) );
}

bool compare(const casa h1,const casa h2){
	return (h1.jump_steps < h2.jump_steps);
}
