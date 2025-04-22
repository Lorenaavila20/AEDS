# _Fuga do incêndio_

![ChatGPT Image 21 de abr  de 2025, 21_43_18](https://github.com/user-attachments/assets/ad252690-9524-48e0-abf6-cce34a0aa73b)

## 🎯 Objetivo

<p> O objetivo deste trabalho é desenvolver uma simulação de propagação de incêndio em uma floresta, considerando a movimentação de um animal tentando escapar do fogo. A simulação deve levar em conta diversos fatores, como a propagação do fogo, a segurança do animal, a presença de água e obstáculos, além de implementar a dinâmica da propagação do incêndio influenciada por condições como o vento. O trabalho visa criar uma solução eficiente para prever o comportamento do fogo ao longo do tempo, fornecendo uma visualização clara do impacto do fogo nas áreas da floresta, enquanto simula as tentativas de fuga do animal para áreas seguras.<p/>


## 🚀 Funcionalidades

- Leitura da floresta a partir de um arquivo `input.dat`
- Propagação do fogo com influência de vento configurável (`config.hpp`)
- Movimentação inteligente do animal usando BFS
- Registro do caminho do animal em uma matriz separada
- Impressão e salvamento do estado da floresta a cada iteração
- Monitoramento de estatísticas:
  - Número de passos do animal
  - Quantidade de vezes em que encontrou água
  - Iteração em que foi bloqueado, se ocorrer




## 📁 Estrutura do Projeto

```bash
.
├── src/                  # Códigos-fonte (classes e funções)
│   ├── floresta.cpp
│   ├── animal.cpp
│   ├── simulacao.cpp
│   └── main.cpp
├── include/              # Arquivos de cabeçalho
│   ├── floresta.hpp
│   ├── animal.hpp
│   ├── simulacao.hpp
│   └── config.hpp
├── input.dat             # Arquivo de entrada com a floresta e posição inicial do fogo
├── output.dat            # Arquivo de saída com os estados da simulação
├── Makefile              # Script de compilação
└── README.md             # Este arquivo
```

## 🚀 Como Executar

1. Compile e execute usando o Makefile:

```bash
make clean
make
make run
```

