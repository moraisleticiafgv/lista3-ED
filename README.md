# Sistema de Matchmaking

# Descrição do projeto:

Implementação de um sistema de matchmaking em C++ que armazena jogadores em uma fila de espera, os ordena por score e forma grupos de jogadores comn niveis de habilidade semelhantes.
A classe principal Matchmaking utiliza um array estático de capacidade MAX_PLAYERS = 100000 e implementa dois algoritmos de ordenação manualmente:
Insertion Sort e Merge Sort.

# Instruções de Compilação:

O programa pode ser compilado com o comando: `g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking`

# Instruções de Execução:
Para executar, utilize o comando: `./matchmaking`

# Organização dos Arquivos
`main.cpp`         – testes para todas as funcionalidades

`Matchmaking.hpp`  – declaracao da classe Matchmaking

`Matchmaking.cpp` – implementacao da classe Matchmaking (ordenacao, formacao de grupos)

`Player.hpp`      – declaracao da classe Player

`Player.cpp`       – implementacao da classe Player

`README.md`            – este arquivo

# Execução dos testes

Os testes foram implementados no arquivo `main.cpp`.

Para executá-los, basta compilar o projeto e rodar o executável gerado.  
O programa executará automaticamente os testes dos principais métodos da classe `Matchmaking`, incluindo:

- inserção de jogadores;
- remoção de jogadores;
- ordenação com Insertion Sort;
- ordenação com Merge Sort;
- formação de grupos;
- tentativa de formação de grupos sem sucesso;
- listagem de jogadores em espera.

Os resultados dos testes serão exibidos no terminal.
