#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <iostream>
#include <fstream>
#include <ilcplex/ilocplex.h>

using namespace std;

namespace Toolkit{
    /*
    * Extrai os coeficientes do arquivo.
    * O arquivo que guarda os dados é padroniazado da seguinte forma:
    * linha     texto                   Descrição
    *   1       n, m\n                  n,m são respectivamente linhas e colunas
    *   2       x11, x12, x13,..., x1m  Matrix[n, m] de custo da função objetivo.
    *   3       x21, x22, x23,..., x2m
    *   4       x31, x32, x33,..., x3m
    *   .       ......................
    *   n+1     xn1, xn2, xn3,..., xnm
    */
    class Problem{
    public:
        Problem(string file_name, IloEnv& env) : file(file_name), 
            model(env), 
            objective(env),
            var_x(env),
            erro(!file.is_open()) {}
        ~Problem(){
          file.close();  
        }

        void readFile();
        void run();
        //getters
        IloObjective& getObjective();
        IloModel& getModel();
        //setters

        //others
        bool hasError();
    private:
        bool erro = false;
        fstream file;
        IloObjective objective;
        IloNumVarArray var_x;
        IloModel model;
    };
}


#endif