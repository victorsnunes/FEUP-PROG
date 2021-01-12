#include <iostream>
using namespace std;

//função para imprimir na tela do computador o estado atual do jogo;
void tela(int *endereco_sementes, int *endereco_total) {
	cout << "\n\n           Jogador 2" << endl;
	cout << "    f   e   d   c   b   a" << endl << "   ";
	for (int i = 11; i >= 6; i--) {
		if (*(endereco_sementes + i) < 10) {
			cout << " " << *(endereco_sementes + i) << "  ";
		}
		else {
			cout << " " << *(endereco_sementes + i) << " ";
		}
	}
	if (*(endereco_total + 1) > 9) {
		cout << endl << *(endereco_total + 1) << "                          " << *(endereco_total) << endl << "   ";
	}
	else {
		cout << endl << *(endereco_total + 1) << "                           " << *(endereco_total) << endl << "   ";
	}
	for (int i = 0; i <= 5; i++) {
		if (*(endereco_sementes + i) < 10) {
			cout << " " << *(endereco_sementes + i) << "  ";
		}
		else {
			cout << " " << *(endereco_sementes + i) << " ";
		}
	}
	cout << endl;
	cout << "    A   B   C   D   E   F" << endl;
	cout << "           Jogador 1\n\n";
}


//Função para fazer, se houver, as capturas necessárias
void capturar(int* endereco_sementes, int* endereco_total, int jogador, int ultima) {
	bool houveCaptura = false;	//Irá checar se houve capturas ou não

	//Caso a jogada tenha sido feita pelo jogador 1
	if (jogador == 1) {
		while (true) {
			if (ultima < 6) {	//Posição atual não está no território inimigo
				break;
			}
			else if (*(endereco_sementes + ultima) == 2 || *(endereco_sementes + ultima) == 3) {	//Posição atual está no território inimigo e possui 2 ou 3 sementes, e serão capturadas
				*endereco_total += *(endereco_sementes + ultima);
				*(endereco_sementes + ultima) = 0;
				ultima -= 1;
				houveCaptura = true;
			}
			else {		//Posição atual está no território inimigo mas não possui 2 ou 3 sementes
				break;
			}
		}
		if (houveCaptura) {		//Caso houver capturas
			cout << "\nCapturando...\n\n";
			tela(endereco_sementes, endereco_total);
		}
		else {					//Caso não houver capturas
			cout << "\nNao houve capturas\n\n";
		}
	}
	//Caso a jogada tenha sido feita pelo jogador 2
	else {
		while (true) {
			if (ultima > 5 || ultima < 0) {		//Posição atual não está no território inimigo
				break;
			}
			else if (*(endereco_sementes + ultima) == 2 || *(endereco_sementes + ultima) == 3) {	//Posição atual está no território inimigo e possui 2 ou 3 sementes, e serão capturadas
				*(endereco_total + 1) += *(endereco_sementes + ultima);
				*(endereco_sementes + ultima) = 0;
				ultima -= 1;
				houveCaptura = true;
			}
			else {		//Posição atual está no território inimigo mas não possui 2 ou 3 sementes
				break;
			}
		}
		if (houveCaptura) {		//Caso houver capturas
			cout << "\nCapturando...\n\n";
			tela(endereco_sementes, endereco_total);
		}
		else {					//Caso não houver capturas
			cout << "\nNao houve capturas\n\n";
		}
	}
}


