
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>//para utilizar a função usleep (linux)


using namespace std;

/*labrinto
' ' = livre
'+' = parede
'.' = visitado
'*' = beco
*/

/*Status do labrindo
0 = explorando
1 = labrindo sem solução
2 =  labrindo concluido
*/

int typeLab = 0;//status do labrindo
const int n = 10;//tamanho do labrinto
char lab[n][n];

typedef struct _nodo{//nodo para locomoção e armazenamento caminho do labrinto
	int x;
	int y;
	struct _nodo *next;
}Pilha;

void printStack(Pilha *temp){//função para mostrar a lista encadeada
	Pilha *aux;
	aux = temp;
	while(aux != NULL){
		cout<<aux->x<<" "<<aux->y<<endl;
		aux = aux->next;
	}
}

void push(Pilha *temp, int x, int y){//função para adicionar um nodo no final da lista
	Pilha *aux = temp;
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = new Pilha;
	aux->next->x = x;
	aux->next->y = y;
	aux->next->next = NULL;
	// fim do push
	lab[x][y] = 'C';
	lab[temp->x][temp->y] = '.';

}

void pop(Pilha *temp){//função para remover o ultimo nodo da lista
	Pilha *aux = temp;
	while(aux->next->next != NULL){
		aux = aux->next;
	}
	lab[aux->next->x][aux->next->y] = '.';
	aux->next = NULL;
	lab[aux->x][aux->y] = 'C';
	
}

void printLab(){//função para mostrar o labrinto
	system("clear");//para linux
	//system("cls"); para windows
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

void criarLab(){//função para criar um labrinto aleatorio
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


void encontrarSaida(Pilha *aux){//função para checar o status da posição atual e saber como proceder
	usleep(100000);//usar para linux
	Pilha *temp = aux;
	while(temp->next != NULL){
		temp = temp->next;
	}
	if(lab[n-2][n-2] == 'C'){
		typeLab = 2;
	}else if(lab[temp->x +1][temp->y] == ' ' || lab[temp->x +1][temp->y] == '$'){
		push(temp, temp->x+1, temp->y);
	}else if(lab[temp->x][temp->y + 1] == ' ' || lab[temp->x][temp->y + 1] == '$'){
		push(temp, temp->x, temp->y + 1);
	}else if(lab[temp->x][temp->y - 1] == ' '){
		push(temp, temp->x, temp->y - 1);
	}else if(lab[temp->x - 1][temp->y] == ' '){
		push(temp, temp->x - 1, temp->y);
	}else if((lab[temp->x +1][temp->y] == '+') && (lab[temp->x][temp->y + 1] == '+') && (lab[temp->x][temp->y - 1] == '+') && (lab[temp->x - 1][temp->y] == '+')){
		typeLab = 1;
	}else if((lab[1][1] == 'C') && (lab[2][1] == '.' || lab[1][2] == '.')){
		typeLab = 1;
	}else{
		pop(aux);
	}

	
}

void run(){
	
		typeLab = 0;
		Pilha *pilha = new Pilha;
		criarLab();
		printLab();
		pilha->next = NULL;
		pilha->x = 1;
		pilha->y = 1;
		
		while(typeLab == 0){
			printLab();	
			encontrarSaida(pilha);
			//printLab();	
		}
		if(typeLab == 2){
			cout<<"\n\nLabrinto concluido!"<<endl;
			cout<<"\n\nSolucao encontrada: "<<endl;
			printStack(pilha);
		}else{
			cout<<"\n\nLabrinto sem solucao"<<endl;
		} 
	
	
}

int main(){
	int opcoes = 0;
	do{
	run();
	cout<<"\n\nTecle '0' para gerar um novo labrinto: ";
	cin>>opcoes;
	}while(opcoes == 0);

	return 0;
}
