#include "funcoes.h"
#include <math.h>
#include <stdio.h>

// Definição da estrutura produto para armazenar informações sobre cada produto
struct produto {
    double valorUnitarioDoProduto;
    double producaoMensalDaFabrica[12];
    double totalItensProduzidosNoAno;
    double valorAnualProduzido;
};

// Função para ler os dados de produção semestral de um arquivo
void LerArquivoProducaoSemestral(char *arquivo, int M[10][6]) {
    FILE *file = fopen(arquivo, "r");

    if (file != NULL) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (fscanf(file, "%d", &M[i][j]) != 1) {
                    printf("Erro ao ler o arquivo %s\n", arquivo);
                    fclose(file);
                    return;
                }
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
    }
}

// Função para ler os valores unitários de cada produto
void LerValoresUnitarios(double V[10]) {
    const char *nomes_produtos[10] = {
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

    printf("Informe os valores unitarios para cada produto:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%s: ", nomes_produtos[i]);
        scanf("%lf", &V[i]);
    }
}

// Função para gerar a matriz final com totais mensais e anuais
void GerarMatrizFinal(double M[12][14], int producao[10][12], double valoresUnitarios[10]) {
    struct produto pd[10];

    // Inicialização da estrutura de produtos
    for (int i = 0; i < 10; i++) {
        pd[i].valorUnitarioDoProduto = valoresUnitarios[i];
        pd[i].totalItensProduzidosNoAno = 0.0;

        // Preenchimento mensal dos produtos
        for (int j = 0; j < 12; j++) {
            pd[i].producaoMensalDaFabrica[j] = producao[i][j];
            pd[i].totalItensProduzidosNoAno += producao[i][j];
        }

        // Cálculo do valor anual produzido por produto
        pd[i].valorAnualProduzido = pd[i].totalItensProduzidosNoAno * pd[i].valorUnitarioDoProduto;
    }

    // Inicialização da matriz final
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 14; j++) {
            M[i][j] = 0.0;
        }
    }

    // Preenchimento da matriz com os valores mensais do produto
    for (int produtoIndex = 0; produtoIndex < 10; produtoIndex++) {
        for (int mes = 0; mes < 12; mes++) {
            M[produtoIndex][mes] = pd[produtoIndex].producaoMensalDaFabrica[mes];
        }
    }

    // Cálculo dos totais anuais
    double producaoAnualTotalEmReais = 0.0;
    double totalDeProdutosProduzidosNoAnoPelaEmpresa = 0.0;

    for (int produtoIndex = 0; produtoIndex < 10; produtoIndex++) {
        M[produtoIndex][12] = pd[produtoIndex].totalItensProduzidosNoAno;
        M[produtoIndex][13] = pd[produtoIndex].valorAnualProduzido;
        producaoAnualTotalEmReais += pd[produtoIndex].valorAnualProduzido;
        totalDeProdutosProduzidosNoAnoPelaEmpresa += pd[produtoIndex].totalItensProduzidosNoAno;
    }

    M[12][13] = producaoAnualTotalEmReais;

    // Cálculo dos totais mensais
    for (int mes = 0; mes < 12; mes++) {
        double totalDeItensProduzidosNoMes = 0.0;
        double valorProduzidoNoMes = 0.0;

        for (int produtoIndex = 0; produtoIndex < 10; produtoIndex++) {
            totalDeItensProduzidosNoMes += pd[produtoIndex].producaoMensalDaFabrica[mes];
            valorProduzidoNoMes += pd[produtoIndex].producaoMensalDaFabrica[mes] * pd[produtoIndex].valorUnitarioDoProduto;
        }

        M[10][mes] = totalDeItensProduzidosNoMes;
        M[11][mes] = valorProduzidoNoMes;
    }

    // Totais anuais e mensais
    M[10][12] = totalDeProdutosProduzidosNoAnoPelaEmpresa;
}

