#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;
float totalGeral = 0.0;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("viagens.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq)!= NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            totalViagens++;
        }
    }
    fclose(arq);
}

void calcularTotalReembolso() {
    for (i = 0; i < totalViagens; i++) {
        viagens[i].total = (viagens[i].preco / 100) * viagens[i].distancia / 3.0;
        totalGeral += viagens[i].total;
    }
}

int compararFuncionarios(const void *a, const void *b) {
    Viagem *va = (Viagem *)a;
    Viagem *vb = (Viagem *)b;
    return strcmp(va->funcionario, vb->funcionario);
}

void mostrarDados()
{
    float totalFuncionario = 0.0;
    char ultimoFuncionario[50];
    int primeiro = 1;

    FILE *saida;
    saida = fopen("RelatorioViagens.md", "w");
    if (saida == NULL)
    {
        printf("Erro ao criar o arquivo de saída\n");
    }
    else
    {
        fprintf(saida, "# Relatório de Viagens ACME\n");
        fprintf(saida, "\n");
        fprintf(saida, "| Matrícula | Funcionário | Data | Origem | Destino | Distância | Preço | Total |\n");
        fprintf(saida, "| --- | --- | --- | --- | --- | --- | --- | --- |\n");

        for(i=0; i < totalViagens; i++)
        {
            if(strcmp(viagens[i].funcionario, ultimoFuncionario)!= 0) {
                if(!primeiro) {
                    fprintf(saida, "\n### Total do funcionário %s: R$ %.2f\n", ultimoFuncionario, totalFuncionario);
                }
                strcpy(ultimoFuncionario, viagens[i].funcionario);
                totalFuncionario = 0.0;
                primeiro = 0;
            }
            totalFuncionario += viagens[i].total;
            fprintf(saida, "| %d | %s | %s | %s | %s | %d | %.2f | %.2f |\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem, viagens[i].destino, viagens[i].distancia, viagens[i].preco, viagens[i].total);
        }
        fprintf(saida, "\n### Total do funcionário %s: R$ %.2f\n", ultimoFuncionario, totalFuncionario);
        fprintf(saida, "\n### Total Geral: R$ %.2f\n", totalGeral);
    }
    fclose(saida);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularTotalReembolso();

    qsort(viagens, totalViagens, sizeof(Viagem), compararFuncionarios);

    mostrarDados();
    return 0;
}
