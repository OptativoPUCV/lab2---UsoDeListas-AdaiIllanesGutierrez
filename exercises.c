#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
   List* L = create_list();
  for(int i=0;i<10;i++){
    int* element = (int*)malloc(sizeof(int));
    *element = i+1;
    pushFront(L, element);
  } 
  return L;
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
  int* elemento = (int*)first(L);
   int suma = 0;
   while (elemento != NULL) {
      suma += *elemento;
      elemento = (int*)next(L);
   }
   return suma;
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List*L, int elem){
  void* elemento = first(L);
  while (elemento != NULL) {
      if (*(int*)elemento == elem) {
          elemento = popCurrent(L);
      }
      elemento = next(L);
  }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

/*void copia_pila(Stack* P1, Stack* P2) {
 Stack* aux_stack = create_stack(); 
  void *dato = first(P1);
  while (dato!=NULL) {
      push(aux_stack, top(P1));
      pop(P1);
  }
  while (aux_stack) {
      void* element = top(aux_stack);
      push(P1, element);
      push(P2, element);
      pop(aux_stack);
  }
  
}*/
void copia_pila(Stack* P1, Stack* P2) {
    // Crear una pila auxiliar
    Stack* aux_stack = create_stack();
    // Copiar los elementos de P1 a la pila auxiliar y mantener el orden
    while (top(P1) != NULL) {
        push(aux_stack, top(P1));
        pop(P1);
    }
    // Restaurar el orden de los elementos en P1 y copiarlos a P2
    while (top(aux_stack) != NULL) {
        void* element = top(aux_stack);
        push(P1, element);
        push(P2, element);
        pop(aux_stack);
    }
}



/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) {
  int len = strlen(cadena);
  Stack *stack = create_stack();
  for (int i = 0; i < len; i++) {
      if (cadena[i] == '(' || cadena[i] == '[' || cadena[i] == '{') {
          push(stack, &cadena[i]);
      } else if (cadena[i] == ')' || cadena[i] == ']' || cadena[i] == '}') {
          if (top(stack) == NULL) {
              return 0; 
          }
          char *top_char = (char *)top(stack);
          if ((cadena[i] == ')' && *top_char == '(') ||
              (cadena[i] == ']' && *top_char == '[') ||
              (cadena[i] == '}' && *top_char == '{')) {
              pop(stack);
          } else {
              return 0; 
          }
      }
  }
  int balanceados;
  if (top(stack) == NULL) {
    balanceados = 1; // Si la pila está vacía, los paréntesis están balanceados
} else {
    balanceados = 0; // Si la pila no está vacía, los paréntesis no están balanceados
}
  /*int balanceados = (top(stack) == NULL) ? 1 : 0;*/
  return balanceados;
}
/*
int parentesisBalanceados(char *cadena) {
  Stack *s = create_stack();

  while (*cadena != '\0') {
      if (*cadena == '(' || *cadena == '[' || *cadena == '{') {
          // Si se encuentra un paréntesis de apertura, se agrega a la pila
          push(s, cadena);
      } else if (*cadena == ')' || *cadena == ']' || *cadena == '}') {
          // Si se encuentra un paréntesis de cierre
          if (s == NULL) {
              // Si la pila está vacía, no hay un paréntesis de apertura correspondiente
              return 0;
          }
          char *topChar = (char*)pop(s);
          if ((*cadena == ')' && *topChar != '(') ||
              (*cadena == ']' && *topChar != '[') ||
              (*cadena == '}' && *topChar != '{')) {
              // Si el paréntesis de cierre no coincide con el paréntesis de apertura superior en la pila
              return 0;
          }
      }
      cadena++;
  }
  // Si la pila está vacía al final, todos los paréntesis están balanceados
  return s == NULL;
}*/