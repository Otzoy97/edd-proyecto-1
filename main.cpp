/* 
 * File:   main.cpp
 * Author: sorem
 *
 * Created on 17 de junio de 2019, 01:16 PM
 */

#include "NodoB.h"

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>
#include <exception>

#include "Capa.h"
#include "Usuario.h"
#include "Imagen.h"
#include "ArbolAVL.h"
#include "ArbolBB.h"

#include "Cola.h"
#include "ListaDoble.h"

#include "Matriz.h"
#include "NodoM.h"
#include "NodoB.h"
#include "NodoL.h"

#include "Lista.h"

#include "Pila.h"


using namespace std;

bool LeerCapa(string const &);
bool LeerUsuario(string const &);
bool LeerImagen(string const &);
void EscribirArchivo(string const &, string const &);
void Graphviz(string const&);

void CargarArchivo();
void RenderizarImagen();
void Reportes();
void ABCUsuario();

ArbolB *arbolCapas = new ArbolB();
ArbolAVL *arbolUsuarios = new ArbolAVL();
Lista *listaImagenes = new Lista();


/*
 * 
 */
int main(int argc, char** argv) {
//    int aux, id, hasta;
//    static int top[5] ;
//    static int fil[5];
//    do{
//    scanf("%d %d", &id, &aux);
//    cout << endl;
//    
//                for(int i = 0; i < 5; i++){
//                    if(aux >= top[i]){
//                        //hasta = i==0 ? 1 : 0;
//                        for(int j = 4; j >= (i==0 ? i+1 : i); j--){
//                                top[j] = top[j-1];
//                                fil[j] = fil[j-1];
//                            }
//                        top[i] = aux;
//                        fil[i] = id;
//                        break;
//                    }
//                }
//    for(int i = 0 ; i<5; i++){
//        cout << *(fil + i) << " -> " << *(top  +i) << endl;
//    }
//    cout << endl;
//    } while(true);
    string decision;
    //Al comenzar mostrará el menu en un ciclo infinito :v
    do{
        cout << endl;
        cout << "    <-MENU->" <<endl;
        cout << " 1. Cargar archivos" <<endl;
        cout << " 2. Renderizar imagen" <<endl;
        cout << " 3. Estado de memoria" <<endl;
        cout << " 4. ABC Usuarios" <<endl;
        cout << " 5. Salir" <<endl;
        cin >> decision;
        if (decision == "1"){
            CargarArchivo();
        } else if (decision == "2"){
            RenderizarImagen();
        } else if (decision == "3"){
            Reportes();
        } else if (decision == "4"){
            ABCUsuario();
        } else if (decision == "5"){
            return 0;
        } else {
            cout << "\"" << decision << "\" no es una opción valida" << endl;
        }
        cout << endl;
    }while(true);
    /*ListaDoble *l = new ListaDoble();
    for(int i = 0 ; i< 0;i++){
        l->AgregarAlFinal(i);
    }
    l->Eliminar(0);
    l->Eliminar(1);
    l->Eliminar(9);
    l->Eliminar(5);
    l->AgregarAlFinal(10);
    l->AgregarAlFinal(10);        
    cout <<l->Dot("a") << endl;*/
//    LeerCapa("/home/sorem/capas");
//    LeerImagen("/home/sorem/imagenes");
//    LeerUsuario("/home/sorem/Descargas/usuarios.txt");
//    stringstream str;
//    str << "digraph G{" << listaImagenes->Dot() << listaImagenes->ListarImagenes() << "}" <<endl;
//    EscribirArchivo("img",str.str());
//    Graphviz("img");
//    str.str(string());
//    str << "digraph G{" << arbolCapas->Dot() << "}" << endl;
//    EscribirArchivo("capasTree", str.str());
//    Graphviz("capasTree");
//    str.str(string());
//    EscribirArchivo("userTree", arbolUsuarios->Dot());
//    Graphviz("userTree");
}  

