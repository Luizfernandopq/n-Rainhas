#include <iostream>
#include <cstdlib>

using namespace std;

struct tabuleiroRainha{
    int nRainhas;
    int **matriz;

    void init(int intNRainhas){
        nRainhas = intNRainhas;

        matriz = (int**)malloc(intNRainhas * sizeof(int*));

        for(int i = 0; i < intNRainhas; i++){
            matriz[i] = (int*)malloc(intNRainhas * sizeof(int));
        }
    }
    void imprimeTabuleiro(){

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                if(matriz[i][j])
                    cout << "w   ";  //nRainhas - (i+1)
                else
                    cout << "-   ";
            }
            cout << "\n" <<endl;
        }

    }

    void colocaRainha(int x, int y){
        matriz[y][x]++;
    }
    void tiraRainha(int x, int y){
        matriz[y][x]--;
    }

    bool isGameOver(){

    // declaração de variáveis locais
        int somaLinha, somaColuna,
         somaDiagonalNordeste, somaDiagonalSudoeste,
         somaDiagonalNoroeste, somaDiagonalSudeste;

    // laço externo
        for (int i = 0; i < nRainhas; i++){

        // inicialização e reinicialização das varáveis locais
            somaLinha = 0;
            somaColuna = 0;
            somaDiagonalNordeste = 0;
            somaDiagonalSudoeste = 0;
            somaDiagonalNoroeste = 0;
            somaDiagonalSudeste = 0;

        // laço interno
            for(int j = 0; j < nRainhas; j++){
            // checagem para saber se os índices ultrapassam as bordas do tabuleiro
                if(j+i < nRainhas){
                    somaDiagonalNordeste += matriz[j][j+i];
                }
                if(i != 0 && j-i >= 0){
                    somaDiagonalSudoeste += matriz[j][j-i];
                }
                if(j+i < nRainhas){
                    somaDiagonalNoroeste += matriz[j][nRainhas - (j+i+1)];
                }
                if(i != 0 && j-(i-1) > 0){
                    somaDiagonalSudeste += matriz[j][nRainhas - (j-(i-1))];
                }
                somaLinha += matriz[i][j];
                somaColuna += matriz[j][i];
                if(somaLinha > 1 || somaColuna > 1 ||
                 somaDiagonalNordeste > 1 || somaDiagonalSudoeste > 1 ||
                 somaDiagonalNoroeste > 1 || somaDiagonalSudeste > 1
                 )
                    return true;
            }
        }
        return false;
    }
};
