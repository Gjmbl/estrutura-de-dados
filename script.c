#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 50

int main() {
    FILE *inputFile;
    FILE *outputFile;

    inputFile = fopen("DadosEntrada.csv", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(1);
    }

    outputFile = fopen("SituacaoFinal.csv", "w");
    if (outputFile == NULL) {
        printf("Erro ao criar o arquivo de saída!\n");
        fclose(inputFile);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), inputFile);

    fprintf(outputFile, "Nome,Nota Média,Situação\n");

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char nome[MAX_NAME_LENGTH];
        float nota1, nota2;

        sscanf(line, "%[^,],%*[^,],%*[^,],%f,%f", nome, &nota1, &nota2);

        float media = (nota1 + nota2) / 2.0;

        const char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO";

        fprintf(outputFile, "%s,%.2f,%s\n", nome, media, situacao);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Arquivo SituacaoFinal.csv gerado com sucesso!\n");

    return 0;
}