void ABCUsuario(){
    string decision;
    regex r("[0-9]+");
    do{
        cout << "    ABC USUARIOS" << endl;
        cout << " 1. Agregar usuario (solo ID)" << endl;
        cout << " 2. Modificar usuario" << endl;
        cout << " 3. Eliminar usuario" << endl;
        cout << " 4. Regresar a MENU" << endl;
        cin >> decision;
        if(decision == "1"){
            cout << "Especifica el ID del usuario";
            cin >> decision;
            //Busca si el usuario ya existe
            NodoB<Usuario> *temp = arbolUsuarios->Buscar(decision);
            //Si es nulo, no existe, por lo tanto sí se puede agregar
            if(temp){
                cout << "\"" << decision << "\" ya existe" << endl;
                continue;
            }
            ListaDoble *list = new ListaDoble();
            Usuario user(decision,list);
            arbolUsuarios->Agregar(user);
            cout << "Usuario agregado exitosamente" << endl;
        } else if (decision == "2"){
            cout << "Especifique el ID del usuario a modificar" << endl;
            cin >> decision;
            //busca el usuario
            NodoB<Usuario> *auxUser = arbolUsuarios->Buscar(decision);
            if(!auxUser){
                cout << "No se encontró el usuario " << decision << endl;
                continue;
            }
            //Si existe, continúa el flujo
            do{
                cout << "    MODIFICAR USUARIO" << endl;
                cout << " 1. Agregar imagen" << endl;
                cout << " 2. Eliminar imagen" << endl;
                cout << " 3. Regresar a ABC USUARIOS" << endl;
                cin >> decision;
                if(decision == "1"){
                    cout << "Especifique el id de la imagen que desea agregar al usuario " << auxUser->Dato().Id() <<endl;
                    cin >> decision;
                    if(regex_match(decision,r)){
                        int ID;
                        istringstream iss (decision);
                        iss >> ID;
                        if(listaImagenes->Existe(ID)){
                            cout << "La imagen con id = " << ID << " no existe en memoria" << endl;
                            continue;
                        }
                        //Si existe la imagen
                        //Verifica que el usuario no posea ya ese id
                        if(auxUser->Dato().Imagenes()->Existe(ID)){
                            cout << "El usuario " << auxUser->Dato().Id() << "ya posee una imagen con id = " << ID << endl << "No se puede agregar la imagen " << ID << endl;
                            continue;
                        }
                        //el usuario no posee ese id
                        auxUser->Dato().Imagenes()->AgregarAlFinal(ID);
                        arbolUsuarios->ModTop(auxUser->Dato().Id(),auxUser->Dato().Imagenes()->Largo());
                        cout << "Imagen " << ID << " agregada a " << auxUser->Dato().Id() <<" exitosamente" << endl;
                    } else {
                        cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
                    }
                } else if (decision == "2"){
                    cout << "Especifique el id de la imagen que desea eliminar del usuario " << auxUser->Dato().Id() <<endl;
                    cin >> decision;
                    if(regex_match(decision,r)){
                        int ID;
                        istringstream iss (decision);
                        iss >> ID;
                        //Verifica que el usuario posea ese id
                        if(!auxUser->Dato().Imagenes()->Existe(ID)){
                            cout << "El usuario " << auxUser->Dato().Id() << " no posee una imagen con id = " << ID << endl << "No se puede eliminar la imagen " << ID << endl;
                            continue;
                        }
                        //el usuario posee ese id
                        auxUser->Dato().Imagenes()->Eliminar(ID);
                        arbolUsuarios->ModTop(auxUser->Dato().Id(),auxUser->Dato().Imagenes()->Largo());
                        cout << "Imagen " << ID << " eliminada de " << auxUser->Dato().Id() <<" exitosamente" << endl;
                    } else {
                        cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
                    }
                } else if (decision == "3"){
                    break;
                } else {
                    cout << "\"" << decision << "\" no es una opción valida" << endl;
                }
            } while(true);
        } else if (decision == "3"){
            cout << "Especifique el ID del usuario a modificar" << endl;
            cin >> decision;
            //busca el usuario
            NodoB<Usuario> *auxUser = arbolUsuarios->Buscar(decision);
            if(!auxUser){
                cout << "No se encontró el usuario " << decision << endl;
                continue;
            }
            string tempNUser = auxUser->Dato().Id();
            //Si existe, continúa el flujo
            do{
                cout << "Se procederá a eliminar el usuario " << tempNUser << endl << "Confirme acción [s/n]" << endl;
                cin >> decision;
                if (decision == "s" || decision == "S"){
                    
                    arbolUsuarios->Remover(tempNUser);
                    arbolUsuarios->EliTop(tempNUser);
                    cout << "Eliminación exitosa" << endl;
                    break;
                } else if (decision == "n" || decision == "N"){
                    cout << "Eliminación cancelada" << endl;
                    break;
                } else {
                    cout << "\"" << decision << "\" no es una opción valida" << endl;
                }               
            } while (true);
        } else if (decision == "4") {
            return;
        } else {
            cout << "\"" << decision << "\" no es una opción valida" << endl;
        }
    }while(true);
}
/**
 * Muestra el menú de cargar archivos
 */
