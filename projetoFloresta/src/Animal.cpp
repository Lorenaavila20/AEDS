#include "Animal.hpp"
#include <fstream>
#include <iostream>

Animal::Animal(int inicioX, int inicioY, int linhas, int colunas)
    : x(inicioX), y(inicioY), caminho(linhas, std::vector<int>(colunas, 0)){
    caminho[x][y] = 1;
}

int Animal::getX() const { return x; }
int Animal::getY() const { return y; }

void Animal::mover(std::vector<std::vector<int>>& matriz, int iteracao){
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    // Verifica se há fogo ao redor
    bool fogoProximo = false;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && matriz[nx][ny] == 2) {
            fogoProximo = true;
            break;
        }
    }

    // Se está em posição segura e pode ficar parado
    if (matriz[x][y] == 0 && tempoParado < 3 && !fogoProximo) {
        tempoParado++;
        return;
    }

    // Se chegou aqui, precisa tentar se mover
    tempoParado = 0; // Resetar porque vai se mover

    std::queue<std::pair<int, int>> fila;
    std::vector<std::vector<bool>> visitado(linhas, std::vector<bool>(colunas, false));
    std::vector<std::vector<std::pair<int, int>>> anterior(linhas, std::vector<std::pair<int, int>>(colunas, {-1, -1}));

    fila.push({x, y});
    visitado[x][y] = true;

    std::pair<int, int> melhorDestino = {-1, -1};
    int melhorPrioridade = 5;

    while (!fila.empty()) {
        auto [cx, cy] = fila.front(); fila.pop();

        int valor = matriz[cx][cy];
        int prioridadeAtual = (valor == 4) ? 1 : (valor == 0) ? 2 : (valor == 1) ? 3 : (valor == 3) ? 4 : 5;

        if (prioridadeAtual < melhorPrioridade && !(cx == x && cy == y)) {
            melhorDestino = {cx, cy};
            melhorPrioridade = prioridadeAtual;
            if (melhorPrioridade == 1) break; // água encontrada, pare!
        }

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas &&
                !visitado[nx][ny] && matriz[nx][ny] != 2) {
                fila.push({nx, ny});
                visitado[nx][ny] = true;
                anterior[nx][ny] = {cx, cy};
            }
        }
    }

    if (melhorDestino.first == -1) {
        // Nenhum lugar melhor encontrado
        if (bloqueadoEmIteracao == -1)
            bloqueadoEmIteracao = iteracao;
        return;
    }

    // Reconstrói o caminho até o melhor destino
    std::vector<std::pair<int, int>> caminhoReverso;
    std::pair<int, int> atual = melhorDestino;
    while (atual != std::make_pair(x, y)) {
        caminhoReverso.push_back(atual);
        atual = anterior[atual.first][atual.second];
    }

    auto [nx, ny] = caminhoReverso.back(); // próximo passo
    x = nx;
    y = ny;
    caminho[x][y] = 1;
    passos++;

    if (matriz[x][y] == 4) {
        encontrouAgua++;
        matriz[x][y] = 0; // transforma água em local seguro

        for (int i = 0; i < 4; i++) {
            int ux = x + dx[i];
            int uy = y + dy[i];
            if (ux >= 0 && ux < linhas && uy >= 0 && uy < colunas && matriz[ux][uy] != 2)
                matriz[ux][uy] = 1; // umedece ao redor
        }
    }
}


void Animal::segundaChance(std::vector<std::vector<int>>& matriz, int iteracao){
    if (matriz[x][y] == 2)
        mover(matriz, iteracao);
}

void Animal::imprimirCaminhoComMatriz(const std::vector<std::vector<int>>& matriz, const std::string& nomeArquivo) const{
    std::ofstream arquivo(nomeArquivo, std::ios::app);
    if (!arquivo){
        std::cerr << "Erro ao abrir o arquivo de saída: " << nomeArquivo << std::endl;
        return;
    }

    std::cout << "Matriz atual:\n";
    for (size_t  i = 0; i < matriz.size(); i++) {
        for (size_t  j = 0; j < matriz[i].size(); j++){
            std::cout << matriz[i][j] << " ";
            arquivo << matriz[i][j] << " ";
        }
        std::cout << "\t\t";
        arquivo << "\t\t";
        for (size_t  j = 0; j < caminho[i].size(); j++){
            std::cout << caminho[i][j] << " ";
            arquivo << caminho[i][j] << " ";
        }
        std::cout << "\n";
        arquivo << "\n";
    }

    std::cout << "Passos dados: " << passos << "\n";
    std::cout << "Águas encontradas: " << encontrouAgua << "\n";
    if (bloqueadoEmIteracao != -1)
        std::cout << "Animal bloqueado na iteração: " << bloqueadoEmIteracao << "\n";

    arquivo << "Passos dados: " << passos << "\n";
    arquivo << "Águas encontradas: " << encontrouAgua << "\n";
    if (bloqueadoEmIteracao != -1)
        arquivo << "Animal bloqueado na iteração: " << bloqueadoEmIteracao << "\n";

    arquivo << "\n";
}

bool Animal::foiAtingidoPeloFogo(const std::vector<std::vector<int>>& matriz) const {
    return matriz[x][y] == ARVORE_EM_CHAMAS;
}

int Animal::getBloqueioEmIteracao() const {
    return bloqueadoEmIteracao;
}
