/* 
 * File:   main.cpp
 * Author: sorem
 *
 * Created on 17 de junio de 2019, 01:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "Capa.h"
#include "Usuario.h"
#include "Imagen.h"

#include "ArbolAVL.h"
#include "ArbolBB.h"

#include "Cola.h"
#include "ListaDobleCircular.h"

#include "Matriz.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    int i = 0;
    
    Matriz *matriz = new Matriz();
    matriz->AgregarEn(0,0,"A");
    
    matriz->AgregarEn(2,3,"B");
    matriz->AgregarEn(0,0,"C");
    matriz->AgregarEn(1,5,"D");
    
    cout << matriz->Dot();
}

