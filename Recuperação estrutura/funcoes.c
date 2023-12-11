#include "funcoes.h"
#include <math.h>
#include <stdio.h>

struct pdct
{
    double valorUnitario;
    double producaoPorMes[12];
    double totalAno;
    double valorDoAno;
};

/*--------------------------------------------------------------
Protótipo: LerArquivoProducaoSemestral(char *arquivo, int M[10][6])
Função: Ler os dados de produção semestral de um arquivo.
Entrada: Nome do arquivo e matriz para armazenar os dados.
Saída: Nenhuma
--------------------------------------------------------------*/
void LerArquivoProducaoSemestral(char *arquivo, int M[10][6])
{
    FILE *file = fopen(arquivo, "r");

    if (file != NULL)
    {
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                if (fscanf(file, "%d", &M[i][j]) != 1)
                {
                    printf("Erro ao ler o arquivo %s\n", arquivo);
                    fclose(file);
                    return;
                }
            }
        }
        fclose(file);
    }
    else
    {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
    }
}

/*--------------------------------------------------------------
Protótipo: MaiorValorDaLinha(double M[12][14], int nlin)
Função: Encontrar o maior valor em uma linha da matriz.
Entrada: Matriz de dados e número da linha.
Saída: Maior valor na linha.
--------------------------------------------------------------*/
double MaiorValorDaLinha(double M[12][14], int nlin)
{
    double maior = M[nlin][0];
    for (int j = 1; j < 14; ++j)
    {
        if (M[nlin][j] > maior)
        {
            maior = M[nlin][j];
        }
    }
    return maior;
}

/*--------------------------------------------------------------
Protótipo: MenorValorDaLinha(double M[12][14], int nlin)
Função: Encontrar o menor valor em uma linha da matriz.
Entrada: Matriz de dados e número da linha.
Saída: Menor valor na linha.
--------------------------------------------------------------*/
double MenorValorDaLinha(double M[12][14], int nlin)
{
    double menor = M[nlin][0];
    for (int j = 1; j < 14; ++j)
    {
        if (M[nlin][j] < menor)
        {
            menor = M[nlin][j];
        }
    }
    return menor;
}

/*--------------------------------------------------------------
Protótipo: MaiorValorDaColuna(double M[12][14], int ncol)
Função: Encontrar o maior valor em uma coluna da matriz.
Entrada: Matriz de dados e número da coluna.
Saída: Maior valor na coluna.
--------------------------------------------------------------*/
double MaiorValorDaColuna(double M[12][14], int ncol)
{
    double maior = M[0][ncol];
    for (int i = 1; i < 12; ++i)
    {
        if (M[i][ncol] > maior)
        {
            maior = M[i][ncol];
        }
    }
    return maior;
}

/*--------------------------------------------------------------
Protótipo: MenorValorDaColuna(double M[12][14], int ncol)
Função: Encontrar o menor valor em uma coluna da matriz.
Entrada: Matriz de dados e número da coluna.
Saída: Menor valor na coluna.
--------------------------------------------------------------*/
double MenorValorDaColuna(double M[12][14], int ncol)
{
    double menor = M[0][ncol];
    for (int i = 1; i < 12; ++i)
    {
        if (M[i][ncol] < menor)
        {
            menor = M[i][ncol];
        }
    }
    return menor;
}

/*--------------------------------------------------------------
Protótipo: LerValoresUnitarios(double V[10])
Função: Ler os valores unitários de cada produto.
Entrada: Vetor para armazenar os valores unitários.
Saída: Nenhuma
--------------------------------------------------------------*/
void LerValoresUnitarios(double V[10])
{
    const char *nomes_pdcts[10] = {
        "Sola inteira",
        "Meia sola",
        "Quarto de sola",
        "Entre sola",
        "Palmilha",
        "Meia palmilha",
        "Salto alto",
        "Salto medio",
        "Salto curto",
        "Salto baixo"};

    printf("Informe os valores unitarios para cada pdct:\n");
    for (int i = 0; i < 10; ++i)
    {
        printf("%s: ", nomes_pdcts[i]);
        scanf("%lf", &V[i]);
    }
}

