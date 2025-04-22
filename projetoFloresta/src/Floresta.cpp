#include "floresta.hpp"
#include "config.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

Floresta::Floresta(){
    std::ifstream arquivo(INPUT_FILE);
    if (!arquivo){
        std::cerr << "Erro ao abrir o arquivo " << INPUT_FILE << std::endl;
        exit(1);
    }

    arquivo >> linhas >> colunas >> fogoX >> fogoY;

    matriz.resize(linhas, std::vector<int>(colunas));

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            arquivo >> matriz[i][j];
        }
    }

    arquivo.close();

    std::srand(std::time(nullptr));
    bool encontrado = false;
    
    while (!encontrado){
        int i = std::rand() % linhas;
        int j = std::rand() % colunas;

        if (matriz[i][j] == AREA_VAZIA){ 
            animalX = i;
            animalY = j;
            encontrado = true;
        }
    }
}

int Floresta::getLinhas() const{
    return linhas; 
    }

int Floresta::getColunas() const{
    return colunas;
    }

int Floresta::getFogoX() const{
    return fogoX;
    }

int Floresta::getFogoY() const{
    return fogoY;
    }

int Floresta::getAnimalX() const{
    return animalX;
    }

int Floresta::getAnimalY() const{
    return animalY;
    }

int Floresta::getValor(int i, int j) const{
    return matriz[i][j];
}

void Floresta::setValor(int i, int j, int valor){
    matriz[i][j] = valor;
}

const std::vector<std::vector<int>>& Floresta::getMatriz() const{
    return matriz;
}

void Floresta::propagarFogo(){
    std::vector<std::vector<int>> novaMatriz = matriz;

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (matriz[i][j] == 2) {
                for (char direcao : DIRECOES_VENTO){
                    int ni = i, nj = j;

                    if (direcao == 'C') ni--;
                    else if (direcao == 'B') ni++;
                    else if (direcao == 'E') nj--;
                    else if (direcao == 'D') nj++;

                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas){
                        if (matriz[ni][nj] == 1)
                            novaMatriz[ni][nj] = 2;
                    }
                }
                novaMatriz[i][j] = 3;
            }
        }
    }

    matriz = novaMatriz;

    for (const auto& linha : matriz){
        for (int celula : linha) {
            std::cout << celula << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    salvarEmArquivo(OUTPUT_FILE);
}

void Floresta::imprimir() const{
    for (const auto& linha : matriz){
        for (int celula : linha) {
            std::cout << std::setw(2) << celula << " ";
        }
        std::cout << "\n";
    }
}

void Floresta::salvarEmArquivo(const std::string& nomeArquivo) const{
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo de saída: " << nomeArquivo << std::endl;
        return;
    }

    for (const auto& linha : matriz){
        for (int celula : linha) {
            arquivo << celula << " ";
        }
        arquivo << "\n";
    }

    arquivo.close();
}
