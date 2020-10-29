#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
0 = livre
1 = parede
2 = visitado
3 = beco
*/

bool typeLab = true;
const int n = 15;
char lab[n][n];

typedef struct _nodo{
	int x = 1;
	int y = 1;
	struct _nodo *next;
	struct _nodo *retorno;
}Pilha;

void printStack(Pilha *temp){
	Pilha *aux;
	aux = temp;
	while(aux != NULL){
		cout<<aux->x<<" "<<aux->y<<endl;
		aux = aux->next;
	}
}

void push(Pilha *temp, int x, int y){
	Pilha *aux = temp;
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = new Pilha;
	aux->next->x = x;
	aux->next->y = y;
	aux->next->next = NULL;
	// fim do push
//	temp->next->x = x;
//	temp->next->y = y;
	lab[x][y] = 'C';
	lab[temp->x][temp->y] = '.';

}

void pop(Pilha *temp){
	Pilha *aux = temp;
	while(aux->next->next != NULL){
		aux = aux->next;
	}
	lab[aux->next->x][aux->next->y] = '.';
	aux->next = NULL;
	lab[aux->x][aux->y] = 'C';
	
}

void printLab(){
	system("cls");
	cout<<" "<<endl;
	int i;
	int j;
	for(i=0; i < n; i++ ){
		for(j=0; j < n; j++){
			cout<<lab[i][j];
		}
		cout<<""<<endl;
	}
}

void criarLab(){
	int i;
	int j;
	srand((unsigned)time(0));
	int maior = 1;
	int menor = 0;
	for(i=0; i < n; i++ ){
		for(j=0; j < n; j++){
			if((i == 0 || j== 0) || (i == n-1 || j== n-1)){
				lab[i][j] = '+';
			}else if(i == 1 && j == 1){
				lab[i][j] = 'C';
			}else if(i == n-2 && j == n-2){
				lab[i][j] = '$';
			}else{
				int aleatorio = rand()%(maior-menor+1) + menor;
				switch(aleatorio){
					case 0:
						lab[i][j] = ' ';
						break;
					case 1:
						lab[i][j] = '+';
						break;
				}
			}
		}
	}
	
}

void enpilhar(Pilha *temp, int x, int y){
	temp->next = new Pilha;
	temp->next->next = NULL;
	temp->next->x = x;
	temp->next->y = y;
	lab[x][y] = 'C';
	lab[temp->x][temp->y] = '.';
		
}

void encontrarSaida(Pilha *aux){
	Pilha *temp = aux;
	while(temp->next != NULL){
		temp = temp->next;
	}
	if(lab[temp->x +1][temp->y] == ' '){
		push(temp, temp->x+1, temp->y);
	}else if(lab[temp->x][temp->y + 1] == ' '){
		push(temp, temp->x, temp->y + 1);
	}else if(lab[temp->x][temp->y - 1] == ' '){
		push(temp, temp->x, temp->y - 1);
	}else if(lab[temp->x - 1][temp->y] == ' '){
		push(temp, temp->x - 1, temp->y);
	}else if((lab[temp->x +1][temp->y] == '+') && (lab[temp->x][temp->y + 1] == '+') && (lab[temp->x][temp->y - 1] == '+') && (lab[temp->x - 1][temp->y] == '+')){
		cout<<"\n\nLabrinto sem solucao cod1"<<endl;
		typeLab = false;
	}else if((lab[1][1] == 'C') && (lab[2][1] == '.' || lab[2][1] == '.')){
		cout<<"\n\nLabrinto sem solucao cod2"<<endl;
		typeLab = false;
	}else if(temp->x == 13 && temp->y == 13){
		cout<<"\n\nAchouuuuuu2"<<endl;
		typeLab = false;
	}
	else{
		pop(aux);
	}
	/*
	else if((temp->x == 1  && temp->y == 1) && (lab[temp->x + 1][temp->y] == '.' && lab[temp->x][temp->y + 1] == '.')){
		cout<<"\n\nLabrinto sem solucao cod2"<<endl;
	}
	*/
	
}

int main(){
	criarLab();
	printLab();
	Pilha *pilha = new Pilha;
	pilha->next = NULL;
	pilha->x = 1;
	pilha->y = 1;
	pilha->retorno = NULL;
	
	while(typeLab){
		printLab();	
		encontrarSaida(pilha);
		//printLab();	
	}
	
	//encontrarSaida(pilha);
	//printLab();

	



/*
	push(pilha, 1,1);
	push(pilha, 1,2);
	push(pilha, 2,2);
	push(pilha, 3,2);
	pop(pilha);
	pop(pilha);
	push(pilha, 5,9);
//	pop(pilha);
*/
	printStack(pilha);
//	push(pilha, 10,10);
//	printStack(pilha);

	return 0;
}
