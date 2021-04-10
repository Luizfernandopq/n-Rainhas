#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "tabuleiro.cpp"



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
        if(iPlusPlus){
            pontuacao++;
        }
        if(pontuacao == nRainhas){
            return true;
        }
        return false;
    }

    void reiniciaPontuacao(){
        pontuacao = 0;
    }

    bool isMelhor(int pont){
        return pontuacao > pont;
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

    void freeCaminho(){
        free(caminhoX);
        free(caminhoY);
    }

    void copiaFormiga(formiga f1){
        nRainhas = f1.nRainhas;
        pontuacao = f1.pontuacao;
        for (int i = 0; i < pontuacao; i++){
            caminhoX[i] = f1.caminhoX[i];
            caminhoY[i] = f1.caminhoY[i];
        }
        //imprimeCaminho();
    }

    void imprimeTabuleiro(){
        tabuleiroRainha t;
        t.init(nRainhas);
        for(int i = 0; i<pontuacao; i++){
            t.colocaRainha(caminhoX[i], caminhoY[i]);
        }
        t.imprimeTabuleiro();
    }
};
