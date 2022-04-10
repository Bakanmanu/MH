#include <iostream>
#include <fstream>
#include "MDD.h"
#include "random.hpp"
#include <string>
#include <vector>


using namespace std;

int main(int argc, char** argv){
    /**
     * @todo {          
     * } 
     *  
    */
//    cout << argv[1] << endl;

    MDD Problema(argv[1]);


    Problema.imprimirMatriz();

    vector<int> sol = Problema.greedy(1);

    cout << "La solucion es: (";
    for(int i=0; i<sol.size(); i++){
        cout <<sol[i]<<" ";
    }
    cout << ")" << endl; 
}
