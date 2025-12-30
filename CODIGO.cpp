//Busqueda binaria para Vocabulario de palabras
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Concepto{
    string termino;
    string definicion;
};
int n        = 240;//negro
int r         = 244;//r
int a    = 246;//a
int ac= 254;//ac
int v        = 242;//v
int vc  = 250;//vc
int b       = 255;//b


const int MAX=100;//tamaño máximo del vocabulario
// Función auxiliar con la ANIMACIÓN y LÓGICA RECURSIVA

//FUNCIONES PRINCIPALES
void ingresar(Concepto*,int&);
void ordenar(Concepto*, int);
void mostrar(Concepto*, int);

//BUSQUEDAS (todas void)
void busqueda_secuencial_iterativa(Concepto*, int);
void busqueda_secuencial_recursiva(Concepto*, int);
void busqueda_binaria_iterativa(Concepto*, int);
void busqueda_binaria_recursiva(Concepto*, int);

//FUNCIONES SECUNDARIAS
void interfaz(string[],string[],const int,int);
//se agrego parametros para los submenus de busqueda 
void sub_menu_busqueda(Concepto*,int);
void sub_sub_menu_implementacion(Concepto*, int, void(*)(Concepto*, int), void(*)(Concepto*, int) );
//tarea para el Ander: void* ... void*().... void (*)() puntero a funcion
void diseno_iterativa(Concepto*,int,int);
void diseno_iterativa_encontrado();
void diseno_iterativa_no_encontrado();
void limpiar_cuadro();

//FUNCIONES AUXILIARES
void gotoxy(int , int );
void cambio_color(int );
void ocultarCursor();
void cambio_color(int x){
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
} 
//CARGA DE CHARMANDER
void cuadradopintad (int, int);
void gotoxy(int, int);
void charm(int, int);
void charm2(int, int);
void colores();
void Piso(int x, int y);
string mayusculas(string);//pasar a mayusculas
void borrar_charm(int x, int y){
    cambio_color(0);

    for(int i = 2; i <= 19; i++){
        gotoxy(x + 10, y + i);
        for(int j = 0; j < 36; j++){
            cout << " ";
        }
    }
}
void auxiliar_binaria_visual(Concepto* p, int inicio, int fin, string palabrita_mayus) {
    
    // CASO BASE: No encontrado
    if (inicio > fin) {
        diseno_iterativa_no_encontrado();
        return; 
    }

    int medio = (inicio + fin) / 2;

    // 1. PINTAR EL CUADRO (Igual que en la iterativa)
    diseno_iterativa(p, inicio, fin);
    
    // 2. ANIMACIÓN DE "COMPARANDO..."
    gotoxy(45,7); cout << "Comparando.";
    Sleep(250); cout << ".";
    Sleep(250); cout << ".";
    Sleep(250);

    string termino_mayus = mayusculas(p[medio].termino);

    // 3. COMPARACIONES CON ANIMACIÓN (Copiado exacto de tu iterativa)
    
    if (termino_mayus == palabrita_mayus) { 
        // CASO ENCONTRADO
        diseno_iterativa_encontrado();

        gotoxy(48,7); cout << p[medio].termino;
        cambio_color(9);
        gotoxy(45,11); cout << p[medio].definicion;
        cambio_color(11);
        _getch();
        return; // Fin de la recursividad
    }
    else if (termino_mayus < palabrita_mayus) {
        // LA PALABRA ES MAYOR (Buscar en la mitad derecha)
        
        // --- Animación visual (Copiada de tu código) ---
        gotoxy(43,7); limpiar_cuadro();
        gotoxy(46,7); cout << p[medio].termino;

        cambio_color(2);
        gotoxy(44,10); cout << "La palabra buscada";
        gotoxy(47,11); cout << "Es mayor";
        cambio_color(7);
        Sleep(1000);

        gotoxy(16,7); limpiar_cuadro();

        gotoxy(43,7); limpiar_cuadro();
        for(int i=0; i<27; i++){
            gotoxy(46-i,7); cout << p[medio].termino; 
            Sleep(40);
            gotoxy(43-i,7); limpiar_cuadro();
        }
        // ----------------------------------------------

        // LLAMADA RECURSIVA (inicio = medio + 1)
        auxiliar_binaria_visual(p, medio + 1, fin, palabrita_mayus);
    }
    else {
        // LA PALABRA ES MENOR (Buscar en la mitad izquierda)

        // --- Animación visual (Copiada de tu código) ---
        gotoxy(43,7); limpiar_cuadro();
        gotoxy(46,7); cout << p[medio].termino;

        cambio_color(3);
        gotoxy(44,10); cout << "La palabra buscada";
        gotoxy(47,11); cout << "Es menor";
        cambio_color(7);
        Sleep(1000);

        gotoxy(70,7); limpiar_cuadro();

        gotoxy(43,7); limpiar_cuadro();
        for(int i=0; i<27; i++){
            gotoxy(46+i,7); cout << p[medio].termino;
            Sleep(40);
            gotoxy(43+i,7); limpiar_cuadro();
        }
        // ----------------------------------------------

        // LLAMADA RECURSIVA (fin = medio - 1)
        auxiliar_binaria_visual(p, inicio, medio - 1, palabrita_mayus);
    }
}
void menu(){
SetConsoleOutputCP(CP_UTF8);
    ocultarCursor();
    
    Concepto Palabra[MAX];
    int contador=0;

    const int total=4;

    string opcionesMayus[total] = {"INGRESAR", "BUSCAR", "MOSTRAR","SALIR"};
    string opcionesMin[total] = {"Ingresar", "Buscar", "Mostrar","Salir"};

    int opcionActual=0;
    string palabrita;

    // Dibujar el menú por primera vez
    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224){
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13){//enter
            system("cls");
            switch(opcionActual){
                case 0:
                    ingresar(Palabra,contador);
                    break;
                case 1:
                    sub_menu_busqueda(Palabra, contador);
                    break;
                case 2:
                    ordenar(Palabra,contador);
                    mostrar(Palabra,contador);
                    break;
                case 3:
                    cout<<"\n\n\n    Saliendo...";
                    Sleep(1000);
                default:
                    break;
            }
            
            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);

        }
    }
}

