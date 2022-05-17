#include <iostream>
#include <fstream>
#include "MDD.h"
#include "random.hpp"
#include <string>
#include <vector>


using namespace std;

int main(int argc, char** argv){
  
    if (argc < 2){
        cout << "ERROR: Formato del ejecutable: ./main <nombre_archivo> <semilla (opcional)>";
    }else if(argc == 3){            // En el caso de querer usar una semilla especifica
        MDD Problema(argv[1]);
        vector<int> sol = Problema.greedy(argv[2]);
    }else{                          // Si no se proporciona una semilla, usará las predeterminadas
        for (int i=3; i<8; i++){
            int seed = i*1534890;
            MDD Problema(argv[1]);

            vector<int> sol = Problema.greedy(seed);

            /*
            cout << "La solucion es: (";
            for(int i=0; i<sol.size(); i++){
                cout <<sol[i]<<" ";
            }
            cout << ")" << endl;  
            */
        }
    }
        cout << endl;
}