// Função para gerar o arquivo de saída
void GerarArquivoDeSaida(char *nome_arquivo, double M[12][14]) {
    FILE *file = fopen(nome_arquivo, "w");
    const char *nomes_produtos[10] = {
        "Sola inteira",
        "Meia sola",
        "Quarto de sola",
        "Entre sola",
        "Palmilha",
        "Meia palmilha",
        "Salto alto",
        "Salto m�dio",
        "Salto curto",
        "Salto baixo"};
    const char *meses[12] = {
        "Janeiro",
        "Fevereiro",
        "Mar�o",
        "Abril",
        "Maio",
        "Junho",
        "Julho",
        "Agosto",
        "Setembro",
        "Outubro",
        "Novembro",
        "Dezembro"};

    if (file != NULL) {
        // Encontrar produto com maior e menor produção anual
        int indiceMaiorProducao = 0;
        int indiceMenorProducao = 0;

        for (int i = 1; i < 10; ++i) {
            if (M[i][12] > M[indiceMaiorProducao][12]) {
                indiceMaiorProducao = i;
            }

            if (M[i][12] < M[indiceMenorProducao][12]) {
                indiceMenorProducao = i;
            }
        }

        // Produção anual total em unidades por produto
        fprintf(file, "Produ��o anual total em unidades por produto\n");
        for (int i = 0; i < 10; ++i) {
            fprintf(file, "%s: %d %s\n", nomes_produtos[i], (int)M[i][12], (i == indiceMaiorProducao) ? "++" : ((i == indiceMenorProducao) ? "--" : ""));
        }
        double totalProducaoAnualEmUnidades = M[10][12];
        fprintf(file, "Total: %d\n\n", (int)totalProducaoAnualEmUnidades);

        // Produção anual total em reais por produto
        fprintf(file, "\nProdu��o anual total em reais por produto\n");
        for (int i = 0; i < 10; ++i) {
            fprintf(file, "%s: %.2lf %s\n", nomes_produtos[i], M[i][13], (i == indiceMaiorProducao) ? "++" : ((i == indiceMenorProducao) ? "--" : ""));
        }
        double totalProducaoAnualEmReais = M[12][13];
        fprintf(file, "Total: %.2lf\n\n", totalProducaoAnualEmReais);

        // Produção total mensal em unidades de produtos
        fprintf(file, "Produ��o total mensal em unidades de produtos\n");
        for (int j = 0; j < 12; ++j) {
            fprintf(file, "%s: %d\n", meses[j], (int)M[10][j]);
        }
        int totalMensalUnidades = M[10][12];
        fprintf(file, "Total: %d\n\n", totalMensalUnidades);

        // Produção total mensal em reais por produto
        fprintf(file, "Produ��o total mensal em reais por produto\n");
        for (int j = 0; j < 12; ++j) {
            fprintf(file, "%s: %.2lf\n", meses[j], M[11][j]);
        }
        double totalMensalReais = M[12][13];
        fprintf(file, "Total: %.2lf\n", totalMensalReais);

        fclose(file);
    } else {
        printf("Erro ao criar o arquivo de sa�da %s\n", nome_arquivo);
    }
}

// Função para encontrar o maior valor em uma linha da matriz
double MaiorValorDaLinha(double M[12][14], int nlin) {
    double maior = M[nlin][0];
    for (int j = 1; j < 14; ++j) {
        if (M[nlin][j] > maior) {
            maior = M[nlin][j];
        }
    }
    return maior;
}

// Função para encontrar o menor valor em uma linha da matriz
double MenorValorDaLinha(double M[12][14], int nlin) {
    double menor = M[nlin][0];
    for (int j = 1; j < 14; ++j) {
        if (M[nlin][j] < menor) {
            menor = M[nlin][j];
        }
    }
    return menor;
}

// Função para encontrar o maior valor em uma coluna da matriz
double MaiorValorDaColuna(double M[12][14], int ncol) {
    double maior = M[0][ncol];
    for (int i = 1; i < 12; ++i) {
        if (M[i][ncol] > maior) {
            maior = M[i][ncol];
        }
    }
    return maior;
}

// Função para encontrar o menor valor em uma coluna da matriz
double MenorValorDaColuna(double M[12][14], int ncol) {
    double menor = M[0][ncol];
    for (int i = 1; i < 12; ++i) {
        if (M[i][ncol] < menor) {
            menor = M[i][ncol];
        }
    }
    return menor;
}

