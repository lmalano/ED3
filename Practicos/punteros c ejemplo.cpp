#include<iostream>


using namespace std;

int main()
{

int *dirnum;
int distancia=20;

dirnum=&distancia;

cout<<"la direccion almacenada en dirnum es "<<dirnum<<endl;

cout<<"el valor a q apunta dirnum es "<<*dirnum<<endl;
dirnum++;

cout<<"la direccion siguiente de dirnum es "<<dirnum<<endl;
return 0;

}