/*--------------------------------------------------------------
Protótipo: GerarMatrizFinal(double M[12][14], int producao[10][6], double valoresUnitarios[10])
Função: Gerar a matriz final com totais mensais e anuais.
Entrada: Matriz de dados de produção, matriz de valores unitários e matriz final.
Saída: Matriz de dados final
--------------------------------------------------------------*/
void GerarMatrizFinal(double M[12][14], int producao[10][12], double valoresUnitarios[10])
{
    struct pdct pd[10];

    for (int i = 0; i < 10; i++)
    {
        pd[i].valorUnitario = valoresUnitarios[i];
        pd[i].totalAno = 0.0;

        for (int j = 0; j < 12; j++)
        {
            pd[i].producaoPorMes[j] = producao[i][j];

            pd[i].totalAno = pd[i].totalAno + (producao[i][j] * 1.0);
        }
        pd[i].valorDoAno = pd[i].totalAno * pd[i].valorUnitario;
    }

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            M[i][j] = 0.0;
        }
    }

    for (int pdctIndex = 0; pdctIndex < 10; pdctIndex++)
    {
        for (int mes = 0; mes < 12; mes++)
        {
            M[pdctIndex][mes] = pd[pdctIndex].producaoPorMes[mes];
        }
    }

    double producaoAnualTotalEmReais = 0.0;
    for (int pdctIndex = 0; pdctIndex < 10; pdctIndex++)
    {
        M[pdctIndex][12] = pd[pdctIndex].totalAno;
        M[pdctIndex][13] = pd[pdctIndex].valorDoAno;
        producaoAnualTotalEmReais = producaoAnualTotalEmReais + pd[pdctIndex].valorDoAno;
    }

    M[12][13] = producaoAnualTotalEmReais;

    double totalDepdctsProduzidosNoAnoPelaEmpresa = 0.0;
    for (int mes = 0; mes < 12; mes++)
    {
        double totalDeItensProduzidosNoMes = 0.0;
        double valorProduzidoNoMes = 0.0;

        for (int pdctIndex = 0; pdctIndex < 10; pdctIndex++)
        {
            totalDeItensProduzidosNoMes = totalDeItensProduzidosNoMes + pd[pdctIndex].producaoPorMes[mes];
            valorProduzidoNoMes = valorProduzidoNoMes + (pd[pdctIndex].producaoPorMes[mes] * pd[pdctIndex].valorUnitario);
        }

        M[10][mes] = totalDeItensProduzidosNoMes;
        totalDepdctsProduzidosNoAnoPelaEmpresa = totalDepdctsProduzidosNoAnoPelaEmpresa + totalDeItensProduzidosNoMes;
        M[11][mes] = valorProduzidoNoMes;
    }

    M[10][12] = totalDepdctsProduzidosNoAnoPelaEmpresa;

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            printf("%lf ", M[i][j]);
        }
        printf("\n");
    }
}

/*--------------------------------------------------------------
Protótipo: GerarArquivoDeSaida(char *nome_arquivo, double M[12][14])
Função: Gerar o arquivo de saída proposto.
Entrada: Nome do arquivo e a matriz de dados.
Saída: TXT final
--------------------------------------------------------------*/
void GerarArquivoDeSaida(char *nome_arquivo, double M[12][14])
{
    FILE *file = fopen(nome_arquivo, "w");
    const char *nomes_pdcts[10] = {
        "Sola inteira",
        "Meia sola",
        "Quarto de sola",
        "Entre sola",
        "Palmilha",
        "Meia palmilha",
        "Salto alto",
        "Salto medio",
        "Salto curto",
        "Salto baixo"};
    const char *meses[12] = {
        "Janeiro",
        "Fevereiro",
        "Marco",
        "Abril",
        "Maio",
        "Junho",
        "Julho",
        "Agosto",
        "Setembro",
        "Outubro",
        "Novembro",
        "Dezembro"};

    if (file != NULL)
    {
        int indexMaior = 0;
        int indexMenor = 0;
        for (int i = 1; i < 10; ++i)
        {
            if (M[i][12] > M[indexMaior][12])
            {
                indexMaior = i;
            }
            if (M[i][12] < M[indexMenor][12])
            {
                indexMenor = i;
            }
        }
        fprintf(file, "----------------------------------------------------\n");
        fprintf(file, "Producao anual total em unidades por produto\n");
        for (int i = 0; i < 10; ++i)
        {
            fprintf(file, "%s: %d %s\n", nomes_pdcts[i], (int)M[i][12], (i == indexMaior) ? "++" : ((i == indexMenor) ? "--" : ""));
        }
        double totalProducaoAnualEmUnidades = 0.0;
        fprintf(file, "Total: %d\n\n", (int)M[10][12]);
        fprintf(file, "----------------------------------------------------\n");
        fprintf(file, "\nProducao anual total em reais por produto\n");
        for (int i = 0; i < 10; ++i)
        {
            fprintf(file, "%s: %.2lf %s\n", nomes_pdcts[i], M[i][13], (i == indexMaior) ? "++" : ((i == indexMenor) ? "--" : ""));
        }
        fprintf(file, "Total: %.2lf\n\n", M[12][13]);
        fprintf(file, "----------------------------------------------------\n");
        fprintf(file, "Producao total mensal em unidades de produto\n");
        for (int j = 0; j < 12; ++j)
        {
            fprintf(file, "%s: %d\n", meses[j], (int)M[10][j]);
        }
        fprintf(file, "Total: %d\n\n", (int)M[10][12]);
        fprintf(file, "----------------------------------------------------\n");
        fprintf(file, "Producao total mensal em reais por produto\n");
        for (int j = 0; j < 12; ++j)
        {
            fprintf(file, "%s: %.2lf\n", meses[j], M[11][j]);
        }
        fprintf(file, "Total: %.2lf\n", M[12][13]);
        fprintf(file, "----------------------------------------------------\n");
        fclose(file);
    }
    else
    {
        printf("Erro ao criar o arquivo de saida %s\n", nome_arquivo);
    }
}
