#ifndef FUNCOES_H
#define FUNCOES_H

void LerArquivoProducaoSemestral(char *arquivo, int M[10][6]);
void LerValoresUnitarios(double V[10]);
void GerarMatrizFinal(double M[12][14], int producao[10][12], double valoresUnitarios[10]);
void GerarArquivoDeSaida(char *nome_arquivo, double M[12][14]);
double MaiorValorDaLinha(double M[12][14], int nlin);
double MenorValorDaLinha(double M[12][14], int nlin);
double MaiorValorDaColuna(double M[12][14], int ncol);
double MenorValorDaColuna(double M[12][14], int ncol);

#endif