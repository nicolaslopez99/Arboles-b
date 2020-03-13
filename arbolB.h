#include<iostream>
#ifndef ARBOLB_H
#define ARBOLB_H

struct nodo{int *claves;
		nodo **hijos;
		int Nclaves;
		bool hoja;
		};

class arbolB {
			nodo *raiz;
		    int d;
		    int *ar;
			nodo **br;
	public: 
		arbolB(int ord){
			ar=new int[2*ord-1];
			br= new nodo*[2*ord];
					d = ord;
					raiz = crear_nodo(ord);
					raiz->Nclaves = 0; 
					raiz-> hoja = true;
					}
					
		   nodo *crear_nodo(int d);
		   nodo *get_raiz ();
		   
		   int  dividir_nodo(nodo *actual, nodo **hermano);
		   void insertar(int clave);
		   nodo *buscar_nodo(int clave, nodo *Actual, nodo **padre);
		   int InsertarNodoNormal(int clave, nodo *Actual);
		   void InsertarNodoLleno(int clave, nodo *Actual, nodo *padre);
		   nodo *buscar_padre (int clave, nodo *Actual, nodo *padre);
		   bool borrar(int clave);
		   nodo *Unir_nodos(nodo* hizq, nodo*hDer, nodo*padre);
		};



nodo *arbolB::crear_nodo (int d)
			{
			nodo *nuevo;
			nuevo -> claves= ar;
			 nuevo->hijos = br;
			 nuevo->Nclaves=0;
			 nuevo->Nclaves=0;
			 nuevo->hoja=true;
			 return nuevo;
			}


nodo *arbolB::get_raiz ()
			{return raiz;
			}

void arbolB::insertar (int clave)
			{nodo *padre= NULL, *Actual=raiz;
			if(Actual->Nclaves !=0){
				 Actual = buscar_nodo( clave, Actual, &padre);
			}
			
			 if (Actual->Nclaves< 2*d-1) InsertarNodoNormal(clave, Actual);
			//else InsertarNodoLleno(clave, Actual, padre);
			}

nodo *arbolB:: buscar_nodo(int clave, nodo *Actual, nodo **padre)
			{ int i=0;
			 while((i < Actual->Nclaves) && clave > Actual->claves[i]) i++;
			 if (Actual->hoja)
				{if (Actual==raiz)
					*padre=NULL;
				 return Actual;} 	
			 else  {*padre= Actual;
				 Actual= Actual ->hijos[i];
				 return buscar_nodo(clave, Actual, padre);}
			}


int arbolB::InsertarNodoNormal(int clave, nodo *Actual)
			{int i, j;
			 i=Actual->Nclaves;
			 while((i-1)>=0 && clave< Actual->claves[i-1])
				{Actual->claves[i]=Actual->claves[i-1];
				 if (!Actual->hoja) //si el nodo no es una hoja
					Actual->hijos[i+1]=Actual->hijos[i];
				 i++;
				}
			 Actual->claves[i]=clave;
			( Actual->Nclaves)++;
			return i;
			}

void arbolB::InsertarNodoLleno( int clave, nodo *Actual, nodo *padre)
			{int pos, sube;
			 nodo *nuevo, * nivelad=NULL;
			 sube = dividir_nodo(Actual, &nuevo);
			 if(clave < sube)
				{Actual->claves[d-1]=clave;
				 (Actual->Nclaves)++;	}
			 else	{nuevo->claves[d-1]=clave;
				 (nuevo->Nclaves)++;}
			 if(Actual != raiz && padre->Nclaves< 2*d-1)
				{pos= InsertarNodoNormal(sube, padre);
				 padre->hijos[pos]=Actual;
				 padre->hijos[pos+1]=nuevo;}
			 else	{if (Actual==raiz)
					{nivelad=crear_nodo(d);
					 nivelad->hoja = false;
					 nivelad->Nclaves=1;
					 nivelad->hijos[0]= Actual;
					 nivelad->hijos[1]=nuevo;}
				 else	{nivelad=buscar_padre(padre->claves[0], padre, nivelad);
					 InsertarNodoLleno(padre->claves[d-1], padre, nivelad);}
				}
			}


int arbolB::dividir_nodo(nodo *actual, nodo **hermano)
			{int i;
			 nodo *nuevo=crear_nodo(d);
			 nuevo->hoja=actual->hoja;
			 for(i=0; i<d-1; i++)
				nuevo->claves[i]=actual->claves[i+d];
			 if(!actual->hoja)
				for (i=0; i<d; i++)
					nuevo->hijos[i]=actual->hijos[i+d];
			 nuevo->Nclaves=actual->Nclaves=d-1;
			 return actual->claves[d-1];
			}

nodo *arbolB::buscar_padre (int clave, nodo *Actual, nodo *padre)
			{int i=0;
			 if(clave == Actual->claves[0])
				 return padre;
			 else	{while(i < Actual->Nclaves && clave > Actual->claves[i]) i++;
				 padre=Actual;
				 Actual= Actual -> hijos[i];
				 return buscar_padre(clave, Actual, padre);}
			}

#endif