void CargarArchivo(){
    string decision;
    string URL;
    bool resultado;
    do{
        cout << "    <-CARGAR ARCHIVOS->" <<endl;
        cout << " 1. Capa" << endl;
        cout << " 2. Imagen" << endl;
        cout << " 3. Usuario" << endl;
        cout << " 4. Regresar a MENU" << endl << endl;
        cin >> decision;
        if (decision == "1"){
            cout << "Escriba la dirección absoluta del archivo" << endl;
            cin >> URL;
            resultado = LeerCapa(URL);
            if (resultado) 
                cout << "Capas cargadas correctamente" << endl;
            else 
                cout << "Ocurrió un error al cargar las capas" << endl;
        } else if (decision == "2"){
            cout << "Escriba la dirección absoluta del archivo" << endl;
            cin >> URL;
            resultado = LeerImagen(URL);
            if (resultado) 
                cout << "Imagenes cargadas correctamente" << endl;
            else
                cout << "Ocurrió un error al cargar las imagenes" << endl;
        } else if (decision == "3"){
            cout << "Escriba la dirección absoluta del archivo" << endl;
            cin >> URL;
            resultado = LeerUsuario(URL);
            if (resultado) 
                cout << "Usuarios cargados correctamente" << endl;
            else 
                cout << "Ocurrió un error al cargar los usuarios" << endl;
        } else if (decision  == "4"){
            return;
        } else {
            cout << "\"" << decision << "\" no es una opción valida" << endl << endl;
        }
    } while (true);
}
/**
 * Muestra el menú para renderizar archivo
 */
