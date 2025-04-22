#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include "floresta.hpp"
#include "animal.hpp"
#include "config.hpp"

class Simulacao{
private:
    Floresta floresta;
    Animal animal;

public:
    Simulacao(std::string arquivoEntrada) : floresta(arquivoEntrada),
        animal(floresta.getInicioAnimalX(), floresta.getInicioAnimalY(), floresta.getLinhas(), floresta.getColunas()) {}

    void rodar(){
        for (int iter = 1; iter <= MAX_ITERACOES; iter++){
            std::cout << "\n=== Iteração " << iter << " ===\n";

            // Movimento do animal
            animal.mover(floresta.getMatriz(), iter);

            // Propagação do fogo
            floresta.propagarFogo();

            // Verifica se o animal foi atingido
            if (floresta.getMatriz()[animal.getX()][animal.getY()] == 2){
                std::cout << "Animal atingido pelo fogo! Tentando segunda chance...\n";
                animal.segundaChance(floresta.getMatriz(), iter);
            }

            // Imprime matrizes e estatísticas
            animal.imprimirCaminhoComMatriz(floresta.getMatriz(), "output.dat");

            // Encerra se animal estiver bloqueado
            if (animal.getBloqueadoEmIteracao() != -1){
                std::cout << "Animal bloqueado na iteração " << iter << ". Encerrando simulação.\n";
                break;
            }
        }
    }
};

#endif
