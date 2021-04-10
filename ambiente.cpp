#include "formigueiro.cpp"

using namespace std;

struct iterador{
    float **matrizFeromonio;
    float **matrizProbabilidade;
    formiga melhorFormiga;
    float valoresSorteados[10000] = {0};
    int sorteados = 0;

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
                for(int i = 0; i < iteracoes; i++){
                    inicializaProbabilidade(nRainhas);
                    melhorFormiga = iteracao(nFormigas, nRainhas);
                    if(melhorFormiga.atualizaPontuacao(false)){
                        cout << "na iteracao " << i+1 << "\nnumero de sorteios: "<< sorteados << endl;
                        break;
                    }
                    atualizaMatrizFeromonio(nRainhas, melhorFormiga);

                }
                melhorFormiga.imprimeTabuleiro();
                //melhorFormiga.imprimeCaminho();
                //imprimeProbabilidade(nRainhas);
                imprimeFeromonio(nRainhas);
                cout << "\nRainhas colocadas: " << melhorFormiga.pontuacao << endl;
            //imprimeProbabilidade(nRainhas);

            }
    }

    formiga iteracao(int nFormigas, int nRainhas){

        formiga melhorFormigaLocal;
        melhorFormigaLocal.init(nRainhas);
        formiga f0;
        f0.init(nRainhas);
        float roleta;
        int xy,x,y;
        for(int i = 0; i < nFormigas; i++){
            for(int j = 0; j < nRainhas; j++){
                roleta = randomico(1);
                //imprimeProbabilidade(nRainhas);
                xy = pesquisaPosXY(roleta, nRainhas);
                //cout<< "\n xy: "<< xy << "\n";
                x = xy % nRainhas;
                y = xy / nRainhas;
                //cout << "posição sorteada: " << x << " " << y << "  " << roleta << endl;

                if(!posicionaRainha(x, y, nRainhas)){
                    continue;
                }
                f0.adicionaCaminho(x, y, j);
                if(f0.atualizaPontuacao(true)){
                    cout << "\nA formiga " << i+1 << " obteve sucesso ";
                    //f0.imprimeCaminho();
                    //imprimeProbabilidade(nRainhas);
                    return f0;
                }
                if(!atualizaMatrizProbabilidade(nRainhas)){
                    break;
                }
            }
            if(f0.isMelhor(melhorFormigaLocal.pontuacao)){
                melhorFormigaLocal.copiaFormiga(f0);
                //cout<< "deu bom \n\n";
            }
            f0.reiniciaPontuacao();
            inicializaProbabilidade(nRainhas);
        }
        return melhorFormigaLocal;
    }

    void inicializaFeromonio(int nRainhas){
        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                matrizFeromonio[i][j] = 5.0f + nRainhas;
            }
        }
    }
    void inicializaProbabilidade(int nRainhas){

        float alfa, beta = 0;
        alfa = randomico(4);
        beta = randomico(4);
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



    void atualizaMatrizFeromonio(int nRainhas, formiga f){
        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                if(matrizFeromonio[i][j] >= 1.0f){
                    matrizFeromonio[i][j] -= 1.0f;
                }else {
                    matrizFeromonio[i][j] = 0;
                }
            }
            if(i < f.pontuacao){
                matrizFeromonio[f.caminhoY[i]][f.caminhoX[i]] += 2.0f;
            }
        }
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

        if(matrizProbabilidade[y][x] == -1){
            return 0;
        }
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
                //cout << "roleta: " << roleta << "   " << matrizProbabilidade[i][j] << "    " << i << " " << j << endl;

                if(roleta <= matrizProbabilidade[i][j] && matrizProbabilidade[i][j] != -1){
                    //cout<< "simm\n\n";
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

        void imprimeFeromonio(int nRainhas){

        for (int i = 0; i < nRainhas; i++){
            for (int j = 0; j< nRainhas; j++){
                //cout << matrizProbabilidade[nRainhas - (i+1)][j] << "   ";
                cout << matrizFeromonio[i][j] << "  ";
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

    float randomico(int intMax){
        rand();
        if(sorteados >= 10000){
            sorteados = 0;
        }
        float novo = intMax * (float(rand()%100001) / 100000);
        for(int i = 0; i <= sorteados; i++){
            if(novo == valoresSorteados[i]){
                return randomico(intMax);
            }
        }
        valoresSorteados[sorteados++] = novo;
        return novo;
    }

};
