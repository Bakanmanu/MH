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
         * @brief Metodo para guardar en la matriz dada por un fichero en el atributo del objeto
         * 
         * @param archivo Nombre del archivo del que obtener los datos de la matriz
         */
        void lecturaDatosFichero(char* archivo);

        void imprimirMatriz();


        /**
         * @brief Función que aplicará el algoritmo greedy para resolver el problema
         * 
         * @param n Numero de posibles posiciones que puede tomar el algoritmo
         * @param m Número de posiciones que debe de tomar para resolver el algoritmo
         * @param dist Matriz simétrica de tamaño n que contiene las distancias entre los elementos
         */
        void greedy(int n, int m, double *dist);

        /**
         * @brief 
         * 
         */
        void BusquedaLineal();



};
#endif