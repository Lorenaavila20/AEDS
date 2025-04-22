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

    if (matriz[x][y] == 0 && tempoParado < 3){
        tempoParado++;
        return;
    }

    tempoParado = 0;

    std::queue<std::pair<int, int>> fila;
    std::vector<std::vector<bool>> visitado(linhas, std::vector<bool>(colunas, false));
    std::vector<std::vector<std::pair<int, int>>> anterior(linhas, std::vector<std::pair<int, int>>(colunas, {-1, -1}));

    fila.push({x, y});
    visitado[x][y] = true;

    std::pair<int, int> destino = {-1, -1};
    int prioridade = 5;

    while (!fila.empty()){
        auto [cx, cy] = fila.front(); fila.pop();

        int valor = matriz[cx][cy];
        int prioridadeAtual = (valor == 4) ? 1 : (valor == 0) ? 2 : (valor == 1) ? 3 : 4;

        if (prioridadeAtual < prioridade){
            prioridade = prioridadeAtual;
            destino = {cx, cy};
            if (prioridade == 1) break;
        }

        for (int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && !visitado[nx][ny]){
                if (matriz[nx][ny] != 2) {
                    fila.push({nx, ny});
                    visitado[nx][ny] = true;
                    anterior[nx][ny] = {cx, cy};
                }
            }
        }
    }

    if (destino.first == -1 || (destino.first == x && destino.second == y)){
        if (bloqueadoEmIteracao == -1)
            bloqueadoEmIteracao = iteracao;
        return;
    }

    std::vector<std::pair<int, int>> caminhoReverso;
    std::pair<int, int> atual = destino;
    while (atual != std::make_pair(x, y)){
        caminhoReverso.push_back(atual);
        atual = anterior[atual.first][atual.second];
    }

    auto [nx, ny] = caminhoReverso.back();
    x = nx;
    y = ny;
    caminho[x][y] = 1;
    passos++;

    if (matriz[x][y] == 4){
        encontrouAgua++;
        matriz[x][y] = 0;
        for (int i = 0; i < 4; i++){
            int ux = x + dx[i];
            int uy = y + dy[i];
            if (ux >= 0 && ux < linhas && uy >= 0 && uy < colunas && matriz[ux][uy] != 2)
                matriz[ux][uy] = 1;
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
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++){
            std::cout << matriz[i][j] << " ";
            arquivo << matriz[i][j] << " ";
        }
        std::cout << "\t\t";
        arquivo << "\t\t";
        for (int j = 0; j < caminho[i].size(); j++){
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