void RenderizarImagen(){
    string decision;
    regex r("[0-9]+");
    do{
        cout << "    <-RENDERIZAR IMAGEN->" << endl;
        cout << " 1. Por recorrido limitado" << endl;
        cout << " 2. Por id de imagen" << endl;
        cout << " 3. Por id de capa" << endl;
        cout << " 4. Por usuario" << endl << endl;
        cout << " 5. Regresar a MENU" << endl;
        cin >> decision;
        if(decision == "1"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo;
            cout << "Especifique la cantidad de capas que desea utilizar" << endl;
            cin >> decision;
            if(regex_match(decision,r)){
                int no;
                istringstream iss (decision);
                iss >> no;
                cout << "    Especifique el tipo de recorrido " << endl;
                cout << " 1. Preorden" << endl;
                cout << " 2. Inorden" << endl;
                cout << " 3. Postorden" << endl;
                cin >> decision;
                string dot;
                if(decision == "1"){
                   dot = arbolCapas->RenderizarPreOrden(no);
                   EscribirArchivo("PreCapa_"+to_string(no),dot);
                   Graphviz("PreCapa_"+to_string(no));
                } else if(decision == "2"){
                   dot = arbolCapas->RenderizarInOrden(no);
                   EscribirArchivo("InCapa_"+to_string(no),dot);
                   Graphviz("InCapa_"+to_string(no));
                } else if(decision == "3"){
                   dot = arbolCapas->RenderizarPostOrden(no);
                   EscribirArchivo("PostCapa_"+to_string(no),dot);
                   Graphviz("PostCapa_"+to_string(no));
                } else {
                    cout << "\"" << decision << "\"  no es una opción válida" << endl;
                    continue;
                }
            } else {
                cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
                continue;
            }
        } else if (decision == "2"){
            if(listaImagenes->EsVacia()){
                cout << "La lista de imágenes está vacía " << endl;
                continue;
            }
            //Posee algo
            cout << "Especifique el id de la imagen a renderizar" << endl;
            cin >> decision;
            if(regex_match(decision,r)){
                int ID;
                istringstream iss (decision);
                iss >> ID;
                if(listaImagenes->Existe(ID)){
                    cout << "La imagen con id = " << ID << " no existe en memoria" << endl;
                    continue;
                }
                string dot = listaImagenes->Renderizar(ID);
                try {
                    EscribirArchivo("Imagen"+to_string(ID),dot);
                    Graphviz("Imagen"+to_string(ID));
                } catch (exception &e){
                    cout << "Ocurrió un error al generar la imagen " << ID << ". " << e.what() << endl;
                }
            } else {
                cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
            }
        } else if (decision == "3"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //Posee algo
            cout << "Especifique el id de la capa a renderizar" << endl;
            cin >> decision;
            if(regex_match(decision,r)){
                int ID;
                istringstream iss (decision);
                iss >> ID;
                NodoB<Capa> *temp = arbolCapas->Buscar(ID);
                //Verifica que el nodo no sea nulo
                if(!temp){
                    cout << "La capa " << ID << " no existe" << endl;
                    continue;
                }
                string dot = temp->Dato().Capa_->Pintar();
                try {
                    EscribirArchivo("Imagen"+to_string(ID),dot);
                    Graphviz("Imagen"+to_string(ID));
                } catch (exception &e){
                    cout << "Ocurrió un error al generar la imagen " << ID << ". " << e.what() << endl;
                }
            } else {
                cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
            }
        } else if (decision == "4"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El arbol de usuarios está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            cout << "Especifique el id del usuario" << endl;
            cin >> decision;
            //Busca el usuario
            NodoB<Usuario> *temp = arbolUsuarios->Buscar(decision);
            //Verifica que no sea nulo
            if(!temp){
                cout << "El usuario \"" << decision << "\" no existe" << endl;
                continue;
            }
            //El usuario existe
            cout << "Especifique el ID de la imagen que desea renderizar" << endl;
            cin >> decision;
            if(regex_match(decision,r)){
                int ID;
                istringstream iss (decision);
                iss >> ID;
                if(!temp->Dato().Imagenes()->Existe(ID)){
                    cout << "La imagen con id = " << ID << " no existe para " << temp->Dato().Id() << endl;
                    continue;
                }
                //La imagen si existe para el usuario
                //Busca la imagen en la lista general
                if(!listaImagenes->Existe(ID)){
                    cout << "La imagen con id = " << ID << " no existe en memoria" << endl;
                    continue;
                }
                //La imagen sí existe
                string dot = listaImagenes->Renderizar(ID);
                try {
                    EscribirArchivo(temp->Dato().Id()+"Imagen"+to_string(ID),dot);
                    Graphviz(temp->Dato().Id()+"Imagen"+to_string(ID));
                } catch (exception &e){
                    cout << "Ocurrió un error al generar la imagen " << ID << ". " << e.what() << endl;
                }
            } else {
                cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
            }
        } else if (decision == "5"){
            return;
        } else {
            cout << "\"" << decision << "\" no es una opción valida"  << endl << endl;
        }
    }while(true);
}
/**
 * Muestra el menú de Reportes
 */
