#ifndef FLORESTA_HPP
#define FLORESTA_HPP

#include <vector>
#include <string>

class Floresta{
    private:
        int linhas, colunas;
        int fogoX, fogoY;
        int animalX, animalY;
        std::vector<std::vector<int>> matriz;

    public:
        Floresta();
        Floresta(const std::string& nomeArquivo);

        int getLinhas() const;
        int getColunas() const;

        int getFogoX() const;
        int getFogoY() const;

        int getAnimalX() const;
        int getAnimalY() const;

        int getValor(int i, int j) const;
        void setValor(int i, int j, int valor);

        const std::vector<std::vector<int>>& getMatriz() const;
        std::vector<std::vector<int>>& getMatriz();

        void propagarFogo();
        void imprimir() const;
        void salvarEmArquivo(const std::string& nomeArquivo) const;
};
#endif 