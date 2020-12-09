/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 1 */
/* Codigo: "Hello World" usando threads em C e a funcao que espera as threads terminarem */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int start, end;
} t_Args;

#define NTHREADS 2
int numeros[90];

//funcao executada pelas threads
void *IncrementOne (void *arg) {
  t_Args *args = (t_Args *) arg;
  int i = 0;
  for(i=args->start; i<args->end;i++){
    numeros[i]+=1;
  }

  free(arg); //aqui pode liberar a alocacao feita na main

  pthread_exit(NULL);
}

//funcao principal do programa
int main() {
  pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
  int thread; //variavel auxiliar
  int i;
  //Preenchendo valores no vetor
  for(i=10;i<100;i++){
    numeros[i-10] = i;
  }

  printf("VALORES INICIAIS\n");
  for(i=0; i<90;i++){
    printf("%d ", numeros[i]);
  }
  for(thread=0; thread<NTHREADS; thread++) {
    t_Args *arg; //receberá os argumentos para a thread

    arg = malloc(sizeof(t_Args));
    if (arg == NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }
    if(thread == 0){
      arg->start = 0; 
      arg->end = 44; 
    }else{
      arg->start = 45; 
      arg->end = 90; 
    }
    
    printf("\n--Cria a thread %d\n", thread);
    if (pthread_create(&tid_sistema[thread], NULL, IncrementOne, (void*) arg)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  //--espera todas as threads terminarem
  for (thread=0; thread<2; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }


  printf("VALORES FINAIS\n");
  for(i=0; i<90;i++){
    printf("%d ", numeros[i]);
  }

}
