#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int machine_count[5] = {0}; // Supondo que as m�quinas s�o numeradas de 1 a 4

    // Abrir o arquivo CSV
    file = fopen("producao.csv", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ignorar a primeira linha (cabe�alho)
    fgets(line, MAX_LINE_LENGTH, file);

    // Ler cada linha do arquivo
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        int machine_number;
        char date[20], time[20];

        // Ler a data, hora e n�mero da m�quina
        sscanf(line, "%[^;];%[^;];%d", date, time, &machine_number);

        // Contar o n�mero de explosivos produzidos por cada m�quina
        if (machine_number >= 1 && machine_number <= 4) {
            machine_count[machine_number]++;
        }
    }

    // Fechar o arquivo
    fclose(file);

    // Exibir a contagem de explosivos por m�quina
    for (int i = 1; i <= 4; i++) {
        printf("M�quina %d: %d explosivos produzidos\n", i, machine_count[i]);
    }

    return 0;
}

