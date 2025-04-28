# Processador de CSV com Ordenação em C

Este projeto contém um programa em linguagem C que lê dados de um arquivo CSV, permite ao usuário escolher uma coluna para ordenação e salva os dados ordenados em um novo arquivo CSV.

## Descrição

O programa implementa as seguintes funcionalidades:

*   Leitura de dados de um arquivo CSV especificado pelo usuário.
*   Suporte para arquivos CSV com campos de ID (inteiro), Descrição (string) e Valor (float).
*   Solicitação ao usuário para escolher a coluna de ordenação (ID, Descrição ou Valor).
*   Ordenação dos dados utilizando o algoritmo Quicksort (função `qsort` da biblioteca padrão).
*   Geração de um novo arquivo CSV com os dados ordenados, com nome definido pelo usuário.

## Arquivos no Repositório

*   `main.c`: Código-fonte principal do programa em C.
*   `entrada.csv`: Arquivo CSV de exemplo para teste.
*   `especificacao.md`: Documento detalhando a especificação do projeto, incluindo objetivo, entrada/saída, algoritmo de ordenação, estrutura do código e desafios.
*   `README.md`: Este arquivo.
*   `.gitignore`: Especifica arquivos a serem ignorados pelo Git (como o executável compilado).

## Como Compilar e Executar

1.  **Pré-requisitos:** É necessário ter um compilador C instalado (como o GCC).

2.  **Compilação:** Navegue até o diretório do projeto no terminal e compile o código:
    ```bash
    gcc main.c -o main.exe
    ```
3.  **Execução:** Execute o programa compilado:
    ```bash
    main.exe
    ```
4.  **Interação:** O programa solicitará:
    *   O nome do arquivo CSV de entrada (ex: `entrada.csv`).
    *   O número da coluna para ordenar (0 para ID, 1 para Descrição, 2 para Valor).
    *   O nome do arquivo CSV de saída (ex: `saida_id.csv`).