//PROGRAMA PRINCIPAL
void activarUTF() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void activarOEM() {
    SetConsoleOutputCP(437); // OEM USA
    SetConsoleCP(437);
}


int main(){
    activarUTF();
    menu();
    return 0;

}

//FUNCIONES PRINCIPALES

void ingresar(Concepto* p, int &contador){
    string verifica, verifica_mayus,palabrita_mayus;//verifica si es duplicado
    bool bandera;

    do{ 
        bandera=true;
        cout<<"\n\n\n\n    ¡Hola!, soy tu vocabulario personal.\n";
        cout<<"    Que palabra deseas agregar?: ";
        getline(cin, verifica);
        
        verifica_mayus=mayusculas(verifica);

        for(int i=0;i<contador;i++){
            palabrita_mayus=mayusculas(p[i].termino);
            if(palabrita_mayus==verifica_mayus){
                cout<<"\n    No se aceptan duplicados";
                bandera=false;
                _getch();
                system("cls");
                break;
            }
        }

    }while(bandera==false);

    p[contador].termino=verifica;
    cout<<"\n\n    Cual es su definición?: \n    ";
    getline(cin, p[contador].definicion);

    contador++;
    cout<<"\n    Palabra agregada exitósamente.\n";
    _getch();
}

void ordenar(Concepto* p, int contador){//ordenamiento por insercion
    for(int i=0;i<contador;i++){
        Concepto temp=p[i];//crea una variable de tipo concepto temporal la cual guarda el valor de p[i]
        int pos=i;

        while(pos>0 && mayusculas(p[pos-1].termino)>mayusculas(temp.termino)){//compara en mayusculas
            p[pos]=p[pos-1];
            pos--;
        }
        
        p[pos]=temp;
    }
}