//Faz a movimentação escolhida pelo jogador
void mover(int* endereco_sementes, int* endereco_total, char escolha, int jogador) {
	
	//Determinar o índice que corresponde à letra escolhida pelo jogador
	int index = 12;
	char caracteres[] = { 'A','B','C','D','E', 'F', 'a', 'b', 'c', 'd', 'e', 'f' };
	for (int i = 0; i < 12; i++) {
		if (caracteres[i] == escolha) {
			index = i;
			break;
		}
	}

	//Descartar escolhas inválidas
	if (index == 12 || (jogador == 1 && index > 5) || (jogador == 2 && index < 6) || *(endereco_sementes + index) == 0) {
		cout << "\nEscolha invalida!\n\n";
		cout << "Escreva a letra da posicao para realizar sua jogada: ";
		cin >> escolha;
		cin.ignore(1000, '\n');
		mover(endereco_sementes, endereco_total, escolha, jogador);
	}
	else {
		int quantidade = *(endereco_sementes + index);	//Quantidade de posições para distribuir as sementes
		int ultima = (index + quantidade) % 12;			//Armazena o valor da última posição, que será útil para a função "capturar"
		*(endereco_sementes + index) = 0;				//Esvazia a posição escolhida
		for (int i = 1; i <= quantidade; i++) {			//Adiciona uma semente em cada posição subsequente
			*(endereco_sementes + ((index + i) % 12)) += 1;
		}
		cout << "\n\n" << "Movendo...\n";
		tela(endereco_sementes, endereco_total);
		capturar(endereco_sementes, endereco_total, jogador, ultima);
	}
}


int main()
{
	int sementes[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};		//Array da quantidade de sementes em cada posição
	int total[] = {0, 0};										//Array do total de pontos de cada jogador
	char escolha;												//Posição escolhida pelo jogador
	int* endereco_sementes = &sementes[0];						//Pointer do array das sementes
	int* endereco_total = &total[0];							//Pointer do array do total de pontos dos jogadores
	int jogador = 1;											//Jogador 1 é quem começa

	cout << "Bem-vindo ao jogo Oware! Divirta-se :)\n\n";
	tela(endereco_sementes, endereco_total);

	//Loop que mantem o jogo em andamento, e só termina quando um dos jogadores passar de 24 sementes ou ocorrer um empate
	while (total[0] < 25 && total[1] < 25 && !((total[0] == 24) && (total[1] == 24))) {

		cout << "\nVez do Jogador " << jogador << endl;
		
		//Verifica se for a vez do jogador 1 e ele não possui sementes em seu território (neste caso ele captura todas as sementes do território adversário)
		if ((jogador == 1) && ((sementes[0] == 0) && (sementes[1] == 0) && (sementes[2] == 0) && (sementes[3] == 0) && (sementes[4] == 0) && (sementes[5] == 0))) {
			for (int i = 6; i < 12; i++) {
				total[0] += sementes[i];
				sementes[i] = 0;
			}
			cout << "\nJogador 1 nao tem possibilidades de movimentos\nCapturando as sementes do territorio adversario...\n\n";
			tela(endereco_sementes, endereco_total);
			break;
		}
		//Verifica se for a vez do jogador 2 e ele não possui sementes em seu território (neste caso ele captura todas as sementes do território adversário)
		else if ((jogador == 2) && ((sementes[6] == 0) && (sementes[7] == 0) && (sementes[8] == 0) && (sementes[9] == 0) && (sementes[10] == 0) && (sementes[11] == 0))) {
			for (int i = 0; i < 6; i++) {
				total[1] += sementes[i];
				sementes[i] = 0;
			}
			cout << "\nJogador 2 nao tem possibilidades de movimentos\nCapturando as sementes do territorio adversario...\n\n";
			tela(endereco_sementes, endereco_total);
			break;
		}
		//Pergunta qual movimento o jogador irá fazer
		else {
			tela(endereco_sementes, endereco_total);
			cout << "Escreva a letra da posicao para realizar sua jogada: ";
			cin >> escolha;
			cin.ignore(1000, '\n');
			mover(endereco_sementes, endereco_total, escolha, jogador);
			if (jogador == 1)
				jogador = 2;
			else
				jogador = 1;
		}
	}

	if (total[0] == 24) {
		cout << "\n\nHouve um empate!";
	}
	else if (total[0] > 24){
		cout << "\n\nO jogador 1 ganhou!";
	}
	else {
		cout << "\n\nO jogador 2 ganhou!";
	}
}