#include <stdio.h>
#include <stdlib.h>
 
#define M 2
#define MM (2 * M)
 
/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Tarefa 15*/
 
/*Struct da nossa ArvoreB*/
struct ArvoreB
{
    int val[MM+1], count;
    struct ArvoreB *link[MM+1];
};
 
struct ArvoreB *raiz;
 
/*Funcao para criar um no*/
struct ArvoreB *criaNo(int val, struct ArvoreB *filho){
    struct ArvoreB *novo;
    novo = (struct ArvoreB *)malloc(sizeof(struct ArvoreB)); /*Aloca o espaco para esse no*/
    novo->val[1]=val; /*Atribui os valores desse novo no*/
    novo->count=1;
    novo->link[0]=raiz;
    novo->link[1]=filho;
    return novo;
}
 
/*Funcao para inserir um no*/
void insercao(int val, int pos, struct ArvoreB *no, struct ArvoreB *filho)
{
    int j = no->count;
    while(j>pos){
        no->val[j+1]=no->val[j]; /*Move os valores para a proxima posicao*/
        no->link[j+1]=no->link[j];
        j--;
    }
    no->val[j+1]=val;
    no->link[j+1]=filho;
    no->count++;
}
 
/*Funcao para separar um no*/
void separa(int val, int *pVal, int pos, struct ArvoreB *no, struct ArvoreB *filho, struct ArvoreB **novoNo)
{
    int medio, j;
    if(pos>M){
        medio=M+1;
    }
    else{
        medio=M;
    }
 
    *novoNo = (struct ArvoreB *)malloc(sizeof(struct ArvoreB)); /*Aloca espaco para a nova cadeia de nos*/
    j = medio+1;
    while(j<= MM){
        (*novoNo)->val[j-medio]=no->val[j];
        (*novoNo)->link[j-medio]=no->link[j];
        j++;
    }
    no->count=medio;
    (*novoNo)->count = MM - medio;
 
    if(pos<=M){
        insercao(val,pos,no,filho); /*Realiza a insercao de um lado*/
    }else{
        insercao(val,pos-medio,*novoNo,filho); /*Realiza a insercao do outro lado*/
    }
    *pVal = no->val[no->count];
    (*novoNo)->link[0]=no->link[no->count];
    no->count--;
}
 
/*Setar valor, vai ser a funcao onde vai realizar as insercoes e separar os nos, se necessario*/
int setValor(int val, int *pVal, struct ArvoreB *no, struct ArvoreB **filho)
{
    int pos;
    if(!no){
        *pVal=val;
        *filho=NULL;
        return 1;
    }
 
    if(val<no->val[1]){ /*Se o valor for menor que o da primeira posicao, ele pode ser inserido*/
        pos=0;
    } else{
        for(pos=no->count;(val<no->val[pos]&&pos>1);pos--); /*Percorre toda a cadeia de nos*/
        if(val==no->val[pos]){ /*Se o valor ja existir, nao insere ele*/
            return 0;
        }
    }
    if(setValor(val,pVal,no->link[pos],filho)){
        if(no->count<MM){ /*Se a quantidade for menor que o tamanho maximo da ordem, insere ele*/
            insercao(*pVal,pos,no,*filho);
        }
        else{ /*Caso contrario, separa as cadeias de nos*/
            separa(*pVal, pVal, pos, no, *filho, filho);
            return 1;
        }
    }
    return 0;
}
 
/*Funcao para inserir o valor*/
void insere(int val){
    int flag, i;
    struct ArvoreB *filho;
 
    flag = setValor(val,&i,raiz,&filho);
    if(flag){ /*Se nao tver nenhum no na arvore, ou se precisa separar as cadeias de nos*/
        raiz=criaNo(i,filho); /*Cria um novo no*/
    }
}
 
/*Funcao para buscar um no*/
int busca(int val, int *pos, struct ArvoreB *no)
{
    int qtd=0, achou=0;
    if(!no){
        return; /*Retorna nada, se nao houver no na arvoreB*/
    }
    if(val<no->val[1]){ /*Se o valor a ser buscado for o menor que o no da primeira posicao, verifica o seu filho*/
        *pos=0;
    }
    else{
        for(*pos = no->count;(val<no->val[*pos] && *pos>1); (*pos)--){
            if(*pos>qtd){ /*Verifica se o valor da utlima posicao eh maior que a variavel 'qtd'*/
                qtd=*pos; /*Atribui o valor pra 'qtd', que vai retornar a quantidade de elementos da cadeia de nos*/
            }
        }
        if(val == no->val[*pos]){ /*Se o valor pesquisado foi encontrado, vericia sua posicao, e atribui 1 para 'achou'*/
            if(*pos>qtd){
                qtd=*pos;
            }
            achou=1;
        }
        if(achou==1){
            printf("%d",qtd); /*Imprime a quantidade de elementos da cadeia de nos*/
            return 1;
        }
    }
    busca(val,pos,no->link[*pos]); /*Chama a funcao, para verificar outra cadeia de nos*/
    return;
    if(achou==0){
        return;
    }
}
 
/*Funcao para imprimir a quantidade de elementos na raiz*/
void qtdRaiz(struct ArvoreB *no){
    int i,qtd;
    if(no){
        printf("%d \n",no->count);
    }
}
 
/*Funcao principal*/
int main()
{
    int numeros,pesquisa,ch,i,achou=0; /*Variaveis utilizadas*/
 
    for(i=0; i<1000; i++){
        scanf("%d", &numeros); /*O usuario digita o valor desejado*/
        if(numeros>=0)  /*Se o numero foi maior que 0, insere ele na tabela*/
        {
            insere(numeros);
        }
        else  /*Senao, encerra o laco de repeticao*/
        {
            break;
        }
    }
 
    qtdRaiz(raiz); /*Imprime a quantidade de elementos que existe na raiz*/
 
    scanf("%d", &pesquisa); /*Usuario digita um valor para verificar se existe na ArvoreB*/
    achou=busca(pesquisa,&ch,raiz); /*Funcao que retorna um valor pra verificar se o valor esta na Arvore*/
    if(achou!=1){ /*Se nao estiver, imprime a mensagem de que nao foi encontrado*/
        printf("Valor nao encontrado");
    }
    return 0;
}
