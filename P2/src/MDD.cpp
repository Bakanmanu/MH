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
        for(int j=0; j<num_elem;j++){
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


vector<double> MDD::calcularVectorDistancias(vector<bool> v_sol){
    vector<double> v_dist;
    for(unsigned i=0; i<v_sol.size(); i++){         // 
        double suma_dist=0;                         // Inicializamos la variable que almacenara la suma de distancias
        if(v_sol[i]){                               // Si la posicion i del vector es true, entendemos que el elemento con ese indice pertenece a la solucion proporcionada y procedemos a trabajar con el
            for(unsigned j=0; j<v_sol.size();j++){  
                if(v_sol[j])                        // Solo debemos tener en cuenta los elementos que sean de la solucion para la suma de distancias 
                suma_dist += getValorMatriz(i, j);
            }
            v_dist.push_back(suma_dist);            // Una vez obtenida la distancia, la introducimos en el vector de distancias 
        }
    }
    return v_dist;
}


double MDD::obtenerDistanciaMax(vector<double> distancias){
    double  dist_max = 0;                   // Inicializamos la dist_max a 0 para que siempre obtenga al menos un valor
    for(int i=0; i<distancias.size(); i++)  // Iteramos sobre el vector dado
        if(distancias[i]>dist_max)   // Si el valor del vector es mayor que la dist_max  
            dist_max = distancias[i];// Reasignamos el valor de dist_max

    return dist_max;        
}

double MDD::obtenerDistanciaMin(vector<double> distancias){
    double dist_min=distancias[0];   // Inicializo la dist_min al primer valor del vector solucion para tener una referencia inicial especifica
    
    for (int i=1; i<distancias.size(); i++) // Itero sobre el vector dado
        if(distancias[i] < dist_min)        // Si el valor del vector es mayor que la dist_min
            dist_min = distancias[i];       // Reasigno el valor de dist_min
    
    return dist_min;
}

/*vector<int> MDD::greedy(int seed){

    vector<int>                 solucion;                       //Vector que contiene el conjunto de elementos que forman la solucion al problema
    
    vector<pair<int, double>>   suma_distancias_solucion;       //Vector SumaAnterior que se irá actualizando cada vez que se inserte un nuevo elemento al vector solucion
           
    double              dispersion_fin,
                        distancia_min,
                        distancia_max,
                        distancia_aux;

    srand(seed);                                                // Configuro la semilla para el valor aleatorio
    int candidato_inicial = rand() % (num_elem-1);              // Escojo el valor aleatorio con el que empezar el algoritmo
    solucion.push_back(candidato_inicial);                      // Coloco el primer elemento escogido aleatoriamente en el vector solucion
    suma_distancias_solucion.emplace_back(pair<int, double> (candidato_inicial, 0.0));
    listaCandidatos[candidato_inicial] = false;                 // Elimino el valor escogido de la lista de candidatos

    // Inicio la busqueda hasta completar el vector solucion
    while (solucion.size() < num_sel){

        pair<int,double> dispersion_min(0,0.0);                         //Pareja minima que contiene el indice y su dispersion 
                                    
        //Comienzo la obtencion de la dispersion de cada elemento
        for(int i=0; i<listaCandidatos.size(); i++){                //Itero sobre los candidatos para actualizar la suma de distancias
            if(listaCandidatos[i]){         // Si el valor es true significa que el candidato a calcular no está en el vector solucion

                //Copiamos el vector suma_solucion para no modificar el original hasta saber cual es el elemento a introducir
                vector<pair<int,double>> suma_dist_sol_aux(suma_distancias_solucion);                
                
                //Actualizo la suma_distancias del vector aux_solucion
                for(int j=0; j<suma_distancias_solucion.size(); j++)
                    suma_dist_sol_aux[j].second += getValorMatriz(suma_dist_sol_aux[j].first, i);
                
                //Obtengo la suma_distancia del nuevo candidato
                distancia_aux = calcularSumaDistancias(solucion, i);

                //Introduzco la suma distancia del nuevo candidato
                suma_dist_sol_aux.emplace_back(pair<int,double>(i, distancia_aux));   

                //Actualizo los maximos y los minimos del vector 
                distancia_min = obtenerDistanciaMin(suma_dist_sol_aux);
                distancia_max = obtenerDistanciaMax(suma_dist_sol_aux);

                double dispersion_candidato;                    // Valor de la dispersion del vector con el candidato introducido

                if (suma_dist_sol_aux.size() < 3)               // Comprobacion para el primer elemento introducido, ya que si solo hay dos elementos en el vector, la dispersion es 0 y esto hace que inserte siempre el ultimo candidato evaluado
                    dispersion_candidato = distancia_max;
                else                                            // Resto de casos para el calculo de la dispersion con mas de dos distancias calculadas
                    dispersion_candidato = distancia_max - distancia_min;

                // Paso los valores de la dispersion a una variable auxiliar
                pair<int, double> dispersion_aux(i,dispersion_candidato);

                // Comprobacion para recibir la dispersion calculada del primer candidato
                if(dispersion_min.second == 0.0)
                    dispersion_min = dispersion_aux;
                  // Compruebo si la dispersion es menor que la obtenida anteriormente       
                else if(dispersion_aux.second < dispersion_min.second) 
                    dispersion_min = dispersion_aux;
                
            }      
        }   // Una vez obtenido el candidato a introducir

        // Introduzco el indice del candidato en el vector solucion
        solucion.push_back(dispersion_min.first);
            
        // Introduzco el candidato en el vector de suma_distancias para actualizarlo mas tarde
        suma_distancias_solucion.emplace_back(pair<int, double>(dispersion_min.first,NULL));

        // Elimino el candidato de la lista de candidatos
        listaCandidatos[dispersion_min.first]= false;

        // Actualizo el vector de sumas distancias solucion  
        if(solucion.size() > 1){
            for(int i=0;i<suma_distancias_solucion.size();i++){
                suma_distancias_solucion[i].second = calcularSumaDistancias(solucion, suma_distancias_solucion[i].first);
            }
        }
        dispersion_fin = dispersion_min.second;         // Dispersion_fin guardará en todos los casos la dispersion del vector solución    
    }
cout << dispersion_fin << endl;    // Imprime la dispersión final para la obtencion de datos para la tabla de la memoria
return solucion;
}
*/


void MDD::BusquedaLineal(){
    // Algoritmo no implementado
}

vector<vector<bool>> MDD::generarSoluciones(){
    // Creamos el conjunto de vectores solucion -> matriz_sol[Vector_i][elem_vector]
    // Cada posicion del vector de booleanos representa un elemento y su valor, si dicho elemento es seleccionado o no
    vector<vector<bool>> matriz_sol(NUM_CONJ_SOL, vector<bool> (getN(), 0));

    // Procedemos a la generacion de los vectores de manera aleatoria
    for(unsigned i=0; i<matriz_sol.size(); i++){   // bucle para iterar sobre los vectores
        for(unsigned j=0; j<getM(); j++){   // bucle para insertar una cantidad M de 1s en cada vector
            int rand_pos = rand()%getN();       // Posicion del vector aleatoria
            if(matriz_sol[i][rand_pos] == 0)    // Comprobar que esa posicion no se haya repetido
                matriz_sol[i][rand_pos] = 1;
            else                                // En caso de que se repita la posicion, reiniciamos la iteracion
                j--;
        }
    }
    return matriz_sol;
}

void MDD::mostrarMatrizBool(vector<vector<bool>> conj_sol){
    for (int i=0; i<conj_sol.size(); i++){
        cout << "| ";
      //  cout << "Iteracion " << i << " del primer for. "<< endl;
        for(int j=0; j<conj_sol[i].size(); j++){
        //    cout << "Iteracion " << j << " del segundo for. "<< endl;
            cout << conj_sol[i][j] << " ";
        }
        cout << "|"<<endl;        
    }
}

void MDD::cruceUniforme(){

}

void MDD::crucePosicion(){

}