void Reportes(){
    string decision;
    stringstream str;
    regex r("[0-9]+");
    do{
        cout << "    <-ESTADO DE MEMORIA->" << endl;
        cout << " 1.  Ver lista de imagenes" << endl;
        cout << " 2.  Ver árbol de capas" << endl;
        cout << " 3.  Ver árbol de capas espejo" << endl;
        cout << " 4.  Ver capa" << endl;
        cout << " 5.  Ver imagen y árbol de capas" << endl;
        cout << " 6.  Ver árbol de usuarios" << endl;
        cout << "     <-OTROS REPORTES->" << endl;
        cout << " 7.  Top 5 imágenes con más número de capas" << endl;
        cout << " 8.  Cantidad de capas que son hojas" << endl;
        cout << " 9.  Profundidad de árbol de capas" << endl;
        cout << " 10. Mostrar arbol de capas en postorden" << endl;
        cout << " 11. Listar capas en preorden" << endl;
        cout << " 12. Listar capas en inorden" << endl;
        cout << " 13. Listar capas en postorden" << endl;
        cout << " 14. Top 5 usuario con más imágenes" << endl;
        cout << " 15. Árbol espejo de usuarios" << endl;
        cout << " 16. Listar usuarios en preorden" << endl;
        cout << " 17. Listar usuarios en inorden" << endl;
        cout << " 18. Listar usuarios en postorden" << endl;
        cout << " 19. Listar usuarios por niveles" << endl << endl;
        cout << " 20. Regresar a MENU" << endl;
        cin >> decision;
        if (decision == "1"){
            if(listaImagenes->EsVacia()){
                cout << endl << "La lista de imágenes está vacía" << endl;
                continue;
            }
            //La lista posee algo
            str.str(string());
            str << "digraph G{" << listaImagenes->Dot() << listaImagenes->ListarImagenes() << "}" <<endl;
            EscribirArchivo("EM_Lista",str.str());
            Graphviz("EM_Lista");
        } else if (decision == "2"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            str.str(string());
            str << "digraph G{" << arbolCapas->Dot() << "}" << endl;
            EscribirArchivo("EM_ACapas",str.str());
            Graphviz("EM_ACapas");
        } else if (decision == "3"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            EscribirArchivo("EM_ACapasE", arbolCapas->DotEspejo());
            Graphviz("EM_ACapasE");
        } else if (decision == "4"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            cout << "Especifique el id de la capa a mostrar" << endl;
            cin >> decision;
            if (regex_match(decision,r)){
                int ID;
                istringstream iss (decision);
                iss >> ID;
                NodoB<Capa> *temp = arbolCapas->Buscar(ID);
                if (!temp){
                    cout << "La capa " << decision << " no existe en el árbol de capas" << endl;
                    continue;
                }
                //El nodo recuperado no es nulo
                try{
                    EscribirArchivo("EM_Capa" + to_string(ID),temp->Dato().Capa_->Dot());
                    Graphviz("EM_Capa"+to_string(ID));
                } catch (exception &e){
                    cout << "Ocurrió un error al intentar generar la matriz para la capa " << ID << endl << e.what() << endl;
                }
            } else {
                cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
            }
        } else if (decision == "5"){
            if(listaImagenes->EsVacia()){
                cout << endl << "La lista de imágenes está vacía" << endl;
                continue;
            }
            //La lista posee algo
            str.str(string());
            cout << "Especifique el id de la imagen a mostrar" << endl;
            cin >> decision;
            if(regex_match(decision,r)){
                int ID;
                istringstream iss (decision);
                iss >> ID;
                if (!listaImagenes->Existe(ID)){
                    cout << "La imagen " << ID <<  " no existe" << endl;
                    continue;
                }
                //La imagen sí existe;
                string dot_txt = listaImagenes->ImagenDot(ID);
                EscribirArchivo("EM_Imagen"+to_string(ID),dot_txt);
                Graphviz("EM_Imagen"+to_string(ID));
            } else {
                cout << "\"" << decision << "\" no es una número entero positivo"  << endl << endl;
            }
        } else if (decision == "6"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El arbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee alo
            try{
                //Recupera el dot del arbol 
                EscribirArchivo("EM_ArbolAVL", arbolUsuarios->Dot());
                Graphviz("EM_ArbolAVL");
            } catch (exception &e){
                cout << "Ocurrió un error al intentar graficar el árbol de Usuarios " << endl << e.what() << endl;
            }
        } else if (decision == "7"){
            if(listaImagenes->EsVacia()){
                cout << endl << "La lista de imágenes está vacía" << endl;
                continue;
            }
            //La lista posee algo
            listaImagenes->Top5();
        } else if (decision == "8"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            arbolCapas->ListarHojas();
        } else if (decision == "9"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            cout << "La profundidad del árbol de capas es de " << arbolCapas->Profundidad() << endl;
        } else if (decision == "10"){
            Matriz *ref = new Matriz();
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            string dot = arbolCapas->RenderizaPostorden();
            //Renderiza la imagen
            EscribirArchivo("EM_CapasPO", dot);
            Graphviz("EM_CapasPO");
        } else if (decision == "11"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            arbolCapas->Preorden();
        } else if (decision == "12"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            arbolCapas->Inorden();
        } else if (decision == "13"){
            if(arbolCapas->EsVacia()){
                cout << endl << "El árbol de capas está vacío" << endl;
                continue;
            }
            //El árbol posee algo
            arbolCapas->Postorden();
        } else if (decision == "14"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El árbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            arbolUsuarios->Top();
        } else if (decision == "15"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El árbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            string a = arbolUsuarios->DotEspejo();
            EscribirArchivo("EM_ArbolAVLE",a);
            Graphviz("EM_ArbolAVLE");
        } else if (decision == "16"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El árbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            arbolUsuarios->Preorden();
        } else if (decision == "17"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El árbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            arbolUsuarios->Inorden();
        } else if (decision == "18"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El árbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            arbolUsuarios->Postorden();
        } else if (decision == "19"){
            if(arbolUsuarios->EsVacio()){
                cout << endl << "El árbol de usuarios está vacío" << endl;
                continue;
            }
            //El arbol posee algo
            arbolUsuarios->Niveles();
        } else if (decision == "20"){
            return;
        } else {
            cout << "\"" << decision << "\" no es una opción valida"  << endl << endl;
        }
    } while (true);
}
/**
 * Lee una archivo de capas
 * @param url
 * @return 
 */
