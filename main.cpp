#include "ambiente.cpp"

using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    /*
    formiga f;
    f.init(5);

    formiga f1 = f;

    f.adicionaCaminho(3, 5, 2);
    f.imprimeCaminho();
    cout << "\n";
    f1.imprimeCaminho();
    f.freeCaminho();

    */
    //srand(time(NULL));
    //rand();

    iterador ambiente1;

    // Argumentos:
    /*
    *   N�mero de Formigas
    *   N�mero de Itera��es
    *   N�mero de Rainhas no tabuleiro
    *   Realizar Resolu��o(caso passe como false o programa n�o tentar� resolver)
    */
    ambiente1.init(25, 100, 25, true);


}

/*
for(int i = 0; i<= 3; i++){
    }*/

    //cout << "j = "<< j << "\ti = " << i << "\tmatriz["<< j <<"]["<< j-i << "]" << endl;
                    //cout << "soma = "<<somaDiagonalSudoeste << "\t" << "rainha = " << matriz[j][j-i] << endl;
