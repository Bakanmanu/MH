/**
 * @file MDD.cpp
 * @author Manuel Zafra Mota (mzafra24@correo.ugr.es)
 * @brief Implementación de las funciones a usar para el desarrollo de los algoritmos Greedy Y Busqueda Lineal
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>

#include "MDD.h"

using namespace std;

void MDD::lecturaDatosFichero(string archivo){
//  Acceso al archivo proporcionado
    ifstream file(archivo);
    if(!file.is_open()){
        
    }

// Guardamos los valores de la primera fila que son el numero de elementos y la cantidad de elementos a elegir
    file >> num_elem >> num_sel;

// Inicializamos la matriz     
// vector<vector<double>> matriz (num_elem, vector);
    
// Introducimos los valores del archivo en la matriz    
    int file_i, file_j, file_d;
// Calculamos la cantidad de lineas a introducir que tiene el fichero    
    const int NUM_LINEAS = num_elem*(num_elem-1)/2;

    for(int i=0; i < NUM_LINEAS; i++){
        file >> file_i >> file_j >> file_d;
        matriz[file_i][file_j] = file_d;
    }

    //Imprimo la matriz para comprobar la insercion de los datos es correcta
    for(int i=0; i<num_elem; i++){
        for(int j=i; j<num_elem;j++){
            cout << matriz[i][j] << " " ;
        }
        cout << endl;
    }

};



void MDD::greedy(int n, int m, double *dist){


}