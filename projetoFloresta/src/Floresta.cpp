#include "Floresta.hpp"
#include "Config.hpp"
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

Floresta::Floresta(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo){
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        exit(1);
    }

    arquivo >> linhas >> colunas >> fogoX >> fogoY;

    matriz.resize(linhas, std::vector<int>(colunas));
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
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

std::vector<std::vector<int>>& Floresta::getMatriz() {
    return matriz;
}

void Floresta::propagarFogo() {
    std::vector<std::vector<int>> novaMatriz = matriz;

    if (VENTO_ATIVO) {
        // Usa somente as direções definidas em DIRECOES_VENTO
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (matriz[i][j] == ARVORE_EM_CHAMAS) {
                    for (char direcao : DIRECOES_VENTO) {
                        int ni = i, nj = j;
                        if (direcao == 'C') ni--;
                        else if (direcao == 'B') ni++;
                        else if (direcao == 'E') nj--;
                        else if (direcao == 'D') nj++;

                        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas &&
                            matriz[ni][nj] == ARVORE_SAUDAVEL) {
                            novaMatriz[ni][nj] = ARVORE_EM_CHAMAS;
                        }
                    }
                    // após replicar, marca queimada
                    novaMatriz[i][j] = ARVORE_QUEIMADA;
                }
            }
        }
    } else {
        // Sem vento: propaga igualmente em todas as 4 direções
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (matriz[i][j] == ARVORE_EM_CHAMAS) {
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];
                        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas &&
                            matriz[ni][nj] == ARVORE_SAUDAVEL) {
                            novaMatriz[ni][nj] = ARVORE_EM_CHAMAS;
                        }
                    }
                    novaMatriz[i][j] = ARVORE_QUEIMADA;
                }
            }
        }
    }

    matriz = std::move(novaMatriz);

    // Impressão e salvamento
    for (const auto& linha : matriz) {
        for (int cel : linha) std::cout << std::setw(2) << cel << " ";
        std::cout << '\n';
    }
    std::cout << std::endl;

    salvarEmArquivo(OUTPUT_FILE);
}

void Floresta::imprimir() const{
    for (const auto& linha : matriz){
        for (int celula : linha) std::cout << std::setw(2) << celula << " ";
        std::cout << "\n";
    }
}

void Floresta::salvarEmArquivo(const std::string& nomeArquivo) const{
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo){
        std::cerr << "Erro ao abrir o arquivo de saída: " << nomeArquivo << std::endl;
        return;
    }

    for (const auto& linha : matriz){
        for (int celula : linha) arquivo << celula << " ";
        arquivo << "\n";
    }
    arquivo.close();
}
