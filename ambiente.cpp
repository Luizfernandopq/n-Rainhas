#include "formigueiro.cpp"

using namespace std;

struct iterador{
    float **matrizFeromonio;
    float **matrizProbabilidade;
    formiga melhorFormiga;

    void init(int nFormigas,int iteracoes,int nRainhas, bool resolve){
            matrizFeromonio = (float**)malloc(nRainhas * sizeof(float*));

            for(int i = 0; i < nRainhas; i++){
                matrizFeromonio[i] = (float*)malloc(nRainhas * sizeof(float));
            }
            matrizProbabilidade = (float**)malloc(nRainhas * sizeof(float*));

            for(int i = 0; i < nRainhas; i++){
                matrizProbabilidade[i] = (float*)malloc(nRainhas * sizeof(float));
            }

            if(resolve){
                inicializaFeromonio(nRainhas);
                inicializaProbabilidade(nRainhas);
                for(int i = 0; i < iteracoes; i++){
                    melhorFormiga = iteracao(nFormigas, nRainhas);
                    if(melhorFormiga.atualizaPontuacao(false)){
                        cout << "na iteração nº " << i+1 << endl;
                        break;
                    }
                }
            //imprimeProbabilidade(nRainhas);

            }
    }

    formiga iteracao(int nFormigas, int nRainhas){

        formiga melhorFormigaLocal;
        formiga f0;
        float roleta;
        int xy,x,y;
        srand(time(NULL));
        rand();
        for(int i = 0; i < nFormigas; i++){
            for(int j = 0; j < nRainhas; j++){
                roleta = (float(rand()%10001) / 10000);
                imprimeProbabilidade(nRainhas);
                xy = pesquisaPosXY(roleta, nRainhas);
                cout<< "\n xy: "<< xy << "\n";
                x = xy % nRainhas;
                y = xy / nRainhas;
                cout << "roleta2: " << x << " " << y << endl;

                //f0.adicionaCaminho(x, y, j);
                posicionaRainha(x, y, nRainhas);
                if(f0.atualizaPontuacao(true)){
                    //cout << "\nA formiga nº " << i+1 << " obteve sucesso \n";
                    f0.imprimeCaminho();
                    imprimeProbabilidade(nRainhas);
                    return f0;
                }
                if(!atualizaMatrizProbabilidade(nRainhas)){
                    break;
                }
            }

        }
    }

    void inicializaFeromonio(int nRainhas){
        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                matrizFeromonio[i][j] = 0.2f;
            }
        }
    }
    void inicializaProbabilidade(int nRainhas){

        inicializaFeromonio(nRainhas);
        srand(time(NULL));
        rand();
        float alfa, beta = 0;
        alfa = (float(rand()%20001) / 10000);
        beta = (float(rand()%10001) / 10000);
        //cout << alfa << "\n" << beta << "\n" << endl;

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j < nRainhas; j++){
                matrizProbabilidade[i][j] = pow(matrizFeromonio[i][j],alfa) *
                                            pow(pow(nRainhas,2) - contradicoesNaPosicao(i, j, nRainhas), beta);
            }
        }
        atualizaMatrizProbabilidade(nRainhas);
    }

    bool atualizaMatrizProbabilidade(int nRainhas){
        float somaTotal = somaProbabilidade(nRainhas);
        if(somaTotal == 0){
            return false;
        }
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
        return true;
    }



    void atualizaMatrizFeromonio(){
    }

    float somaProbabilidade(int nRainhas){
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

    int posicionaRainha(int x, int y, int nRainhas){
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
        //atualizaMatrizProbabilidade();
        return contradicGerada;
    }


    int pesquisaPosXY(float roleta, int nRainhas){
        bool ignore = false;
        for(int i = 0; i < nRainhas; i++){
            for(int j = 0; j < nRainhas; j++){
                cout << "roleta: " << roleta << "   " << matrizProbabilidade[i][j] << "    " << i << " " << j << endl;

                if(roleta <= matrizProbabilidade[i][j] && matrizProbabilidade[i][j] != -1){
                    return i * nRainhas + j;
                }
            }
        }
        return nRainhas * nRainhas - 1;
    }


    void imprimeProbabilidade(int nRainhas){

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                //cout << matrizProbabilidade[nRainhas - (i+1)][j] << "   ";
                cout << matrizProbabilidade[i][j] << "  ";
            }
            cout << "\n" <<endl;
        }

    }

    int contradicoesNaPosicao(int x, int y, int nRainhas){
        iterador it0;
        it0.init(1, 1, nRainhas, false);
        int contradicGerada = it0.posicionaRainha(x, y, nRainhas);
        it0.freeMatrizes();
        return contradicGerada;
    }

    void freeMatrizes(){
        free(matrizProbabilidade);
        free(matrizFeromonio);
    }
};
