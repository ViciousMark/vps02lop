#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#define MAX_LINE_LENGTH 100

typedef struct {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
} Produto;

void ler_dados(const char* filename, Produto produtos[], int* num_produtos) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    *num_produtos = 0;

    // Abrir o arquivo CSV
    file = fopen(filename, "parametros.csv");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Ignorar a primeira linha (cabe�alho)
    fgets(line, MAX_LINE_LENGTH, file);

    // Ler cada linha do arquivo
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        sscanf(line, "%d;%d;%d", &produtos[*num_produtos].numero_de_serie,
               &produtos[*num_produtos].resistencia, &produtos[*num_produtos].durabilidade);
        (*num_produtos)++;
    }

    // Fechar o arquivo
    fclose(file);
}

void calcular_medias(Produto produtos[], int num_produtos, double* media_resistencia, double* media_durabilidade) {
    int soma_resistencia = 0, soma_durabilidade = 0;
    for (int i = 0; i < num_produtos; i++) {
        soma_resistencia += produtos[i].resistencia;
        soma_durabilidade += produtos[i].durabilidade;
    }
    *media_resistencia = (double)soma_resistencia / num_produtos;
    *media_durabilidade = (double)soma_durabilidade / num_produtos;
}

void encontrar_extremos(Produto produtos[], int num_produtos, Produto* min_resistencia, Produto* max_resistencia, Produto* min_durabilidade, Produto* max_durabilidade) {
    *min_resistencia = *max_resistencia = *min_durabilidade = *max_durabilidade = produtos[0];
    for (int i = 1; i < num_produtos; i++) {
        if (produtos[i].resistencia < min_resistencia->resistencia) {
            *min_resistencia = produtos[i];
        }
        if (produtos[i].resistencia > max_resistencia->resistencia) {
            *max_resistencia = produtos[i];
        }
        if (produtos[i].durabilidade < min_durabilidade->durabilidade) {
            *min_durabilidade = produtos[i];
        }
        if (produtos[i].durabilidade > max_durabilidade->durabilidade) {
            *max_durabilidade = produtos[i];
        }
    }
}

void contar_acima_abaixo_medias(Produto produtos[], int num_produtos, double media_resistencia, double media_durabilidade, int* acima_medias, int* abaixo_medias) {
    *acima_medias = *abaixo_medias = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].resistencia > media_resistencia && produtos[i].durabilidade > media_durabilidade) {
            (*acima_medias)++;
        } else {
            (*abaixo_medias)++;
        }
    }
}

int main() {
    Produto produtos[100]; // Assumindo um m�ximo de 100 produtos
    int num_produtos;
    double media_resistencia, media_durabilidade;
    Produto min_resistencia, max_resistencia, min_durabilidade, max_durabilidade;
    int acima_medias, abaixo_medias;

    // Ler os dados do arquivo
    ler_dados("qualidade.csv", produtos, &num_produtos);

    // Calcular as m�dias de resist�ncia e durabilidade
    calcular_medias(produtos, num_produtos, &media_resistencia, &media_durabilidade);

    // Encontrar os produtos com maior e menor resist�ncia e durabilidade
    encontrar_extremos(produtos, num_produtos, &min_resistencia, &max_resistencia, &min_durabilidade, &max_durabilidade);

    // Contar quantos produtos est�o acima e abaixo das m�dias
    contar_acima_abaixo_medias(produtos, num_produtos, media_resistencia, media_durabilidade, &acima_medias, &abaixo_medias);

    // Exibir os resultados
    printf("M�dia de resist�ncia: %.2f\n", media_resistencia);
    printf("M�dia de durabilidade: %.2f\n", media_durabilidade);
    printf("Produto com menor resist�ncia: N�mero de s�rie %d, Resist�ncia %d\n", min_resistencia.numero_de_serie, min_resistencia.resistencia);
    printf("Produto com maior resist�ncia: N�mero de s�rie %d, Resist�ncia %d\n", max_resistencia.numero_de_serie, max_resistencia.resistencia);
    printf("Produto com menor durabilidade: N�mero de s�rie %d, Durabilidade %d\n", min_durabilidade.numero_de_serie, min_durabilidade.durabilidade);
    printf("Produto com maior durabilidade: N�mero de s�rie %d, Durabilidade %d\n", max_durabilidade.numero_de_serie, max_durabilidade.durabilidade);
    printf("N�mero de produtos acima das m�dias: %d\n", acima_medias);
    printf("N�mero de produtos abaixo das m�dias: %d\n", abaixo_medias);

    return 0;
}

