# Documento de Especificação: Processador de CSV com Ordenação

## 1. Objetivo da Solução

O objetivo principal deste projeto é desenvolver um programa em linguagem C capaz de ler dados de um arquivo CSV (Comma-Separated Values), ordenar esses dados com base em uma coluna especificada pelo usuário e, por fim, gerar um novo arquivo CSV contendo os dados ordenados. Esta ferramenta visa facilitar a manipulação e organização de dados tabulares armazenados em formato CSV.

## 2. Descrição da Entrada e Saída de Dados

### Entrada

*   **Arquivo CSV de Entrada:** O programa espera um arquivo CSV como entrada. O nome deste arquivo é fornecido pelo usuário durante a execução.
    *   **Formato:** Cada linha do arquivo representa um registro.
    *   **Campos:** Cada registro deve conter pelo menos três campos, separados por vírgulas. O exemplo implementado assume a seguinte estrutura:
        1.  `ID` (Inteiro): Um identificador numérico.
        2.  `Descricao` (String): Um texto descritivo.
        3.  `Valor` (Float): Um valor numérico (ponto flutuante).
        *Exemplo de linha:* `2,Maçã,2.30`
    *   **Observação:** O parser atual (`sscanf`) é simples e espera exatamente este formato. Arquivos com cabeçalhos, strings contendo vírgulas ou outros delimitadores podem exigir um parser mais robusto.
*   **Coluna de Ordenação:** O usuário deve fornecer um número inteiro indicando a coluna pela qual deseja ordenar os dados (0 para ID, 1 para Descricao, 2 para Valor, no exemplo implementado).
*   **Nome do Arquivo de Saída:** O usuário deve fornecer o nome desejado para o arquivo CSV que conterá os dados ordenados.

### Saída

*   **Arquivo CSV de Saída:** O programa gera um novo arquivo CSV com o nome especificado pelo usuário.
    *   **Conteúdo:** Este arquivo contém os mesmos registros do arquivo de entrada, mas ordenados de acordo com a coluna selecionada pelo usuário.
    *   **Formato:** O formato de cada linha no arquivo de saída é idêntico ao formato do arquivo de entrada (ex: `ID,Descricao,Valor`).
*   **Mensagens no Console:** O programa exibe mensagens informativas no console, indicando o progresso (leitura do arquivo, número de registros, início da ordenação, nome do arquivo de saída) e eventuais erros (falha ao abrir arquivos, coluna inválida, problemas de alocação de memória, linhas com formato inválido).

## 3. Algoritmo de Ordenação Utilizado

Para a ordenação dos dados, foi utilizada a função `bubblesort` implementada manualmente em C. O Bubble Sort é um algoritmo simples de ordenação.

*   **Funcionamento:** A função `bubblesort` requer:
    1.  Um ponteiro para o início do array de dados a ser ordenado (no caso, nosso vetor de `Registro`).
    2.  O número de elementos no array (`num_registros`).
    3.  Um ponteiro para a função de comparação que determina a ordem entre dois elementos.
*   **Funções de Comparação:** Foram implementadas três funções de comparação distintas, uma para cada coluna do exemplo (`ID`, `Descricao`, `Valor`):
    *   `comparar_id`: Compara dois registros com base no campo `id` (ordem numérica crescente).
    *   `comparar_descricao`: Compara dois registros com base no campo `descricao` (ordem alfabética usando `strcmp`).
    *   `comparar_valor`: Compara dois registros com base no campo `valor` (ordem numérica crescente).
*   **Seleção:** A função `ordenar_registros` utiliza uma estrutura `switch` para selecionar a função de comparação apropriada com base na coluna escolhida pelo usuário antes de chamar `bubblesort`.

## 4. Estrutura do Código e Principais Funções Implementadas

O código foi estruturado em um único arquivo (`main.c`) para simplicidade, mas utiliza funções modulares para separar as responsabilidades.

*   **`struct Registro`:** Define a estrutura de dados para armazenar as informações de uma linha do CSV (ID, Descricao, Valor). Pode ser facilmente modificada para acomodar diferentes estruturas de CSV.
*   **`main()`:**
    *   Função principal que orquestra a execução do programa.
    *   Solicita os nomes dos arquivos de entrada e saída e a coluna de ordenação ao usuário.
    *   Chama as funções `ler_csv`, `ordenar_registros` e `escrever_csv`.
    *   Realiza validações básicas de entrada e trata erros.
    *   Libera a memória alocada para os registros antes de terminar.
*   **`ler_csv()`:**
    *   Responsável por abrir e ler o arquivo CSV de entrada.
    *   Aloca memória dinamicamente para armazenar os registros lidos (usando `malloc` e `realloc` para lidar com um número desconhecido de linhas).
    *   Utiliza `fgets` para ler linha por linha e `sscanf` para extrair os campos de cada linha. **Nota:** `sscanf` tem limitações para CSVs complexos.
    *   Retorna o número de registros lidos e um ponteiro para o array de registros.
    *   Inclui tratamento básico de erros (falha ao abrir arquivo, falha de alocação).
*   **`ordenar_registros()`:**
    *   Recebe o array de registros, o número de registros e a coluna de ordenação.
    *   Chama `bubblesort` com a função de comparação apropriada (selecionada via `switch`).
*   **`comparar_id()`, `comparar_descricao()`, `comparar_valor()`:**
    *   Funções auxiliares de comparação usadas por `bubblesort` para determinar a ordem relativa de dois registros com base em um campo específico.
*   **`escrever_csv()`:**
    *   Responsável por criar e escrever no arquivo CSV de saída.
    *   Itera sobre o array de registros (agora ordenado) e escreve cada registro no arquivo usando `fprintf` no formato CSV.
    *   Inclui tratamento de erro para falha ao abrir o arquivo de saída.

## 5. Problemas Encontrados e Soluções Adotadas

*   **Parsing de CSV:** A leitura inicial usando `sscanf` é simples, mas frágil. Ela não lida bem com campos que contêm vírgulas, aspas ou dados ausentes. Para um cenário real, seria necessário implementar um parser de CSV mais robusto, que trate esses casos (por exemplo, lendo caractere por caractere ou usando bibliotecas dedicadas, se permitido).
    *   **Solução Adotada (Parcial):** O código atual assume um formato CSV simples e emite um aviso para linhas que não correspondem ao formato esperado por `sscanf`. Para o escopo deste trabalho, esta abordagem foi considerada suficiente.
*   **Alocação Dinâmica de Memória:** O número de registros no CSV não é conhecido a priori. Foi necessário usar alocação dinâmica (`malloc` e `realloc`) para o array de `Registro`.
    *   **Solução Adotada:** Implementou-se uma estratégia de realocação que dobra a capacidade do array quando ele fica cheio. Verificações foram adicionadas para tratar possíveis falhas de alocação.
*   **Dependência de Compilador:** Durante o teste inicial, verificou-se que o compilador C (`gcc`) não estava instalado no ambiente.
    *   **Solução Adotada:** O pacote `build-essential` (que inclui `gcc`, `make` e outras ferramentas) foi instalado.
*   **Tratamento de Tipos na Ordenação:** A ordenação precisa tratar corretamente diferentes tipos de dados (inteiros, strings, floats).
    *   **Solução Adotada:** Foram criadas funções de comparação específicas para cada tipo de dado, garantindo que a lógica de comparação seja apropriada (subtração para números, `strcmp` para strings).

