#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include "Floresta.hpp"
#include "Animal.hpp"
#include "Config.hpp"
#include <iostream>

class Simulacao{
private:
    Floresta floresta;
    Animal animal;

public:
    Simulacao()
        : floresta(),
          animal(floresta.getAnimalX(), floresta.getAnimalY(), floresta.getLinhas(), floresta.getColunas())
    {}

    Simulacao(const std::string& arquivoEntrada);

    void rodar();
};

#endif 
