#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
    int producaoAnual[10][12];
    int primeiroSemestre[10][6];
    int segundoSemestre[10][6];
    double valorPorProduto[10];
    double final[12][14];

    LerArquivoProducaoSemestral("prod-2023-1.txt", primeiroSemestre);
    LerArquivoProducaoSemestral("prod-2023-2.txt", segundoSemestre);

    for (int produtoIndex = 0; produtoIndex < 10; produtoIndex++)
    {
        for (int mes = 0; mes < 12; mes++)
        {
            if (mes < 6)
            {
                producaoAnual[produtoIndex][mes] = primeiroSemestre[produtoIndex][mes];
            }
            else
            {
                producaoAnual[produtoIndex][mes] = segundoSemestre[produtoIndex][mes - 6];
            }
        }
    }

    LerValoresUnitarios(valorPorProduto);
    GerarMatrizFinal(final, producaoAnual, valorPorProduto);
    GerarArquivoDeSaida("2024-2023.txt", final);
    return 0;
}
