#ifndef CONFIG_H
#define CONFIG_H

const int MAX_INTERACOES = 5;

const bool VENTO_ATIVO = true;

const int AREA_VAZIA = 0;
const int ARVORE_SAUDAVEL = 1;
const int ARVORE_EM_CHAMAS = 2;
const int ARVORE_QUEIMADA = 3;
const int AGUA = 4;

const int TEMPO_MAX_ESPERA = 3;

const std::string INPUT_FILE = "input.dat";
const std::string OUTPUT_FILE = "output.dat";

const char DIRECOES_VENTO[] = {'B', 'E'};

#endif