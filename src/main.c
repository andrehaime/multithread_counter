/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define n_threads 4

void* funcao_thread(void *arg);
int prime(unsigned long long number);

int n_prime = 0;
pthread_mutex_t trava;

int main() {
  unsigned long long entrada[100];
  int n_entradas =0, i =0;
  char escape;
  pthread_t threads[n_threads];
  int thread_args[n_threads];

  /* Entrada de dados comum, como a utilizada no exercicio 4*/
  do {
  	scanf("%llu%c", &entrada[n_entradas], &escape);
  	n_entradas++;
  } while (escape != '\n' && escape != EOF);

  /* Loop de criação das threads*/
  for (int j=0; j<n_threads, i<n_entradas; j++, i++){
		/* Cria thread e passa valor atual como argumento*/
		pthread_create(&(threads[j]), NULL, funcao_thread, &(entrada[i]));

		/* espera sair de todas as threads*/
  	if (j == n_threads -1 || i == n_entradas-1){
  		for (int k=0; k<n_threads && k<n_entradas -1 ; k++){
  			pthread_join(threads[k], NULL);
  		}
  		j = -1;
  	}
  }
  printf("%d\n", n_prime);

  return 0;
}


void* funcao_thread(void *arg) {
  int* N = (int*)arg;
  int M = (*N);

	pthread_mutex_lock(&trava);
  n_prime += prime(M);
  pthread_mutex_unlock(&trava);
  return NULL;
}

int prime(unsigned long long number){
	/* algoritmo simples pra calculo de primos 
		ENTRADA: um numero int de 0 até 2^64 - 1
		SAÍDA: 1 se o número é primo
					 0 se o número não é primo
	*/

	int divisores =0, retorno =0;
	unsigned long long i=0;
	if (number<=1) retorno = 0;
  	else{
	  for(i=1; i<=number/2; i++){
	  	if (number%i == 0) divisores++;
	  	if (divisores >2){
	  		retorno = 0;
	  		break;
	  	} 
	  } 
  	if (divisores <= 1) retorno = 1;
  }
  return retorno;
}