void mostrar(Concepto* p, int contador){
    ordenar(p,contador);

    if(contador==0){
        cout<<"\n\n\n    ¡Ups! No tienes palabras registradas en el vocabulario\n";
        cout<<"    Encuentra palabras interesantes primero.\n";
        _getch();
        return;
    }

    cout<<"\n\n\n    Tus palabras son:\n\n";
    for(int i=0;i<contador;i++){
        cout<<"    "<<i+1<<". "<<p[i].termino<<": "<<p[i].definicion<<"\n";
    }
    _getch();
}

//FUNCIONES SECUNDARIAS

void interfaz(string opcionesMayus[], string opcionesMin[], const int total, int seleccionada) {
    gotoxy(0,0);//mover el cursor
    string texto;
    int x=30,y=6;
    int espacio_vertical=5;
    
    cout << "\n\n\n";
    cambio_color(11);
    cout << "                \n\n\n\n    ";
    cambio_color(7);
    
    for(int i=0;i<total;i++){

        if(i==seleccionada){
            cambio_color(5);
            texto= *(opcionesMayus+i);//opcionesMayus[i]
            gotoxy(x,y);cout<<  "╔═════════════════╗";
            gotoxy(x,y+1);cout<<"║  "<< texto;
            gotoxy(x+18,y+1);cout<<"║";
            gotoxy(x,y+2);cout<<"╚═════════════════╝";
            cambio_color(7);
        }else{
            texto= *(opcionesMin+i);
            gotoxy(x,y);cout<<  "╔═════════════════╗";
            gotoxy(x,y+1);cout<<"║  "<< texto;
            gotoxy(x+18,y+1);cout<<"║";
            gotoxy(x,y+2);cout<<"╚═════════════════╝";

        }
        y+=espacio_vertical;
    }
}

void sub_menu_busqueda(Concepto* p, int contador){
    const int total=3;

    string opcionesMayus[total] = {"SECUENCIAL", "BINARIA", "VOLVER"};
    string opcionesMin[total] = {"Secuencial", "Binaria", "Volver"};

    int opcionActual=0;

    // Dibujar el menú por primera vez
    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13){//enter
            system("cls");
            switch(opcionActual){
                case 0://busqueda secuencial
                    sub_sub_menu_implementacion(p, contador, busqueda_secuencial_iterativa, busqueda_secuencial_recursiva);
                    //tarea: pasar las funciones de busqueda secuencial iterativa y recursiva(agregado para los que le toco secuencial)
                    break;
                case 1://busqueda binaria
                    sub_sub_menu_implementacion(p, contador, busqueda_binaria_iterativa, busqueda_binaria_recursiva);
                    //tarea: pasar las funciones de busqueda binaria recursiva
                    break;
                default:
                    break;
            }

            if(opcionActual==2) break;

            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);

        }
    }
}

void sub_sub_menu_implementacion(Concepto* p, int contador, void (*opc1)(Concepto*, int), void (*opc2)(Concepto*, int)){//equivalen a (void* opc1(), void* opc2())
    const int total=3;

    string opcionesMayus[total] = {"ITERATIVA", "RECURSIVA", "VOLVER"};
    string opcionesMin[total] = {"Iterativa", "Recursiva", "Volver"};

    int opcionActual = 0;
    string palabrita;

    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13) {
            system("cls");
            switch(opcionActual){
                case 0:
                    opc1(p, contador); //busqueda secuencial o binario iterativa
                    break;
                case 1:
                    opc2(p, contador); //busqueda secuencial o binaria recursiva
                    break;
                default:
                    break;
            }
            if(opcionActual==2) break;

            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);

        }
    }
}

