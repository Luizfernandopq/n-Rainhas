#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>


using namespace std;

struct formiga{
    int nRainhas;
    int *caminhoX;
    int *caminhoY;
    int pontuacao = 0;

    void init(int intNRainhas){
        nRainhas = intNRainhas;
        caminhoX = (int*)malloc(intNRainhas * sizeof(int));
        caminhoY = (int*)malloc(intNRainhas * sizeof(int));
    }

    bool atualizaPontuacao(bool iPlusPlus){
        if(iPlusPlus)
            pontuacao++;
        if(pontuacao == nRainhas)
            return true;
        return false;
    }

    void adicionaCaminho(int x, int y,int  posicao){
        caminhoX[posicao] = x;
        caminhoY[posicao] = y;
    }

    void imprimeCaminho(){
        for (int i = 0; i < nRainhas; i++){
            cout << caminhoX[i] << "    " << caminhoY[i] << endl;
        }
    }

};
