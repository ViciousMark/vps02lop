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
        while (fgets(linha, 100, arq) != NULL)
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

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("+----------+----------+----------+----------+----------+----------+-------+-------+\n");
    printf("| Matrícula | Funcionário | Data      | Origem    | Destino   | Distância | Preço  | Total  |\n");
    printf("+----------+----------+----------+----------+----------+----------+-------+-------+\n");
    for(i=0; i < totalViagens; i++)
    {
        printf("| %8d | %-10s | %-10s | %-10s | %-10s | %8d | %.2f | %.2f |\n", 
               viagens[i].matricula, viagens[i].funcionario, viagens[i].data, 
               viagens[i].origem, viagens[i].destino, viagens[i].distancia, 
               viagens[i].preco, viagens[i].total);
    }
    printf("+----------+----------+----------+----------+----------+----------+-------+-------+\n");
}

void calcularReembolso()
{
    float totalReembolso = 0;
    for(i=0; i < totalViagens; i++)
    {
        viagens[i].total = (viagens[i].preco * viagens[i].distancia) / 3;
        totalReembolso += viagens[i].total;
    }
    printf("\n+---------------------------------------+\n");
    printf("|             Total de Reembolso        |\n");
    printf("+---------------------------------------+\n");
    printf("| R$ %.2f                             |\n", totalReembolso);
    printf("+---------------------------------------+\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    mostrarDados();
    calcularReembolso();
    return 0;
}