void charm(int x, int y){
              cout << "\n";
              cout << "\n\t";//1era linea
              gotoxy(x+16,y+2);
              cuadradopintad(1,n);gotoxy(x+34,y+2);cuadradopintad(5,n);
              cout << "\n\t";//2da linea
              gotoxy(x+14,y+3);
              cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+32,y+3);cuadradopintad(1,n);cuadradopintad(5,r);cuadradopintad(1,n);
              cout << "\n\t";//3era linea
              gotoxy(x+12,y+4);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n); gotoxy(x+30,y+4);cuadradopintad(1,n);cuadradopintad(7,r);cuadradopintad(1,n);
              cout << "\n\t";//4ta linea
              gotoxy(x+12,y+5);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);gotoxy(x+30,y+5);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(3,r);cuadradopintad(1,n);
              cout << "\n\t";//5ta linea
              gotoxy(x+10,y+6);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,ac);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+30,y+6);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(2,n);cuadradopintad(3,r);cuadradopintad(1,n);
              cout << "\n\t";//6ta linea
              gotoxy(x+10,y+7);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(2,ac);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+28,y+7);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(2,n);cuadradopintad(4,r);cuadradopintad(1,n);
              cout << "\n\t";//7tima linea
              gotoxy(x+12,y+8); cuadradopintad(2,n);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+28,y+8);cuadradopintad(1,n);cuadradopintad(9,r);cuadradopintad(1,n);
              cout << "\n\t";//8va linea
              gotoxy(x+14,y+9); cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+28,y+9);cuadradopintad(1,n);cuadradopintad(8,r);cuadradopintad(1,n);
              cout << "\n\t";//9va linea
              gotoxy(x+14,y+10);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);gotoxy(x+26,y+10);cuadradopintad(1,n);cuadradopintad(5,r);cuadradopintad(4,n);
              cout << "\n\t";//10va linea
              gotoxy(x+14,y+11);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);gotoxy(x+24,y+11);cuadradopintad(1,n);cuadradopintad(5,r);cuadradopintad(3,ac);cuadradopintad(2,n); 
              cout <<"\n\t";//11va linea
              gotoxy(x+14,y+12);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(2,r);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(4,ac);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);
              cout <<"\n\t";//12va linea
              gotoxy(x+16,y+13);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(2,r);cuadradopintad(3,n);cuadradopintad(2,r);cuadradopintad(4,ac);cuadradopintad(3,n);
              cout <<"\n\t";//13va linea
              gotoxy(x+18,y+14);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(1,r);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(5,ac);cuadradopintad(1,n);
              cout <<"\n\t";//14va linea
              gotoxy(x+20,y+15);cuadradopintad(2,n);cuadradopintad(4,r);cuadradopintad(1,n);cuadradopintad(3,ac);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);
              cout <<"\n\t";//15va linea
              gotoxy(x+22,y+16);cuadradopintad(1,n);cuadradopintad(4,r);cuadradopintad(1,n);cuadradopintad(2,ac);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);
              cout <<"\n\t";//16va linea
              gotoxy(x+24,y+17);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(4,n);cuadradopintad(2,r);cuadradopintad(1,n);
              cout <<"\n\t";//17va linea
              gotoxy(x+24,y+18);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(1,n);
              cout <<"\n\t";//18va linea
              gotoxy(x+24,y+19);cuadradopintad(2,n);cuadradopintad(1,b);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(3,n);cuadradopintad(1,b);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(1,n);
}
void charm2(int x, int y){
              cout << "\n";
              cout << "\n\t";//1era linea
              gotoxy(x+16,y+2);
              cuadradopintad(1,n);gotoxy(x+34,y+2);cuadradopintad(5,n);
              cout << "\n\t";//2da linea
              gotoxy(x+14,y+3);
              cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+32,y+3);cuadradopintad(1,n);cuadradopintad(5,r);cuadradopintad(1,n);
              cout << "\n\t";//3era linea
              gotoxy(x+12,y+4);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n); gotoxy(x+30,y+4);cuadradopintad(1,n);cuadradopintad(7,r);cuadradopintad(1,n);
              cout << "\n\t";//4ta linea
              gotoxy(x+12,y+5);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);gotoxy(x+30,y+5);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(3,r);cuadradopintad(1,n);
              cout << "\n\t";//5ta linea
              gotoxy(x+10,y+6);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,ac);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+30,y+6);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(2,n);cuadradopintad(3,r);cuadradopintad(1,n);
              cout << "\n\t";//6ta linea
              gotoxy(x+10,y+7);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(2,ac);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+28,y+7);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(2,n);cuadradopintad(4,r);cuadradopintad(1,n);
              cout << "\n\t";//7tima linea
              gotoxy(x+12,y+8); cuadradopintad(2,n);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+28,y+8);cuadradopintad(1,n);cuadradopintad(9,r);cuadradopintad(1,n);
              cout << "\n\t";//8va linea
              gotoxy(x+14,y+9); cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);gotoxy(x+28,y+9);cuadradopintad(1,n);cuadradopintad(8,r);cuadradopintad(1,n);
              cout << "\n\t";//9va linea
              gotoxy(x+14,y+10);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);gotoxy(x+26,y+10);cuadradopintad(1,n);cuadradopintad(5,r);cuadradopintad(4,n);
              cout <<"\n\t";//10va linea
              gotoxy(x+14,y+11);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(1,n);gotoxy(x+24,y+11);cuadradopintad(1,n);cuadradopintad(5,r);cuadradopintad(3,ac);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);
              cout <<"\n\t";//11va linea
              gotoxy(x+14,y+12);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(2,r);cuadradopintad(2,n);cuadradopintad(2,r);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(4,ac);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);
              cout <<"\n\t";//12va linea
              gotoxy(x+16,y+13);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(2,r);cuadradopintad(3,n);cuadradopintad(2,r);cuadradopintad(4,ac);cuadradopintad(2,n);
              cout <<"\n\t";//13va linea
              gotoxy(x+18,y+14);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(1,r);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(5,ac);cuadradopintad(1,n);
              cout <<"\n\t";//14va linea
              gotoxy(x+20,y+15);cuadradopintad(1,n);cuadradopintad(1,ac);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(1,n);cuadradopintad(3,ac);cuadradopintad(1,n);cuadradopintad(1,r);cuadradopintad(1,n);
              cout <<"\n\t";//15va linea
              gotoxy(x+22,y+16);cuadradopintad(2,n);cuadradopintad(3,r);cuadradopintad(1,n);cuadradopintad(2,ac);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(2,n);
              cout <<"\n\t";//16va linea
              gotoxy(x+20,y+17);cuadradopintad(1,n);cuadradopintad(4,r);cuadradopintad(4,n);cuadradopintad(4,r);cuadradopintad(1,b);cuadradopintad(1,n);
              cout <<"\n\t";//17va linea
              gotoxy(x+20,y+18);cuadradopintad(1,n);cuadradopintad(3,r);cuadradopintad(1,n);gotoxy(x+38,y+18);cuadradopintad(1,n);cuadradopintad(2,r);cuadradopintad(2,n);
              cout <<"\n\t";//18va linea
              gotoxy(x+22,y+19);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(1,n);cuadradopintad(1,b);cuadradopintad(1,n);gotoxy(x+40,y+19);cuadradopintad(2,n);
}
void Piso(int x, int y){
    gotoxy(x, y);
    cuadradopintad(70, n);

    gotoxy(x, y+1);
    cuadradopintad(70, v);

    gotoxy(x, y+2);
    cuadradopintad(70, v);

    gotoxy(x, y+3);
    cuadradopintad(70, v);
}

