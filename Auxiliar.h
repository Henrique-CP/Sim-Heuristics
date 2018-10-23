#pragma once

#include <vector>

struct Var
{
  char tipo;
  int rota;
  int maq;
  int prod;
  double inicio;
  double duracao;
  double fim;
};

struct Maquina
{
  int maq;
  double inicio;
  double duracao;
  double fim;
};


//Funcao que ira gerar o tempo de conserto segundo um normal com media e variancia dadas
double tempo_reparo(double, double);

//Funcao que ira gerar um momento de quebra a partir de um lambda de uma distribuicao exponencial
double quebra_maquina(double);

//Funcao que ira ler um arquivo e preencher um vector de vectors com os dados do problema
void le_solucao(const char*, std::vector<std::vector<Var> >&);

//Funcao que ira ler um arquivo e dizer quais maquinas aquela rota utiliza
void le_rota_maq(const char*, std::vector<std::vector<int> >&);

//Funcao que escreve no vetor maq quais as maq
void escreve_maq(Var vari, std::vector<int>&, std::vector<Maquina>& maq);

//Funcao que ira ordenar um vetor de maquinas na ordem do processamento
void ordena_maq(int i, std::vector<std::vector<Var> >&, std::vector<std::vector<int> >&, std::vector<Maquina>&);

//Funcao que ira propagar a quebra das maquinas para o restante da solucao
void propaga_quebra(double reparo, int pos, std::vector<Maquina>& maq);

//Funcao que simulara a quebra e dira qual a nova FO
void simula(std::vector<Maquina>& maq);
