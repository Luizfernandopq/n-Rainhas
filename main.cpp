#include "tabuleiro.cpp"
#include "formigueiro.cpp"
using namespace std;

int main(int argc, char *argv[]){
/*
    tabuleiroRainha t5;

    t5.init(5);
    //t5.imprimeTabuleiro();

    t5.colocaRainha(3, 2);
    t5.colocaRainha(2, 3);
    t5.colocaRainha(1, 5);
    t5.colocaRainha(5, 1);
    t5.colocaRainha(4, 4);
    t5.imprimeTabuleiro();
    cout << t5.isGameOver() << endl;


/*/
    formigueiro f5;
    f5.init(5);
    //cout << f5.posicionaRainha(0,4) << endl;
    //cout << f5.contradicoesNaPosicao(0,4) << "\n" << endl;
    //f5.imprimeProbabilidade();


    f5.inicializaProbabilidade();
    cout << "\n" << endl;
    f5.imprimeProbabilidade();
    cout << "\n" << endl;
    f5.posicionaRainha(3,3);
    f5.imprimeProbabilidade();
    //*/


    f5.freeMatrizes();
    return 0;
}

/*
for(int i = 0; i<= 3; i++){
    }*/

    //cout << "j = "<< j << "\ti = " << i << "\tmatriz["<< j <<"]["<< j-i << "]" << endl;
                    //cout << "soma = "<<somaDiagonalSudoeste << "\t" << "rainha = " << matriz[j][j-i] << endl;