bool LeerCapa(string const &url){
    //Almacea el archivo de entrada
    ifstream archivoEntrada;
    //Alojará una línea leída del archivo
    string linea;
    string color = "";
    int lineaArchivo = 0;
    //Automata a pila
    Pila<int> *pila = new Pila<int>();
    Capa cap = Capa();
    //Abre el archivo
    archivoEntrada.open(url);
    //Verifica  que exista el archivo
    if(!archivoEntrada){
        cout << "No se pudo abrir el archivo " << url << endl << "¿Estará mal escrito?" << endl;
        return 0;
    }
    //Procede a leer el archivo
    while(getline(archivoEntrada,linea)){
        for(int i = 0 ; i < linea.length() ; i++){
            if(!pila->EsVacio()){
                //La pila no está vacía y llego a un } 
                if (linea.at(i) == '}'){
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return 0;
                }
                //Comienza a leer alguna cadena, [#A-Za-z] , 0, -1
                if ( (linea.at(i) == '#' ||  (linea.at(i) >= 'a' && linea.at(i) <= 'z') || (linea.at(i) >= 'A' && linea.at(i) <= 'Z')) && pila->Ver() == 0){
                    color += linea.at(i);
                    pila->Apilar(pila->Desapilar()-1);
                    continue;
                }
                //Continua leyendo alguna cadena, [A-Za-z0-9], -1, E;
                if ( ((linea.at(i) >= 'a' && linea.at(i) <= 'z') || (linea.at(i) >= 'A' && linea.at(i) <= 'Z') || (linea.at(i) >= '0' && linea.at(i) <= '9')) && pila->Ver() == -1){
                    color += linea.at(i);
                    continue;
                }
                //{ ,(conteo de pila == 1), Zo
                if(linea.at(i) == '{' && pila->Largo() == 1){
                    cap.id = pila->Desapilar();
                    cap.Capa_ = new Matriz();
                    continue;
                }
                // "," , ( 1 <= conteo de pila <= 2 ) , 0
                if (linea.at(i) == ',' && pila->Largo() >= 1 && pila->Largo() <= 2){
                    pila->Apilar(0);
                    continue;
                }
                //Concatena numeros
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(pila->Desapilar()*10 + (linea.at(i) - '0') );
                    continue;
                }
                // ";" , -1 , Zo;
                if (linea.at(i) == ';' && pila->Largo() == 3 && pila->Desapilar() == -1){
                    cap.Capa_->AgregarEn(pila->Desapilar(), pila->Desapilar(), color);
                    color = "";
                    continue;
                } else if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) {
                    //Espacio, saltos de linea, tabulaciones
                    continue;
                } else {
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return 0;
                }
            } else {
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(linea.at(i) - '0');
                    continue;
                }
                if (linea.at(i) == '}'){
                    arbolCapas->Agregar(cap);
                    cap = Capa();
                    continue;
                }
            }
        }
        lineaArchivo++;
    }
    return 1;
}
/**
 * Lee un archivo de imagenes
 * @param url
 * @return 
 */
