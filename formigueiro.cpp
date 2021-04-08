#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>


using namespace std;

struct formigueiro{
    int nRainhas;
    float **matrizFeromonio;
    float **matrizProbabilidade;

    void init(int intNRainhas){
        nRainhas = intNRainhas;

        matrizFeromonio = (float**)malloc(intNRainhas * sizeof(float*));

        for(int i = 0; i < intNRainhas; i++){
            matrizFeromonio[i] = (float*)malloc(intNRainhas * sizeof(float));
        }

        matrizProbabilidade = (float**)malloc(intNRainhas * sizeof(float*));

        for(int i = 0; i < intNRainhas; i++){
            matrizProbabilidade[i] = (float*)malloc(intNRainhas * sizeof(float));
        }
    }

    void inicializaFeromonio(){
        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                matrizFeromonio[i][j] = 0.2f;
            }
        }
    }

    void inicializaProbabilidade(){

        inicializaFeromonio();
        srand(time(NULL));
        float alfa, beta = 0;
        alfa = (float(rand()%2000000) / 1000000);
        beta = (float(rand()%1000000) / 1000000);
        cout << alfa << "\n" << beta << "\n" << endl;

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j < nRainhas; j++){
                matrizProbabilidade[i][j] =  pow(matrizFeromonio[i][j],alfa) *
                                            pow(pow(nRainhas,2) - contradicoesNaPosicao(i, j), beta);
                //cout << "MP: "<< i << j << ": " << matrizProbabilidade[i][j] << "\n";

            }
        }
        //imprimeProbabilidade();
        atualizaMatrizProbabilidade();

    }

    int contradicoesNaPosicao(int x, int y){
        formigueiro f;
        f.init(nRainhas);
        int contradicGerada = f.posicionaRainha(x, y);
        f.freeMatrizes();
        return contradicGerada;

    }

    void freeMatrizes(){
        free(matrizProbabilidade);
        free(matrizFeromonio);
    }

    void atualizaMatrizProbabilidade(){

        float somaTotal = somaProbabilidade();
        //cout<< somaTotal<< "\n"<<endl;
        float contador = 0;
        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                if(matrizProbabilidade[i][j] != -1){
                    contador += matrizProbabilidade[i][j]/somaTotal;
                    matrizProbabilidade[i][j] = contador;

                    //cout << contador << endl;
                }
            }
        }
    }

    void imprimeFeromonio(){

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                cout << matrizFeromonio[i][j] << "   ";
            }
            cout << "\n" <<endl;
        }

    }

    void imprimeProbabilidade(){

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                //cout << matrizProbabilidade[nRainhas - (i+1)][j] << "   ";
                cout << matrizProbabilidade[i][j] << "  ";
            }
            cout << "\n" <<endl;
        }

    }


    float somaProbabilidade(){
        float somaProbabilidade = 0;
        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                if(matrizProbabilidade[i][j] != -1){
                    somaProbabilidade += matrizProbabilidade[i][j];
                }
            }
        }
        return somaProbabilidade;
    }

    int posicionaRainha(int x, int y){
        int contradicGerada = 0;

        for (int i  = 0; i < nRainhas; i++){

            //linha
            if(matrizProbabilidade[y][i] != -1){
                matrizProbabilidade[y][i] = -1;
                contradicGerada++;
            }

            //coluna
            if(matrizProbabilidade[i][x] != -1){
                matrizProbabilidade[i][x] = -1;
                contradicGerada++;
            }

            // diagonais
            if(i-(y-x) >= 0 && i-(y-x) < nRainhas && matrizProbabilidade[i][i-(y-x)] != -1){
                matrizProbabilidade[i][i - (y - x)] = -1;
                contradicGerada++;
            }
            if((y+x)-i >= 0 && (y+x)-i < nRainhas && matrizProbabilidade[i][(y+x)-i] != -1){
                matrizProbabilidade[i][(y + x) - i] = -1;
                contradicGerada++;

            }
        }
        atualizaMatrizProbabilidade();
        return contradicGerada;
    }
};