void cuadradopintad  (int x, int c){//cuadrados pintados
              cambio_color(c);
              for(int i=1; i<=x;i++){
                            cout << char (219) << char(219);//el 219 es el caract del cuad pint
              }
            }
void mostrarcharm(){
    activarOEM();
      ocultarCursor();
    cambio_color(0);
    Piso(0, 30);   // ← se dibuja UNA SOLA VEZ

    int x = 10;
    int y = 10;

    for(int i = 0; i < 50; i++){
        charm(x, y);
        Sleep(120);
        borrar_charm(x, y);

        x++;

        charm2(x, y);
        Sleep(120);
        borrar_charm(x, y);
    }
    system("cls");
    activarUTF();
    getch();
}
//BUSQUEDAS

void busqueda_secuencial_iterativa(Concepto* p, int contador){
    cout<<"\n\n\n    Por implementar\n";
    system("pause");
}

void busqueda_secuencial_recursiva(Concepto* p, int contador){
    cout<<"\n\n\n    Por implementar\n";
    system("pause");
}

void busqueda_binaria_recursiva(Concepto* p, int contador){
    // Validación inicial
    if(contador == 0){
        system("cls");
        cout<<"\n\n\n    No hay palabras en el vocabulario.\n";
        cout<<"    Agrega algunas primero.\n";
        _getch();
        return;
    }

    // Configuración inicial (Idéntica a la iterativa)
    system("cls");
    ordenar(p, contador);
    
    string palabrita;
    gotoxy(45,2); cout << "Que palabra buscas?: "; 
    gotoxy(45,3); getline(cin, palabrita);
    mostrarcharm();
    
    string palabrita_mayus = mayusculas(palabrita);

    system("cls");

    // AQUÍ INICIA LA MAGIA RECURSIVA
    // Llamamos a la función auxiliar pasando 0 como inicio y contador-1 como fin
    auxiliar_binaria_visual(p, 0, contador - 1, palabrita_mayus);
    
    // El _getch() final está dentro de la auxiliar en caso de éxito, 
    // o hay que ponerlo aquí si quieres esperar al salir del fallo
    if (contador > 0) _getch(); 

    system("pause");
}

