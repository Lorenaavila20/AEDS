#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <vector>
#include <queue>
#include <string>
#include "Config.hpp" 

class Animal {
private:
    int x, y;
    int passos = 0;
    int encontrouAgua = 0;
    int bloqueadoEmIteracao = -1;
    int tempoParado = 0;
    std::vector<std::vector<int>> caminho;

public:
    Animal(int inicioX, int inicioY, int linhas, int colunas);
    
    void mover(std::vector<std::vector<int>>& matriz, int iteracao);
    void imprimirCaminhoComMatriz(const std::vector<std::vector<int>>& matriz, const std::string& nomeArquivo) const;
    void segundaChance(std::vector<std::vector<int>>& matriz, int iteracao);

    int getX() const;
    int getY() const;

    bool foiAtingidoPeloFogo(const std::vector<std::vector<int>>& matriz) const;
    int getBloqueioEmIteracao() const;
};

#endif

