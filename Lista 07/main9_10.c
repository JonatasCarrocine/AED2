/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício Semana 7*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20 /*Define o tamanho maximo para o vetor x*/
 
/*Funcao para verificar o caractere atual*/
int verificaChar(char **A, int i, int j){
    if(A[i][j]!=32){ /*32 em ASC II seria o campo 'space'*/
        return (A[i][j]-96);
    }
    else{
        return (A[i][j]-32);
    }
}
 
/*Funcao counting sort*/
void count_sort(char **A, int n, int coluna){
    char B[n][MAX]; /*Vetor de strings auxiliar para ordenar*/
    int i,j,C[27],x; /*Variaveis e vetor utilizados*/
    for(i=0;i<27;i++){
        C[i]=0; /*Declara todo os campos do vetor como 0*/
    }
    for(i=0;i<n;i++){
        for(x=0;x<MAX;x++){
            B[i][x]=32; /*Gera um vetor B preenchido de espacos, que sera utilizado posteriormente*/
        }
    }
    for(j=0;j<n;j++){
        C[verificaChar(A,j,coluna)]++; /*Incrementa cada posicao do vetor de acordo com o alfabeto*/
    }
    for(i=1;i<27;i++){
        C[i]=C[i]+C[i-1]; /*Soma o valor do campo da posicao anterior com o atual*/
    }
    for(i=0;i<27;i++){
        printf("%d ",C[i]); /*Imprime a linha de valores*/
    }
    printf("\n");
 
    for(j=n-1;j>=0;j--){
        for(x=0;x<MAX;x++){
            B[C[verificaChar(A,j,coluna)]-1][x]=A[j][x];
        }
        C[verificaChar(A,j,coluna)]--;
    }
 
    for(j=0;j<n;j++){
        for(x=0;x<MAX;x++){
            A[j][x]=B[j][x]; /*Vetor A recebe os caracteres em B, ordenado*/
        }
    }
}
 
/*Funcao radix sort*/
void radix_sort(char **A, int n, int maior){
    int i=0;
    int a=maior-1;
    for(i=a;i>=0;i--){
        count_sort(A,n,i); /*Chama a funcao count_sort*/
    }
}
 
/*Funcao main*/
int main ()
{
    int n,i,p,m,j,maior; /*Variaveis que serao utilizadas*/
    maior=0;
    scanf("%d",&n);
    char **palavra; /*Ponteiro de ponteiro de strings*/
    palavra=(char**)malloc(n*sizeof(char*)); /*Aloca espaco para a quantidade de palavras que serao digitada*/
    for(i=0;i<MAX;i++)
    {
        palavra[i]=(char*)malloc(MAX*sizeof(char)); /*Aloca espaco para 20 caracteres em cada palavra*/
    }
    for(i=0; i<n; i++)
    {
        scanf("%s", palavra[i]); /*Digita as palavras*/
    }
    scanf("%d",&p); /*Armazena o valor da primeira posicao para impressao em ordem alfabetica */
    scanf("%d",&m); /*Armazena o valor para imprimir as proximas palavras*/
 
    for(i=0; i<n; i++)
    {
        for(j=0;j<strlen(palavra[i]); j++)
        {
            /*Se na palavra tiver letra maiuscula, transforma em letra minuscula*/
            if((palavra[i][j])<97)
            {
                palavra[i][j]+=32;
            }
        }
        if(strlen(palavra[i])>maior){ /*Se determinada palavra for maior que o localizado em 'maior', armazena*/
            maior=strlen(palavra[i]);
        }
    }
    for(i=0;i<n;i++){
        printf("%s.\n",palavra[i]); /*Imprime as palavras com o ponto final*/
    }
    for(i=0;i<n;i++){
        while(strlen(palavra[i])<MAX){ /*Enquanto a palavra nao atinge seu tamanho maximo, preenche de campos vazios*/
            strcat(palavra[i]," ");
        }
    }
    printf("%d\n",maior); /*Imprime o tamanho da maior palavra*/
    radix_sort(palavra,n,maior); /*Chama a funcao para ordenar as palavras e mostrar counting sort*/
    for(i=p-1;m>=1;i++){ /*Imprime as palavras no determinado intervalo definido em 'p' e 'm'*/
        printf("%s", palavra[i]);
        m--;
        printf("\n");
    }
}
