/*
Sebastian Gonzalo Vives Faus - A01025211
*/

#include <iostream>
#include <stdlib.h>
#include <list> //STL Library
#include <time.h>//Para usar en la variable de Random y generar un seed aleatorio.

using namespace std;

//Estructura de elementos, donde se registra el peso y beneficio de cada uno.
struct Elemento{ //Objeto
  float peso;
  int beneficio;
};

void Valorar(Elemento arr[], int n, int MinP, int MaxP, int MinB, int MaxB){

  srand (time(NULL));//Semilla aleatorio
  for(int i = 0; i<n; i++){
    //Random float
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = MaxP - MinP;
    float r = random * diff;
    arr[i].peso = MinP + r;
    arr[i].beneficio = rand()% MaxB - MinB;

    //Imprimir elementos
    cout<<"Elemento "<<i<<" : Peso = "<<arr[i].peso<<" Beneficio = "<<arr[i].beneficio<<endl;
  }//for

}

int max(Elemento e[], int i, int j){//Existe algun otro elemento que si quepa pero su beneficio sea mayor al del elemento actual?
  if(e[j].beneficio>e[i].beneficio){
    return 1;
    cout<<e[j].beneficio<<" es mayor que "<<e[i].beneficio<<endl;
  }
  else{
    return 0;
    cout<<e[j].beneficio<<" NO es mayor que "<<e[i].beneficio<<endl;
  }
}

void Mochila(Elemento e[], int n, int MaxElements, float pesoM, float sol[], Elemento Mochila[], float MaxP, float MinP){
  float pesoActual;
  int i, j, counter;
  bool metialgo, mayor;


  //Llenar Elementos de la mochila con 0,0
  for(i=1; i< MaxElements; i++){
    sol[i] = 0.0;
    Mochila[i].peso = 0.0;
  }
  pesoActual = 0.0;
  i = 0;
  counter = 0;




  while((pesoActual<pesoM) && (i<=n)){
    if(counter<MaxElements){
    metialgo = false;
    if((e[i].peso + pesoActual) <= pesoM){//Si el peso del elemento y el peso actual de la mochila son menores al de la capacidad

      //while(metialgo){

        for(j = 0; j<=n; j++){
          if(((e[i].peso + pesoActual) <= pesoM) && (max(e, i, j) == 1)){//Existe algun otro elemento que si quepa pero su beneficio sea mayor al del elemento actual?

            //Si no, el otro elemento cabe en la mochila? Si si, mete el otro e ignora este. Si no, solo mete este.
              if(e[j].peso + pesoActual <= pesoM && metialgo == false && e[j].peso>=MinP && e[j].peso<=MaxP){
              sol[counter]= 1.0;
              Mochila[counter].peso = e[j].peso;
              Mochila[counter].beneficio = e[j].beneficio;
              counter++;
              pesoActual = pesoActual + e[j].peso;
              cout<<"El elemento con mayor beneficio fue insertado. ["<<e[j].peso<<"]"<<endl;
              e[j].peso = pesoM+10;
              metialgo = true;
            //  i++;
              cout<<"Peso actual "<<pesoActual<<endl;
            }//end if3
          }//end if
        }//end for

            if(metialgo == false && e[i].peso>=MinP && e[i].peso<=MaxP){
              sol[counter]=1.0;
              Mochila[counter].peso = e[i].peso;
              Mochila[counter].beneficio = e[i].beneficio;
              counter++;
              pesoActual = pesoActual + e[i].peso;
              cout<<"Elemento inicial fue insertado["<<e[i].peso<<"]"<<endl;
              e[i].peso = pesoM+10;
              metialgo = true;
              //i++;
              cout<<"Peso actual "<<pesoActual<<endl;
            }

      //}//end while2

    }
    else{
      //sol[i]=(pesoM - pesoActual)/e[i].peso;
      cout<<"Elemento con peso "<<e[i].peso<<" no cabe en la mochila."<<endl;
      cout<<"Peso actual "<<pesoActual<<endl;
      //i++;
    }
    i++;
  }
    else{
      cout<<"La mochila esta llena con "<<counter<<" elementos!"<<endl;
      i = n+1;
    }
  }//end while

}//first if




int main(){
  //Creacion de Elementos
  int cantidad, cantidadM, MinB=1, MaxB=50, option;
  float MPeso,MinP=1.0, MaxP=10.0;
  cout<<"Insertar cantidad de Elementos: "<<endl;
  cin>>cantidad;

  cout<<"Insertar cantidad de Elementos que caben en la mochila: "<<endl;
  cin>>cantidadM;

  cout<<"Insertar peso maximo de la Mochila: "<<endl;
  cin>>MPeso;

  cout<<"Desea definir un rango para el peso y beneficio de cada elemento? (Default: "<<MinP<<"-"<<MaxP<<"; "<<MinB<<"-"<<MaxB<<") [1/0]"<<endl;
  cin>>option;

  if(option == 1){
    cout<<"Insertar Valores para Peso Minimo, Maximo y Beneficio Minimo, Maximo: "<<endl;
    cin>>MinP >> MaxP >> MinB >> MaxB;
  }
  else{}
  //Crear Lista de Elementos
  Elemento Cosas[cantidad];
  Elemento MochilaDeCosas[cantidadM];
  float M[cantidadM];

  //Metodo para valorar los elementos.
  Valorar(Cosas, cantidad, MinP, MaxP, MinB, MaxB);
  Mochila(Cosas, cantidad, cantidadM, MPeso, M, MochilaDeCosas, MaxP, MinP);

  float EDentro;
  for(int i = 0; i<cantidadM; i++){
    if((MochilaDeCosas[i].peso >= MinP)&&(MochilaDeCosas[i].peso <= MaxP)){
    EDentro = EDentro + 1;
    }
  }

  cout<<"Numero de Elementos maximo que caben en la mochila: "<<EDentro<<" dentro los cuales se encuentran: "<<endl;

  for(int i = 0; i<cantidadM; i++){
    if((MochilaDeCosas[i].peso >= MinP)&&(MochilaDeCosas[i].peso <= MaxP)){
    cout<<"Elemento con peso: "<<MochilaDeCosas[i].peso<<" y beneficio total de "<<MochilaDeCosas[i].beneficio<<endl;
    }
  }

  return 0;
}
