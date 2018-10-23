#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <string.h>
#include <algorithm>
#include "Auxiliar.h"

bool compara (const Var& v1, const Var& v2)
{
  return (v1.inicio < v2.inicio);
}

double tempo_reparo(double u, double s)
{
  double tempo;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution(u,s);
  tempo = distribution(generator);
  if (tempo < 0)
  tempo = -tempo;
  return tempo;
}

double quebra_maquina(double lambda)
{
  double quebra;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::poisson_distribution<int> distribution(lambda);
  quebra = distribution(generator);
  return quebra;
}

void le_solucao(const char* arq, std::vector<std::vector<Var> >& variaveis)
{
  std::ifstream myfile;
  myfile.open(arq);
  std::string lixo;
  double periodo, duracao, tarefas;
  char car;
  int cont = 0;

  if (!myfile)
  {
      std::cout << "Erro na abertura do arquivo" << std::endl;
      exit(0);
  }

  //Le-se o cabecalho do arquivo aparentemente sem informacao
  for (int i = 0; i < 3; i++)
  {
    getline(myfile, lixo);
  }
  variaveis.resize(4);
  //Le-se o arquivo para todos os periodos
  while (!myfile.eof())
  {
    //Salvando a duracao e o periodo
    for (int i = 0; i < 4; i++)
    {
      myfile >> lixo;
    }
    myfile >> periodo;
    // std::cout << periodo << std::endl;
    myfile >> lixo;
    myfile >> lixo;
    myfile >> duracao;
    //std::cout << duracao << std::endl;

    //Lendo duracao do periodo, inicialmente sera jogado fora
    getline(myfile, lixo);
    getline(myfile, lixo);
    getline(myfile, lixo);

    //Obtendo o total de tarefas
    for (int i = 0; i < 3; i++)
    {
      myfile >> lixo;
    }
    myfile >> tarefas;
    // std::cout << tarefas << std::endl;
    variaveis[cont].resize(tarefas);
    getline(myfile, lixo);
    getline(myfile, lixo);

    for(int i = 0; i < tarefas; i++)
    {
      //Lendo as tarefas, com a descricao, inicio, fim e duracao
      myfile >> lixo;
      myfile >> lixo;
      myfile >> lixo;
      //Lendo a variavel
      myfile.get(car);
      myfile.get(car);

      if (car == 'X')
      {
        variaveis[cont][i].tipo = car;
        myfile.get(car);
        myfile.get(car);
        lixo = "";
        while(car != '_')
        {
          lixo += car;
          myfile.get(car);
        }
        std::string::size_type sz;
        variaveis[cont][i].rota = std::stoi (lixo, &sz);
        // std::cout << "Variavel: " << variaveis[cont][i].rota << std::endl;
        myfile.get(car);
        lixo = "";
        while(car != '_')
        {
          lixo += car;
          myfile.get(car);
        }
        variaveis[cont][i].maq = std::stoi (lixo, &sz);
        // std::cout << "Maquinas: " << variaveis[cont][i].maq << std::endl;
        myfile.get(car);
        myfile.get(car);
        myfile.get(car);

        myfile >> lixo;
        myfile >> lixo;
        myfile >> variaveis[cont][i].inicio;
        // std::cout << variaveis[cont][i].inicio << std::endl;

        myfile >> lixo;
        myfile >> lixo;
        myfile >> variaveis[cont][i].fim;
        // std::cout << variaveis[cont][i].fim << std::endl;

        myfile >> lixo;
        myfile >> lixo;
        myfile >> variaveis[cont][i].duracao;
        // std::cout << variaveis[cont][i].duracao << std::endl;
      }
      if (car == 'Y' || car == 'Z')
      {
        variaveis[cont][i].tipo = car;
        // std::cout << variaveis[cont][i].tipo << std::endl;
        myfile.get(car);
        myfile.get(car);
        lixo = "";

        while(car != '_')
        {
          lixo += car;
          myfile.get(car);
        }
        std::string::size_type sz;
        variaveis[cont][i].rota = std::stoi(lixo, &sz);
        // std::cout << "Variaveis: " << variaveis[cont][i].rota << std::endl;

        myfile.get(car);
        lixo = "";
        while(car != '_')
        {
          lixo += car;
          myfile.get(car);
        }
        variaveis[cont][i].maq = std::stoi(lixo, &sz);
        // std::cout << "Maqu: " << variaveis[cont][i].maq << std::endl;
        myfile.get(car);
        lixo = "";
        while(car != '_')
        {
          lixo += car;
          myfile.get(car);
        }
        variaveis[cont][i].prod = std::stoi(lixo, &sz);
        // std::cout << "Produto: " << variaveis[cont][i].prod << std::endl;

        myfile.get(car);
        myfile.get(car);
        myfile.get(car);

        myfile >> lixo;
        myfile >> lixo;
        myfile >> variaveis[cont][i].inicio;
        // std::cout << variaveis[cont][i].inicio << std::endl;

        myfile >> lixo;
        myfile >> lixo;
        myfile >> variaveis[cont][i].fim;
        // std::cout << variaveis[cont][i].fim << std::endl;

        myfile >> lixo;
        myfile >> lixo;
        myfile >> variaveis[cont][i].duracao;
        // std::cout << variaveis[cont][i].duracao << std::endl;
      }
    }

    getline(myfile, lixo);
    getline(myfile, lixo);
    getline(myfile, lixo);
    getline(myfile, lixo);
    cont++;
  }
}

