#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <iostream>
#include <fstream>
#include <ilcplex/ilocplex.h>

//#define DEBUG

using namespace std;

namespace Toolkit{
    /*
    * Extrai os coeficientes e outros dados do arquivo.
    * O arquivo é padronizado da seguinte forma:
    * linha     texto                   Descrição
    *   1       n m                     n,m são respectivamente linhas e colunas
    *   2       x11 x12 x13 ... x1m     Matrix[n, m] de custo da função objetivo.
    *   3       x21 x22 x23 ... x2m
    *   4       x31 x32 x33 ... x3m
    *   .       ...................
    *   n+1     xn1 xn2 xn3 ... xnm
    *           D1 D2 D3 ... DM         Demanda
    *           O1 O2 O3 ... ON         Oferta
    */
    class Problem{
    public:
        Problem(string file_name, IloEnv& env, IloCplex& cplex) : file(file_name),
            file_name(file_name),
            output_name("padrao.txt"),
            env(env), 
            cplex(cplex),
            model(env), 
            custo(env),
            objective(env),
            demanda(env),
            oferta(env),
            erro(!file.is_open()) {}

        ~Problem(){
          file.close();
          for(int i = 0; i < custo.getSize(); i++){
            delete custo[i];
          }
        }

        void readFile(bool dual);
        bool balancear();//Só balancea se necessario
        void run();
        //getters
        IloObjective& getObjective();
        IloModel& getModel();
        //setters
        void setOutputFileName(string file_name);

        //others
        bool hasError();
        bool isBalanced();
    private:
        void dual();
        string file_name, output_name;
        bool erro = false;
        int n = 0, m = 0; //n e m; linha e colunas
        IloNum deman = 0,ofer = 0;//demanda e oferta, valores

        fstream file;
        IloEnv& env;
        IloCplex& cplex;
        IloObjective objective;
        IloArray<IloNumArray*> custo;
        IloNumArray demanda;
        IloNumArray oferta;
        IloModel model;
    };
}


#endif