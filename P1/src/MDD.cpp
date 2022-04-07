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
#include <random>

#include "MDD.h"

using namespace std;


MDD::MDD(char* archivo){
    lecturaDatosFichero(archivo);
};

void MDD::lecturaDatosFichero(char* archivo){
//  Acceso al archivo proporcionado
    ifstream file(archivo);
    if(!file.is_open()){
        cerr << "Error al intentar abrir el archivo " << archivo << endl;
        exit(0);
    }

// Guardamos los valores de la primera fila que son el numero de elementos y la cantidad de elementos a elegir
    file >> num_elem 
         >> num_sel;
// Creamos una matriz auxiliar con el tamaño deseado, la cual pasaremos por referencia a la matriz atributo     
    vector<vector<double>> aux( num_elem, vector<double> (num_elem) );
    matriz = aux;    

// Calculamos la cantidad de lineas a introducir que tiene el fichero    
    const int NUM_LINEAS = num_elem*(num_elem-1)/2;

// Introducimos los valores del archivo en la matriz    
    int file_i, file_j;
    double file_d;
    
    for(int i=0; i < NUM_LINEAS; i++){      // Segun el patron de valores de los archivos, obtenemos:
        file >> file_i;                     // El primer indice de la matriz (equivale a la primera posicion) 
        file >> file_j;                      // El segundo indice de la matriz (equivale a la segunda posicion)
        file >> file_d;                     // La distancia de la primera posicion a la segunda
        matriz[file_i][file_j] = file_d;    // Introducimos el valor en la matriz
    }
    
};

void MDD::imprimirMatriz(){
    cout << "Matriz de valores: "<< endl;
    for(int i=0; i<num_elem-1; i++){
        cout << "| ";
        for(int j=i+1; j<num_elem;j++){
            cout << matriz[i][j] << " " ;
        }
        cout << " |" << endl;
    }

};


vector<int> MDD::greedy(int seed){
    /**
     * @brief Vector de booleanos (inicializado en TRUE) en el cual cada posicion corresponde a un elemento de la lista de candidatos,
     * el cual si es true sigue siendo un candidato para el vector solucion y
     * si es false significa que ya ha sido introducido en el vector solucion y no debemos operar con el.
     */
    vector<bool> listaCandidatos(num_elem, true); 
    /**
     * @brief Vector que contiene el elemento de conjunto que forman la solucion al problema
     */
    vector<int> solucion(num_sel);
    
    srand(seed);                                                // Configuro la semilla para el valor aleatorio
    int candidato_inicial = rand() % (num_elem-1);              // Escojo el valor aleatorio con el que empezar el algoritmo
    solucion.push_back(candidato_inicial);                      // Coloco el primer elemento escogido aleatoriamente en el vector solucion
    listaCandidatos[candidato_inicial] = false;                 // Elimino el valor escogido de la lista de candidatos

    // Inicio la busqueda 
    while (solucion.size() < num_sel){
        
        

    }


return solucion;
};