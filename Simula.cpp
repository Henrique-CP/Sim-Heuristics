#include <iostream>
#include <vector>
#include "Auxiliar.h"

int main()
{
  double u = 10, s = 1, lambda = 4.1;
  std::vector<std::vector<Var> > variaveis;
  std::vector<std::vector<int> > rotas;
  std::vector<Maquina> maq;
  maq.reserve(1000);
  //std::cout << "Numero gerado Normal: " << tempo_reparo(u,s) << std::endl;
  //std::cout << "Numero gerado Normal: " << quebra_maquina(lambda) << std::endl;
  //E chamada a funcao le_arquivo para preencher o valor das variaveis resolvidas pela algoritmo hierarquico
  le_solucao("SolHierarquica-Scheduling.txt", variaveis);
  le_rota_maq("MaqRota.txt", rotas);
  ordena_maq(0, variaveis, rotas, maq);

  //E realizada a simulacao para cada periodo
  simula(maq);


  for(int i = 0; i < maq.size(); i++)
  {
     std::cout << "Maquina rota: " << maq[i].maq << std::endl;
     std::cout << "Inicio: " << maq[i].inicio << '\n';
     std::cout << "Fim: " << maq[i].fim << '\n';
  }
}
