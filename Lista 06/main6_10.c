/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício Semana 6*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20 /*Define o tamanho maximo para o vetor x*/
 
/*Funcao para verificar organizar os elementos em ordem crescente*/
void max_heapify(char *saida[], int raiz, int tam)
{
    int maior=raiz; /*no de maior valor*/
    int esq=2*raiz; /*no esquerdo*/
    int dir=2*raiz+1; /*no direito*/
 
    char *aux[1]; /*string auxiliar para trocar os elementos*/
    /*Verifica se existem filhos do lado esquerdo, e se o esquerdo eh maior que o direito e o pai*/
    if((esq<=tam)&& (strcmp(saida[esq],saida[dir])>0)&& (strcmp(saida[esq],saida[raiz])>0))
    {
        maior=esq; /*O maior valor eh o esquerdo*/
    }
    else
    {
        maior=raiz; /*Senao o maior valor eh o pai*/
    }
    /*Verifica se existem filhos do lado direito, e se o direito eh maior que o esquerdo e o pai*/
    if((dir<=tam)&& (strcmp(saida[dir],saida[raiz])>0)&& (strcmp(saida[dir],saida[esq])>0))
    {
        maior=dir;
    }
    if(strcmp(saida[raiz],saida[maior])<0)
    {
        /*Troca as palavras de posicao*/
        aux[0]=saida[raiz];
        saida[raiz]=saida[maior];
        saida[maior]=aux[0];
        /*Chama a funcao max_heapify*/
        max_heapify(saida,raiz,maior);
    }
}
 
/*Funcao build_maxheap*/
void build_maxheap(char * saida[], int tam)
{
    int i;
    char *aux[1];
    for (i=(tam/2)-1; i>=0; i--)
    {
        /*Vai pra funcao max_heapify para verifica a subarvore*/
        max_heapify(saida,i,tam);
    }
    for(i=tam-1; i>0; i--)
    {
        /*Troca de posicao as palavras*/
        aux[0]=saida[0];
        saida[0]=saida[i];
        saida[i]=aux[0];
        /*Vai pra funcao max_heapify*/
        max_heapify(saida,i,0);
    }
}
 
/*Funcao main*/
int main ()
{
    int n,m,i,j; /*Declarando atributos*/
    scanf("%d",&n); /*Recebe a qtd de palavras que serao escritas*/
    char *palavra[n]; /*Ponteiro de strings*/
    for(i=0; i<n; i++)
    {
        palavra[i]=malloc(MAX*sizeof(char)); /*Aloca espaco para as strings*/
        scanf("%s",palavra[i]); /*Armazena a string*/
    }
    scanf("%d",&m); /*Recebe a qtd de palavras para serem selecionadas*/
    char *saida[m]; /*Ponteiro de strings que serao escolhidos*/
    int p[m]; /*Declarando vetor*/
    for(i=0; i<m; i++)
    {
        scanf("%d",&p[i]); /*Armazena as posicoes das palavras que serao escolhidas*/
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<strlen(palavra[i]); j++)
        {
            /*Se na palavra tiver letra maiuscula, acentos ou caracteres especiais, eh invalido*/
            if(!islower(palavra[i][j]))
            {
                printf("a palavra %s eh invalida", palavra[i]);
                return 0; /*Encerra o programa*/
            }
        }
    }
    for(i=0; i<m; i++)
    {
        saida[i]=malloc(MAX*sizeof(char)); /*Aloca espaco para os atribuots de saida*/
        strcpy(saida[i],palavra[p[i]]); /*Copia de 'palavra' na posicao p[i] para a 'saida'*/
    }
    printf("build_heap: ");
    for(i=0; i<m; i++)
    {
        printf("%s ",saida[i]); /*Mostra as palavras escolhidas*/
    }
    printf("\n");
    build_maxheap(saida, m); /*Vai para a funcao 'build_maxheap' onde vai ordenar as palavras*/
    printf("palavras: ");
    for(i=0; i<m; ++i)
    {
        printf("%s ",saida[i]); /*Imprime as palavras em ordem alfabetica*/
    }
    /*Libera o espaco alocado dos ponteiros*/
    for(i=0; i<n; i++)
    {
        free(palavra[i]);
    }
    for(i=0; i<m; i++)
    {
        free(saida[i]);
    }
    return 0;
}