void busqueda_binaria_iterativa(Concepto* p, int contador){
    if(contador==0){//verificar si hay palabras en el vocabulario
        system("cls"); 
        cout<<"\n\n\n    No hay palabras en el vocabulario.\n";
        cout<<"    Agrega algunas primero.\n";
        _getch();
        return;
    }

    system("cls");
    ordenar(p,contador);
    int inicio=0, fin=contador-1, medio;//indices (posiciones del arreglo)
    string palabrita;

    gotoxy(45,2); cout<<"Que palabra buscas?: "; 
    gotoxy(45,3); getline(cin,palabrita);
    
    string palabrita_mayus=mayusculas(palabrita);//convertir palabra ingresada a mayusculas para comparar

    system("cls");
    
    while(inicio<=fin){
        medio=(inicio+fin)/2;//base del calulo
        
        diseno_iterativa(p,inicio,fin);
        gotoxy(45,7);cout<<"Comparando.";
            Sleep(250);cout<<".";
            Sleep(250);cout<<".";
            Sleep(250);

        string termino_mayus=mayusculas(p[medio].termino);//convertir palabra del arreglo a mayusculas para comparar

        if(termino_mayus==palabrita_mayus){//compara las dos palabras en mayusculas

            diseno_iterativa_encontrado();

            gotoxy(48,7);cout<<p[medio].termino;//se mantiene el formato original
            cambio_color(9);
            gotoxy(45,11);cout<<p[medio].definicion;
            cambio_color(11);
            _getch();
            return;
        }
        else if(termino_mayus<palabrita_mayus){
            
            gotoxy(43,7);limpiar_cuadro();
            gotoxy(46,7);cout<<p[medio].termino;


            cambio_color(2);
            gotoxy(44,10); cout<<"La palabra buscada";
            gotoxy(47,11); cout<<"Es mayor";
            cambio_color(7);
            Sleep(1000);

            gotoxy(16,7);limpiar_cuadro();

            gotoxy(43,7);limpiar_cuadro();
            for(int i=0;i<27;i++){
                gotoxy(46-i,7);cout<<p[medio].termino; 
                Sleep(40);
                gotoxy(43-i,7);limpiar_cuadro();
            }

            inicio=medio+1;//buscar en la mitad superior a la actual
            
        }
        else{

            gotoxy(43,7); limpiar_cuadro();
            gotoxy(46,7);cout<<p[medio].termino;

            cambio_color(3);
            gotoxy(44,10); cout<<"La palabra buscada";
            gotoxy(47,11); cout<<"Es menor";
            cambio_color(7);
            Sleep(1000);

            gotoxy(70,7);limpiar_cuadro();

            gotoxy(43,7);limpiar_cuadro();
            for(int i=0;i<27;i++){
                gotoxy(46+i,7);cout<<p[medio].termino;
                Sleep(40);
                gotoxy(43+i,7);limpiar_cuadro();
            }
 
            fin=medio-1;//buscar en la mitad inferior a la actual
        }
    }   
    diseno_iterativa_no_encontrado();

    _getch();
}

