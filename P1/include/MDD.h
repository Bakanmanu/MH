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
#include <string>

#include "random.hpp"

using namespace std;

/**
 * @brief 
 * 
 */

class MDD{
    private:
        vector<vector<double>> matriz;
        int num_elem, num_sel;

    public:
        /**
         * @brief Construct a new MDD object
         * 
         * @param archivo 
         */
        MDD(char* archivo);      
        
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



};
#endif