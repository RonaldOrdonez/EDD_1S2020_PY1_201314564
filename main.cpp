#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;



int main()
{
    string name1="amanda"; // NOMBRE MUEVO A COMPARAR
    string name2="ana";  //NOMBRE YA INGRESADO AL ARBOL CON EL QUE SE COMPARA 
    
    if(name1.compare(name2)==0)   
    {
        cout<<"NOMBRES IGUALES \n";
    }
    else if(name1.compare(name2)>0) // es hijo derecho
    {
        cout<<name1+" VA DESPUES DE "+name2+"\n";
    }
    else
    {
        cout<<name1+" VA ANTES DE "+name2+"\n";  // es hijo izquierdo      
    }   

    return 0;
}