#include "Toolkit.h"

using namespace Toolkit;

void Problem::readFile(bool dual = false){
    if(file.is_open()){
        file >> n;
        file >> m;
        #ifdef DEBUG
            cout << n << " " << m << endl;
        #endif
        if(dual){
            this->dual();
            return;
        }
        
        //IloArray<IloNumArray> custo(env, n);
        for(int i = 0; i < n; i++){//Inicializa matrix de custo
            this->custo.add(new IloNumArray(env, m));
            for(int j = 0; j < m; j++){
                file >> (*custo[i])[j];//adiciona custo do arquivo
            }
        }

        //Obrigatorio o uso do metodo add
        //a sobrecarga [] não aloca mais memoria
        for(int i = 0; i < m; i++){//Demanda
            IloNum num;
            file >> num;
            demanda.add(num);
            this->deman += num;
            //file >> demanda[i]; //errado
        }

        for(int i = 0; i < n; i++){//Oferta
            IloNum num;
            file >> num;
            oferta.add(num);
            this->ofer += num;
        }

        this->balancear();//Só balancea se necessario

        #ifdef DEBUG
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    cout << (*custo[i])[j] << " ";
                }
                cout << endl;
            }
            cout << "Demanda ";
            for(int i = 0; i < m; i++){
                cout << demanda[i] << " ";
            }
            cout << endl;
            cout << "Oferta ";
            for(int i = 0; i < n; i++){
                cout << oferta[i] << " ";
            }
            cout << endl;
        #endif
    }else{
        this->erro = true;
    }
}

bool Problem::balancear(){
    if(isBalanced())
        return false;
    if(ofer > deman){
        demanda.add(ofer - deman);
        for(int i = 0; i < n; i++){
            (*custo[i]).add(0);
        }
        this->m += 1;
    }

    return true;
}

void Problem::run(){
    clock_t start, end;
    start = clock();
    IloArray<IloNumVarArray> var_x(env, n);
    for(int i = 0; i < n; i++){
        var_x[i] = IloNumVarArray(env, m, 0, IloInfinity);
    }

    IloExpr expr(env);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            expr += (*custo[i])[j] * var_x[i][j];
        }
    }
    model.add(IloMinimize(env, expr)); //Adiciona função objetivo ao modelo
    expr.clear();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            expr += var_x[i][j];
        }   
        model.add(expr <= oferta[i]);
        expr.clear();     
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            expr += var_x[j][i];
        }
        model.add(expr >= demanda[i]);
        expr.clear();
    }

    string s;
    stringstream str(s);
    str << this->output_name;
    str << ".lp";

    this->cplex.extract(model);
    this->cplex.exportModel(str.str().c_str());

    env.out() << "Variaveis binarias: " << cplex.getNbinVars() << endl;
    env.out() << "Variaveis Inteiras: " << cplex.getNintVars() << endl;
	env.out() << "Filas - Restrições: " << cplex.getNrows() << endl;
    env.out() << "Colunas - Variaveis: " << cplex.getNcols() << endl;

    if(!this->cplex.solve()){
        cerr << "Não Foi possivel resolver o Problema" << endl;
        throw(-1);
    }
    end = clock();
    // Get solution

    ofstream saida(this->output_name);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            saida << cplex.getValue(var_x[i][j]) << " ";
        }
        saida << endl;
    }
    saida << "Balanceado: " << ((isBalanced())? "Sim": "Não") << endl;
    saida << "Status: " << cplex.getStatus() << endl;
    saida << "Valor Fobj: " << cplex.getObjValue() << endl;
    saida << "Tempo: " << end - start;

    saida.close();   

    #ifdef DEBUG
        cout << "Chego aqui" << endl;
    #endif
}

IloObjective& Problem::getObjective(){
    return this->objective;
}

IloModel& Problem::getModel(){
    return this->model;
}

bool Problem::isBalanced(){    
    if(this->deman == this->ofer)
        return true;
    return false;
}

void Problem::setOutputFileName(string file_name){
    this->output_name = file_name;
}

void Problem::dual(){
    
}