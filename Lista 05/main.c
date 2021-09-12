/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício Semana 5*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 /*Define o tamanho maximo para o vetor x*/
 
/*Funcao que vai realizar a troca entre as posicoes do vetor*/
void troca(int* i, int* j){
    int aux = *i; /*Vetor auxiliar recebe conteudo em 'i'*/
    *i = *j; /*Conteudo em 'i' recebe o conteudo em 'j'*/
    *j = aux; /*Conteudo em 'j' recebe o valor do vetor auxiliar*/
}
 
/*Funcao que vai ser feita a particao */
int particao (int x[], int esquerdo, int direito){
    int pivo = x[direito]; /*Atributo 'pivo' recebe o ultimo valor do vetor*/
    int i = esquerdo; /*Atributo recebe o primeiro valor do vetor*/
    int j;
    for(j = esquerdo; j<=direito-1;j++){
        if(x[j]<pivo){ /*Se o valor na posicao atual for menor que o pivo, incrementa i e troca os valores de posicao*/
            troca(&x[i],&x[j]);
            i++;
        }
    }
    troca(&x[i],&x[direito]);/*A funcao pega o valor da posicao 'i' e leva pro final de vetor, para comparar novamente*/
    return i; /*Retorna o valor 'i'*/
}
 
/*Funcao que realiza a ordenacao da forma de quicksort*/
void quicksort(int x[], int esquerdo, int direito, int k){
    /*A funcao funciona somente se a posicao de busca esteja dento do tamanho do vetor*/
    if(k>0 && k<=direito-esquerdo+1){
        int q = particao(x,esquerdo,direito); /*Atributo recebe o valor de 'i' da funcao particao*/
        if(q-esquerdo<=k-1){
            /*Se o valor obtido for menor ou oigual a posicao desejada no vetor, verifica no intervalo de
            q+1 ateh o fim do vetor*/
            quicksort(x,q+1,direito,k-q+esquerdo-1);
        }
        else{
            /*Se o valor obtido for maior que da posicao desejada, chama a funcao quicksort, agora pra
            verificar no intervalo da posicao em 'esquerdo' ateh o 'q-1' obtido*/
            quicksort(x,esquerdo,q-1,k);
        }
    }
}
 
/*Funcao que vai imprimir o vetor ordenado no momento em que as condicoes do programa sao atendidas*/
void ordenado(int x[], int tam){
    int i;
    for(i=0;i<tam;i++){
        printf("%d ",x[i]);/*Imprime cada posicao do vetor*/
    }
}
 
/*Funcao main*/
int main (void)
{
    int n,k,i; /*Declarando atributos*/
    int x[MAX]; /*Declarando vetor*/
    scanf("%d",&k); /*Recebe a posicao para descobrir o valor*/
    scanf("%d",&n); /*Recebe a qtd de valores que serao inseridos no vetor*/
    for(i=0;i<n;i++){
        scanf("%d",&x[i]); /*Digitar o valor em cada posicao*/
    }
    quicksort(x,0,n-1,k); /*Vai para a funcao quicksort*/
    printf("%do menor elemento eh o %d\n",k,x[k-1]);
    ordenado(x,n); /*Chama a funcao que vai imprimir o vetor*/
 
    return 0;
}