void le_rota_maq(const char* arq, std::vector<std::vector<int> >& rotas)
{
  std::ifstream myfile;
  myfile.open(arq);
  int maq, rota;
  //Tem que verificar como sera possivel saber o numero de rotas existentes. Deve-se adicionar um a mais porque as maquinas sao salvas a partir do 1
  rotas.resize(111);
  for (int i = 0; i < rotas.size(); i++)
  {
    //Tem que verificar como sera possivel saber o numero de maquinas existentes
    rotas[i].reserve(50);
  }

  if (!myfile)
  {
      std::cout << "Erro na abertura do arquivo" << std::endl;
      exit(0);
  }

  while (!myfile.eof())
  {
    myfile >> maq;
    //std::cout << "Maquina: " << maq << '\n';
    myfile >> rota;
    while (rota != -1)
    {
      rotas[rota].push_back(maq);
      //std::cout << "Elemento adicionado: " << rotas[rota].back() <<  '\n';
      //std::cout << "Rota: " << rota << '\n';
      myfile >> rota;
    }
  }
}

void ordena_maq(int i, std::vector<std::vector<Var> >& variaveis, std::vector<std::vector<int> >& rotas, std::vector<Maquina>& maq)
{
  Maquina temp;
  //Ordena as variaveis da solucao atraves do tempo de inicio
  std::sort(variaveis[i].begin(), variaveis[i].end(), compara);

  //Agora e necessario realizar a criacao de um vetor contendo a ordem que as maquinas sao utilizadas
  for (int j = 0; j < variaveis[i].size(); j++)
  {
    // std::cout << "Rota: " << variaveis[i][j].rota << '\n';
    //std::cout << "Tams" << variaveis[i].size() << '\n';
    // std::cout << "Rotas: " << rotas[variaveis[i][j].rota].size() << std::endl;
    //Escreve todas as maquinas que aquela rota contem no vetor maquinas
    for (int k = 0; k < rotas[variaveis[i][j].rota].size(); k++)
    {
      temp.maq = rotas[variaveis[i][j].rota][k];
      temp.inicio = variaveis[i][j].inicio;
      temp.duracao = variaveis[i][j].duracao;
      temp.fim = variaveis[i][j].fim;
      maq.push_back(temp);
    }
  }
}

void propaga_quebra(double reparo, int pos, std::vector<Maquina>& maq)
{
   int j = pos;
   //Caso a maquina tivesse começado antes do fim siginifica que a rota não tinha conflito com a rota da maq que quebrou    
   while (maq[j].inicio <= maq[pos].fim && j < maq.size())
   {
     j++;
   }
   if (j < maq.size())
   {
     while (j < maq.size())
     {
       maq[j].inicio = maq[j].inicio + reparo;
       maq[j].fim = maq[j].inicio + maq[j].duracao;
       j++;
     }
   }
}

void simula(std::vector<Maquina>& maq)
{
  double tempo, reparo;
  for (int i = 0; i < maq.size(); i++)
  {
    tempo = quebra_maquina(10);
    std::cout << "Quebra: " << tempo << std::endl;
    if (tempo >= maq[i].fim)
    {
      std::cout << "Não quebrou" << std::endl;
      continue;
    }
    else
    {
     std::cout << "Quebrou" << std::endl;
     reparo = tempo_reparo(1,0.5);
     std::cout << "Reparo: " << reparo << std::endl;
     propaga_quebra(reparo, i, maq);
    }
   }
}	





