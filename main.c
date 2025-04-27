#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 100
#define MAX_CAMPO 100

typedef struct {
    int id; 
    char descricao[MAX_CAMPO]; 
    float valor; 
    
} Registro;

int ler_csv(const char *nome_arquivo, Registro **registros, int *num_registros);
void ordenar_registros(Registro *registros, int num_registros, int coluna_ordem);
int comparar_id(const void *a, const void *b);
int comparar_descricao(const void *a, const void *b);
int comparar_valor(const void *a, const void *b);
int escrever_csv(const char *nome_arquivo, Registro *registros, int num_registros);

int main() {
    char nome_arquivo_entrada[MAX_CAMPO];
    char nome_arquivo_saida[MAX_CAMPO];
    Registro *registros = NULL;
    int num_registros = 0;
    int coluna_ordem = 0;
    printf("Digite o nome do arquivo CSV de entrada: ");
    if (!fgets(nome_arquivo_entrada, sizeof(nome_arquivo_entrada), stdin)) {
        fprintf(stderr, "Erro ao ler o nome do arquivo de entrada.\n");
        return 1;
    }
    nome_arquivo_entrada[strcspn(nome_arquivo_entrada, "\n")] = 0; 


    if (!ler_csv(nome_arquivo_entrada, &registros, &num_registros)) {
        fprintf(stderr, "Erro ao ler o arquivo CSV.\n");
        return 1;
    }

    if (num_registros == 0) {
        printf("Arquivo CSV vazio ou inválido.\n");
        free(registros);
        return 1;
    }

    printf("Arquivo CSV lido com sucesso. %d registros encontrados.\n", num_registros);


    printf("Selecione a coluna para ordenar:\n");
    printf("  0 = ID\n");
    printf("  1 = Descricao\n");
    printf("  2 = Valor\n");
    printf("Digite o número da coluna: ");
    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        fprintf(stderr, "Erro ao ler a coluna de ordenação.\n");
        free(registros);
        return 1;
    }
    coluna_ordem = atoi(buffer);

    if (coluna_ordem < 0 || coluna_ordem > 2) { 
        fprintf(stderr, "Coluna inválida selecionada.\n");
        free(registros);
        return 1;
    }

    ordenar_registros(registros, num_registros, coluna_ordem);
    printf("Registros ordenados pela coluna %d.\n", coluna_ordem);
 
    printf("Digite o nome do arquivo CSV de saída: ");
    if (!fgets(nome_arquivo_saida, sizeof(nome_arquivo_saida), stdin)) {
        fprintf(stderr, "Erro ao ler o nome do arquivo de saída.\n");
        free(registros);
        return 1;
    }
    nome_arquivo_saida[strcspn(nome_arquivo_saida, "\n")] = 0; 

    if (!escrever_csv(nome_arquivo_saida, registros, num_registros)) {
        fprintf(stderr, "Erro ao escrever o arquivo CSV de saída.\n");
        free(registros);
        return 1;
    }

    printf("Arquivo CSV de saída '%s' gerado com sucesso.\n", nome_arquivo_saida);

    free(registros);

    return 0;
}

int ler_csv(const char *nome_arquivo, Registro **registros, int *num_registros) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo de entrada");
        return 0;
    }

    char linha[MAX_LINHA];
    int capacidade = 10;
    *registros = (Registro *)malloc(capacidade * sizeof(Registro));
    if (!*registros) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(arquivo);
        return 0;
    }
    *num_registros = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (*num_registros >= capacidade) {
            capacidade *= 2;
            Registro *temp = (Registro *)realloc(*registros, capacidade * sizeof(Registro));
            if (!temp) {
                fprintf(stderr, "Erro de realocação de memória.\n");
                free(*registros);
                fclose(arquivo);
                return 0;
            }
            *registros = temp;
        }

        if (sscanf(linha, "%d,%[^,],%f",
                   &((*registros)[*num_registros].id),
                   (*registros)[*num_registros].descricao,
                   &((*registros)[*num_registros].valor)) == 3) {
            (*num_registros)++;
        } else {
             fprintf(stderr, "Aviso: Linha ignorada devido a formato inválido: %s", linha);
        }
    }

    fclose(arquivo);
    return 1;
}

void ordenar_registros(Registro *registros, int num_registros, int coluna_ordem) {
    switch (coluna_ordem) {
        case 0:
            qsort(registros, num_registros, sizeof(Registro), comparar_id);
            break;
        case 1:
            qsort(registros, num_registros, sizeof(Registro), comparar_descricao);
            break;
        case 2:
            qsort(registros, num_registros, sizeof(Registro), comparar_valor);
            break;
        default:
            fprintf(stderr, "Coluna de ordenação inválida.\n");
            break;
    }
}

int comparar_id(const void *a, const void *b) {
    Registro *regA = (Registro *)a;
    Registro *regB = (Registro *)b;
    return (regA->id - regB->id);
}

int comparar_descricao(const void *a, const void *b) {
    Registro *regA = (Registro *)a;
    Registro *regB = (Registro *)b;
    return strcmp(regA->descricao, regB->descricao);
}

int comparar_valor(const void *a, const void *b) {
    Registro *regA = (Registro *)a;
    Registro *regB = (Registro *)b;
    if (regA->valor < regB->valor) return -1;
    if (regA->valor > regB->valor) return 1;
    return 0;
}

int escrever_csv(const char *nome_arquivo, Registro *registros, int num_registros) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir arquivo de saída");
        return 0;
    }

    fprintf(arquivo, "ID,Descricao,Valor\n");

    for (int i = 0; i < num_registros; i++) {
        fprintf(arquivo, "%d,%s,%.2f\n",
                registros[i].id,
                registros[i].descricao,
                registros[i].valor);
    }

    fclose(arquivo);
    return 1;
}

