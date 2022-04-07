#include <iostream>
#include <fstream>
#include "MDD.h"
#include "random.hpp"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
    /**
     * @todo {          
     * } 
     *  
    */
    cout << argv[1] << endl;

    MDD Problema(argv[1]);


    Problema.imprimirMatriz();


   cout << endl; 
}
