/*
Sebastian Gonzalo Vives Faus - A01025211
  Fontanero Diligente
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>//Para usar en la variable de Random y generar un seed aleatorio.

using namespace std;

struct Elementos{
  int numero;
  double tiempo; //Tiempo de reparacion
};

void randomTime(Elementos X[], int n, double MinT, double MaxT){
  srand (time(NULL));//Semilla aleatorio
  int i;
  for(i=0;i<n; i++){
    X[i].numero = i+1;
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = MaxT - MinT;
    double r = random*diff;
    X[i].tiempo = MinT + r;

    cout<<"El trabajo "<<X[i].numero<<" le va a tomar a el plomero "<<X[i].tiempo<<" minutos."<<endl;
  }
}//end randomTime

//BUBBLE SORT!
// Code obtained from: https://www.geeksforgeeks.org/bubble-sort/
void swap(int *x, int *y){
    int temporal = *x;
    *x = *y;
    *y = temporal;
}

void BubbleSort(Elementos arr[], int size){
    for (int i = 0; i < size-1; i++){
     for (int j = 0; j < size-i-1; j++){
        if (arr[j].tiempo > arr[j+1].tiempo){
            swap(arr[j].tiempo, arr[j+1].tiempo);
            swap(arr[j].numero, arr[j+1].numero);
        }//if1
     }//for2
    }//for1
}

void print(Elementos X[], int n){
  for(int i = 0; i< n; i++){
    cout<<"Trabajo "<<X[i].numero<<" con tiempo "<<X[i].tiempo<<endl;
  }
}

double Fontanero(Elementos X[], int n){
  double XY;
  for(int i = 0; i<n-1; i++){
    XY = XY + (n-X[i].numero+1)*(X[i].tiempo - X[i+1].tiempo) + (n-X[i+1].numero+1)*(X[i+1].tiempo - X[i].tiempo);
    //XY = XY + (X[i+1].numero - X[i].numero)*(X[i].tiempo - X[i+1].tiempo);
  }
  return XY;
}

int main(){
  //Declaracion de variables
  int n,i;
  double MinT, MaxT;

  cout<<"Cuantos trabajos tiene el plomero? :"<<endl;
  cin>>n;

  cout<<"Cual es el rango de tiempo que tiene de cada trabajo? (Min, Max):"<<endl;
  cin>>MinT>>MaxT;

  Elementos X[n];
  cout<<"X[i]"<<endl;
  randomTime(X, n, MinT, MaxT);

  //Ordenar los elementos en un nuevo arreglo Y.
  Elementos Y[n];
  for(int i = 0; i<n; i++){
    Y[i] = X[i];
  }

  BubbleSort(Y, n);
  cout<<"Y[i]"<<endl;
  print(Y, n);

  cout<<"E[X] - E[Y]: "<<Fontanero(X,n)<<endl;
  //cout<<"Tiempo de Y (Tiempo Ordenado): "<<Fontanero(Y,n)<<endl;

  return 0;
}
