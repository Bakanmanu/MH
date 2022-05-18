/**
 * @file MDD.cpp
 * @author Manuel Zafra Mota (mzafra24@correo.ugr.es)
 * @brief Cabeceras de los algoritmos (greedy y BL) y funciones auxiliares
 * para el problema de la Mínima Dispersión Diferencial(MDD) 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _MDD_H_
#define _MDD_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <utility>

using namespace std;

/**
 * @brief 
 * 
 */

class MDD{
    private:
        /******** CONSTANTES *********/
        
        const int NUM_CONJ_SOL = 50;

        /**
         * @brief Matriz que contiene los datos de las distancias de un indice a otro, solo está completa la diagonal superior derecha
         * 
         */
        vector<vector<double>> matriz;
        
        int num_elem,
            num_sel;

       

        /**
         * @brief Vector de booleanos (inicializado en TRUE) en el cual cada posicion corresponde a un elemento de la lista de candidatos,
         * el cual si es true sigue siendo un candidato para el vector solucion y
         * si es false significa que ya ha sido introducido en el vector solucion.
         */
        vector<bool> listaCandidatos; 



        /*********** Métodos privados que usarán los algoritmos ************/
        
        /**
         * @brief Metodo para guardar los valores dados en un fichero, los valores a tomar son:
         * num_elem -> Número de elementos del problema
         * num_sel -> Numero de elementos a seleccionar del problema
         * matriz -> Distancias de un elemento a otro 
         * 
         * @param archivo Nombre del archivo del que obtener los datos de la matriz
         */
        void lecturaDatosFichero(char* archivo);

        /**
         * @brief Imprime por pantalla la matriz de distancias
         * 
         */
        void imprimirMatriz();

        /**
         * @brief Obtiene el valor de la matriz,
         * teniendo en cuenta que solo está rellena la diagonal superior
         * Con lo cual si con los indices dados el valor es 0, 
         * se devuelve el valor con los indices permutados
         * @param indice1 
         * @param indice2 
         * @return double 
         */
        double getValorMatriz(int indice1, int indice2);

        /**
         * @brief Calcula la suma de distancias del candidato al vector solucion
         * 
         * @param candidato 
         * @return double 
         */
        double calcularSumaDistancias(vector<int> &solucion, int candidato);

        double obtenerDistanciaMax(vector<pair<int, double>> distancias);

        double obtenerDistanciaMin(vector<pair<int, double>> distancias);

         /**
         * @brief Getter del numero de elementos del problema
         * 
         * @return int 
         */
        int getN(){return num_elem;};

        /**
         * @brief Getter del numero de elementos que debe tener la solucion del problema 
         * 
         * @return int 
         */
        int getM(){return num_sel;};

        /*************** Metodos privados creados para la practica 2 **************/

        /**
         * @brief Método para generar los vectores de soluciones aleatorios
         * Para la creacion de los vectores aleatorios,
         * voy a obtener posiciones del vector de manera aleatoria,
         * que serán los elementos seleccionados para la solucion
         * @return Conjunto de vectores solucion
         */
        vector<vector<bool>> generarSoluciones();

        /**
         * @brief Muestra la matriz de booleanos proporcionada
         * 
         * @param conj_sol 
         */
        void mostrarMatrizBool(vector<vector<bool>> conj_sol);

        /***  Metodos de los cruces  ***/

        void cruceUniforme(); 
        void crucePosicion();

    public:
        
        
        /**
         * @brief Constructor del problema que obtiene los datos del archivo pasado por parámetros y los inicializa en los atributos
         * 
         * @param archivo Variable cuyo valor es la direccion de un archivo txt con los valores a tener en cuenta en el problemas
         */
        MDD(char* archivo);      

        /************ Métodos de los algoritmos a realizar ***********/  
        
        /**
         * @brief Función que aplicará el algoritmo greedy para resolver el problema
         * 
         * @param seed Valor de la semilla que tendrá la funcion que determina el valor aleatorio
         */
        vector<int> greedy(int seed);

        /**
         * @brief 
         * 
         */
        void BusquedaLineal();


        /**
         * @brief Función del algoritmo genetico generacional con cruce uniforme
         * 
         */
        void AGGU();

        /**
         * @brief Función del algoritmo genetico generacional con cruce de posición
         * 
         */
        void AGGP();

        /**
         * @brief Función del algoritmo genetico estacionario con cruce uniforme
         * 
         */
        void AGEU();

        /**
         * @brief Función del algoritmo genetico estacionario con cruce de posición
         * 
         */
        void AGEP();

};
#endif