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
#include <vector>
#include <random>       // srand, rand
#include <utility>      // pair

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
// Creamos una matriz auxiliar con el tamaño deseado     
    vector<vector<double>> matriz_aux( num_elem, vector<double> (num_elem) );
    matriz = matriz_aux;    
// Creamos la lista de candidatos con el tamaño deseado
    vector<bool> lista_aux(num_elem, true);
    listaCandidatos = lista_aux;
// Calculamos la cantidad de lineas a introducir que tiene el fichero    
    const int NUM_LINEAS = num_elem*(num_elem-1)/2;

// Introducimos los valores del archivo en la matriz    
    int file_i, file_j;
    double file_d;
    
    for(int i=0; i < NUM_LINEAS; i++){      // Segun el patron de valores de los archivos, obtenemos:
        file >> file_i;                     // El primer indice de la matriz (equivale a la primera posicion) 
        file >> file_j;                     // El segundo indice de la matriz (equivale a la segunda posicion)
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

double MDD::getValorMatriz(int indice1, int indice2){
    double valor;
    if(matriz[indice1][indice2] != 0)          
        valor = matriz[indice1][indice2];
    else
        valor = matriz [indice2][indice1];
    
    return valor;
}

double MDD::calcularSumaDistancias(vector<int> &solucion, int candidato){
    double suma_distancias = 0;                                         //Inicializo la suma de distancias 
    for(int i=0; i<solucion.size(); i++){                               //Bucle para recorrer el vector solucion
        if(candidato != solucion[i])                                    //Saltamos las sumas con ambos indices iguales
            suma_distancias += getValorMatriz(solucion[i], candidato);  //Suma la distancia desde el candidato al elemento del vector solucion
    }
    return suma_distancias;
}

double MDD::obtenerDistanciaMax(vector<pair<int, double>> distancias){
//#IMPLEMENTAR
}

double MDD::obtenerDistanciaMin(vector<pair<int, double>> distancias){
//#IMPLEMENTAR
}


vector<int> MDD::greedy(int seed){

    vector<int> solucion;               //Vector que contiene el conjunto de elementos que forman la solucion al problema
    
    srand(seed);                                                // Configuro la semilla para el valor aleatorio
    int candidato_inicial = rand() % (num_elem-1);              // Escojo el valor aleatorio con el que empezar el algoritmo
    solucion.push_back(candidato_inicial);                      // Coloco el primer elemento escogido aleatoriamente en el vector solucion
    listaCandidatos[candidato_inicial] = false;                 // Elimino el valor escogido de la lista de candidatos

    // Inicio la busqueda hasta completar el vector solucion
    while (solucion.size() < num_sel){

        pair<int,double>    dispersion_min(0,0.0);                     //Pareja minima que contiene el indice y su dispersion 
                            

        double              distancia_min,
                            distancia_max,
                            distancia_sol,
                            distancia_aux;

        vector<pair<int, double>>   funcion_suma_distancias,        //Vector de pares que contiene el elemento y la suma de las distancias a los elementos del vector solucion(indice, suma_distancias_indice)
                                    suma_distancias_solucion;       //Vector SumaAnterior que se irá actualizando cada vez que se inserte un nuevo elemento al vector solucion
                                    
        //Comienzo la obtencion de la dispersion de cada elemento
        for(int i=0; i<listaCandidatos.size(); i++){                //Itero sobre los candidatos para actualizar la suma de distancias
            if(listaCandidatos[i]){

                //Obtengo la suma_distancia del nuevo candidato
                distancia_aux = calcularSumaDistancias(solucion, i);

                //Copiamos el vector suma_solucion para no modificar el original hasta saber cual es el elemento a introducir
                vector<pair<int,double>> suma_dist_sol_aux(suma_distancias_solucion);       
                
                //Actualizo la suma_distancias del vector solucion
                for(int j=0; j<suma_distancias_solucion.size(); j++)
                    suma_dist_sol_aux[j].second += getValorMatriz(suma_dist_sol_aux[j].first, i);
                
                
                //Introduzco la suma distancia del nuevo candidato
                suma_dist_sol_aux.emplace_back(pair<int,double>(i, distancia_aux));   

                //Actualizo los maximos y los minimos del vector 
                distancia_min = obtenerDistanciaMin(suma_dist_sol_aux);
                distancia_max = obtenerDistanciaMax(suma_dist_sol_aux);

                // Paso los valores de la dispersion a una variable auxiliar
                pair<int, double> dispersion_aux(i, distancia_max - distancia_min);

                // Comprobacion para recibir la dispersion calculada del primer candidato
                if(dispersion_min.second == 0.0){
                    dispersion_min = dispersion_aux;
                }   // Compruebo si la dispersion es menor que la obtenida anteriormente       
                else if(dispersion_aux.second < dispersion_min.second){     
                    dispersion_min = dispersion_aux;
                }

            }
           
                    
        }   // Una vez obtenido el candidato a introducir
            // Introduzco el indice del candidato en el vector solucion
        solucion.push_back(dispersion_min.first);
            // Elimino el candidato de la lista de candidatos
        listaCandidatos[dispersion_min.first]= false;
            // Actualizo el vector de sumas distancias solucion         #REVISAR
        for(int i=0;i<solucion.size();i++){
            suma_distancias_solucion[i].second = calcularSumaDistancias(solucion, suma_distancias_solucion[i].first);
        }

    }


return solucion;
}




void MDD::BusquedaLineal(){

}