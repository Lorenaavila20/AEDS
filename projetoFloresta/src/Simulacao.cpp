#include "Simulacao.hpp"

Simulacao::Simulacao(const std::string& arquivoEntrada)
    : floresta(arquivoEntrada),
      animal(floresta.getAnimalX(), floresta.getAnimalY(),
             floresta.getLinhas(), floresta.getColunas())
{}

void Simulacao::rodar(){
    for (int iter = 1; iter <= MAX_INTERACOES; ++iter){
        std::cout << "\n=== Iteração " << iter << " ===\n";

        auto& matriz = floresta.getMatriz();  

        // 1) Animal se move
        animal.mover(matriz, iter);

        // 2) Fogo se propaga
        floresta.propagarFogo();

        // 3) Se o animal for atingido pelo fogo, tenta segunda chance
        if (animal.foiAtingidoPeloFogo(matriz)) {
            std::cout << "Animal atingido pelo fogo! Tentando segunda chance...\n";
            animal.segundaChance(matriz, iter);

            // Verifica se morreu mesmo após a segunda chance
            if (animal.foiAtingidoPeloFogo(matriz)) {
                std::cout << "Animal morreu após a segunda chance. Simulação encerrada.\n";
                return;
            }
        }

        // 4) Imprime estado atual e salva no arquivo
        animal.imprimirCaminhoComMatriz(matriz, OUTPUT_FILE);

        // 5) Verifica bloqueio do animal
        if (animal.getBloqueioEmIteracao() != -1) {
            std::cout << "Animal bloqueado na iteração " 
                      << animal.getBloqueioEmIteracao() 
                      << ". Encerrando simulação.\n";
            return;
        }
    }

    // Se chegou ao fim sem morrer ou ser bloqueado
    std::cout << "Animal sobreviveu após " << MAX_INTERACOES << " iterações!\n";
}