void limpiar_cuadro(){
    cout<<"                   ";
}

void diseno_iterativa(Concepto* p,int inicio, int fin){
    int x=15, y=5;
    //izquierda
    
    gotoxy(x,y);  cout<<"       INICIO";
    gotoxy(x,y+1);cout<<"┌────────────────────┐";
    gotoxy(x,y+2);cout<<"│     "<<p[inicio].termino;
    gotoxy(x+21,y+2);cout<<"│";
    gotoxy(x,y+3);cout<<"└────────────────────┘";

    //centro
    gotoxy(x+27,y);  cout<<"        ";
    gotoxy(x+27,y+1);   cout<<"╔════════════════════╗";
    gotoxy(x+27,y+2);   cout<<"║     ";
    gotoxy(x+21+27,y+2);cout<<"║";
    gotoxy(x+27,y+3);cout<<"╚════════════════════╝";
      
    //derecha
    gotoxy(x+(27*2),y);  cout<<"         FIN";
    gotoxy(x+(27*2),y+1);cout<<"┌────────────────────┐";
    gotoxy(x+(27*2),y+2);cout<<"│     "<<p[fin].termino;
    gotoxy(x+21+(27*2),y+2);cout<<"│";
    gotoxy(x+(27*2),y+3);cout<<"└────────────────────┘";
}

void diseno_iterativa_encontrado(){
    system("cls");
    int x=15, y=5;
    
    cambio_color(6);
    gotoxy(x+27,y);  cout<<"      EUREKA!!!";
    gotoxy(x+27,y+1);   cout<<"╔════════════════════╗";
    gotoxy(x+27,y+2);   cout<<"║     ";
    gotoxy(x+21+27,y+2);cout<<"║";
    gotoxy(x+27,y+3);cout<<"╚════════════════════╝";
    cambio_color(11);
    gotoxy(x+27,y+5);cout<<"     DEFINICIÓN:";
}

void diseno_iterativa_no_encontrado(){
    system("cls");
    int x=15, y=5;
    
    cambio_color(14);
    gotoxy(x+27,y);  cout<<"     ¡OH NO!";
    gotoxy(x+27,y+1);   cout<<"╔════════════════════╗";
    gotoxy(x+27,y+2);   cout<<"║    NO ENCONTRADO";
    gotoxy(x+21+27,y+2);cout<<"║";
    gotoxy(x+27,y+3);cout<<"╚════════════════════╝";
    cambio_color(12);
}

//FUNCIONES AUXILIARES
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void ocultarCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; 
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

string mayusculas(string cadena){
    for(int i=0;cadena[i]!='\0';i++){
        if(cadena[i]>='a' && cadena[i]<='z'){
            cadena[i]=cadena[i]-32;
        }
    }
    return cadena;
}