bool LeerImagen(string const &url){
    //Almacena el archivo de entrada
    ifstream archivoEntrada;
    //Alojará una línea leída del archivo
    string linea = "";
    int lineaArchivo = 0;
    //Automat a pila
    Pila<int> *pila = new Pila<int>();
    Imagen img;
    NodoB<Capa> *temp;
    //Abre el archivo
    archivoEntrada.open(url);
    //Verifica que exista el archivo
    if(!archivoEntrada){
        cout << "No se pudo abrir el archivo " << url << endl << "¿Estará mal escrito?" << endl;
        return 0;
    }
    //Procede a leer el archivo y guradar datos
    while(getline(archivoEntrada,linea)){
        for(int i = 0 ;  i < linea.length() ; i++){
            if(!pila->EsVacio()){
                // } , 
                if (linea.at(i) == '}'){
                    do{
                        //Procede a buscar el id en el arbolB
                        temp = arbolCapas->Buscar(pila->Ver());
                        if(!temp){
                            cout << "La capa " << pila->Desapilar() << " no existe en memoria. Línea " << lineaArchivo << endl;
                            continue;
                        }
                        //Existe el nodo, procede a guardar el apuntador 
                        img.Capas()->AgregarAlInicio(temp->DatoPtr());
                        //Despila el nodo
                        pila->Desapilar();
                    }while(!pila->EsVacio());
                    listaImagenes->Agregar(img);
                    continue;
                }
                //{ ,(conteo de pila == 1), 0
                if(linea.at(i) == '{' && pila->Largo() == 1){
                    img = Imagen(pila->Desapilar());
                    continue;
                }
                // "," , ( largo >= 1) , 0
                if (linea.at(i) == ',' && pila->Largo() >= 1){
                    pila->Apilar(0);
                    continue;
                }
                //Concatena numeros
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(pila->Desapilar()*10 + (linea.at(i) - '0') );
                    continue;
                }
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) {
                    //Espacio, saltos de linea, tabulaciones
                    continue;
                }
            } else {
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(linea.at(i) - '0');
                    continue;
                }
                if (linea.at(i) == '{'){
                    //La pila está vacía y encontró un {
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return 0;
                }
            }
        }
        lineaArchivo++;
    }
    return 1;
}
/**
 * Lee un archivo de usuarios
 * @param url
 * @return 
 */
bool LeerUsuario(string const &url){
    //Almacena el archivo de entrada
    ifstream archivoEntrada;
    //Alojará una línea leída del archivo
    string linea ="";
    int lineaArchivo = 0;
    string nombreUsuario = "";
    //ListaDobleCircular *listad;
    //Automata a pila
    Pila<int> *pila = new Pila<int>();
    //Abre el archivo
    archivoEntrada.open(url);
    //Verifica que exista el archivo
    if (!archivoEntrada){
        cout << "No se pudo abrir el archivo " << url << endl << "¿Estará mal escrito?" << endl;
        return 0;
    }
    //Procede a leer el archivo y guardar datos
    while(getline(archivoEntrada, linea)){
        for(int i = 0 ; i < linea.length() ; i++){
            if(!pila->EsVacio()){
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(pila->Desapilar()*10 + (linea.at(i) - '0') );
                    continue;
                }
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if (linea.at(i) == ','){
                    pila->Apilar(0);
                    continue;
                }
                if (linea.at(i) == ';' && nombreUsuario.length() > 0){
                    ListaDoble *lista = new ListaDoble();
                    //Fin de la línea, se procede a leer el contenido de la pila y meterlo a la lista del usuario
                    while(!pila->EsVacio()){
                        //Busca en la lista de imagenes el id
                        if (listaImagenes->Existe(pila->Ver()))
                            lista->AgregarAlFinal(pila->Desapilar());
                        else 
                            cout << "La imagen " << pila->Desapilar() << " no existe. No se puede agregar a " << nombreUsuario << ". Linea " << lineaArchivo << endl;
                    }
                    Usuario user(nombreUsuario,lista);
                    //Agrega el usuario al arbol
                    arbolUsuarios->Agregar(user);
                    nombreUsuario = "";
                    continue;
                }
            } else {
                //Continua leyendo alguna cadena, [A-Za-z0-9], -1, E;
                if ( ((linea.at(i) >= 'a' && linea.at(i) <= 'z') || (linea.at(i) >= 'A' && linea.at(i) <= 'Z') || (linea.at(i) >= '0' && linea.at(i) <= '9'))){
                    nombreUsuario += linea.at(i);
                    continue;
                }
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if (linea.at(i) == ':'){
                    pila->Apilar(0);
                    continue;
                }
                if (linea.at(i) == ';' && nombreUsuario.length() > 0 && pila->Ver() == 0 ){
                    ListaDoble *lista = new ListaDoble();
                    Usuario user(nombreUsuario,lista);
                    arbolUsuarios->Agregar(user);
                    nombreUsuario = "";
                    continue;
                }
            }
        }
        lineaArchivo++;
    }
        
}
/**
 * Escribe un nuevo archivo 
 * @param nombre
 * @param contenido
 */
void EscribirArchivo(string const &nombre, string const &contenido){
    ofstream archivo;
    archivo.open(nombre);
    archivo << contenido;
    archivo.close();
}
/**
 * Ejecuta una orden graphviz y muestra la imagen
 * @param nombre
 */
void Graphviz(string const &nombre){
    string cmd = "dot -Tpng "  + nombre + " -o " + nombre + ".png";
    string cmd_d = "eog " + nombre + ".png";
    system(cmd.c_str());
    system(cmd_d.c_str());
}
