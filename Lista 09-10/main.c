/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício 9*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/*Gera as informacoes de um no*/
struct TNo
{
    int valor;
    struct TNo *esq;
    struct TNo *dir;
    int tamanho;
};
 
/*Funcao para obter a altura da arvore, a partir de um no*/
int tamanho(struct TNo *N)
{
    if(N==NULL) /*Neste caso, a arvore nao possui o valor, logo o tamanho eh 0*/
        return 0;
    return N->tamanho;
}
 
/*Funcao para encontrar o maior valor entre dois*/
int maximo(int v1, int v2)
{
    if(v1>v2)
        return v1;
    else
        return v2;
}
 
/*Funcao para criar um novo no da arvore*/
struct TNo *NovoNo(int valor)
{
    struct TNo *novo=(struct TNo *)malloc(sizeof(struct TNo));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->tamanho = 1;
    return novo;
}
/*Funcao para fazer a rotacao pela esquerda*/
struct TNo *LL(struct TNo *pA)
{
    struct TNo *pB = pA->dir;
    struct TNo *pC = pB->esq;
    pB->esq=pA;
    pA->dir=pC;
 
    pA->tamanho=maximo(tamanho(pA->esq),tamanho(pA->dir))+1;
    pB->tamanho=maximo(tamanho(pB->esq),tamanho(pB->dir))+1;
 
    return pB;
}
/*Funcao para fazer a rotacao pela direita*/
struct TNo *RR(struct TNo *pA)
{
    struct TNo *pB = pA->esq;
    struct TNo *pC = pB->dir;
    pB->dir=pA;
    pA->esq=pC;
 
    pA->tamanho=maximo(tamanho(pA->esq),tamanho(pA->dir))+1;
    pB->tamanho=maximo(tamanho(pB->esq),tamanho(pB->dir))+1;
 
    return pB;
}
 
/*Funcao para verificar se a arvore esta balanceada*/
int balanca(struct TNo *N)
{
    if(N == NULL) /*Se nao houver uma arvore criada, retorna 0*/
    {
        return 0;
    }
    return tamanho(N->esq)-tamanho(N->dir);
}
 
/*Funcao para inserir um novo no na arvore*/
struct TNo *insere(struct TNo *Atual, int valor)
{
    if(Atual==NULL)  /*Se o valor a ser adicionado nao existe na arvore, chama a funcao pra criar um no*/
    {
        return NovoNo(valor);
    }
    if(valor<Atual->valor)  /*Se o valor for menor que o do no atual pesquisado, ele verifica a esquerda do no atual*/
    {
        Atual->esq=insere(Atual->esq, valor);
    }
    else if(valor>Atual->valor)  /*Se o valor for maior que o do no atual pesquisado, ele verifica a direita do no atual*/
    {
        Atual->dir=insere(Atual->dir, valor);
    }
    else
    {
        return Atual;
    }
    /*Atribui o tamanho desse no a partir da maior altura encontrada entre a esquerda ou direita*/
    Atual->tamanho=1+maximo(tamanho(Atual->esq),tamanho(Atual->dir));
    /*Atribui o valor pra verificar se a arvore estah balanceada, depois de adicionar o no*/
    int balancea=balanca(Atual);
 
    /*Se estiver desbalanceada (ou seja, com mais nos) na esquerda e o valor do no
    recem-inserido for menor que o do no atual da esquerda, faz uma rotacao da direita*/
    if(balancea>1 && balanca(Atual->esq)>=0)
    {
        return RR(Atual);
    }
    /*Se estiver desbalanceada na direita e o valor do no recem-inserido for maior
    que o do no atual da esquerda, faz uma rotacao da esquerda*/
    if(balancea<-1 && balanca(Atual->dir)<=0)
    {
        return LL(Atual);
    }
    /*Se estiver desbalanceada na esquerda e o valor do no recem-inserido for maior que
    o do no atual da esquerda, faz uma rotacao da esquerda, e depois para a direita*/
    if(balancea>1 && balanca(Atual->esq)<0)
    {
        Atual->esq=LL(Atual->esq);
        return RR(Atual);
    }
    /*Se estiver desbalanceada na direita e o valor do no recem-inserido for maior que o
    do no atual da esquerda, faz uma rotacao da direita, e depois para a esquerda*/
    if(balancea<-1 && balanca(Atual->dir)>0)
    {
        Atual->dir=RR(Atual->dir);
        return LL(Atual);
    }
    return Atual;
}
 
/*Funcao pata obter o valor do menor no*/
struct TNo *minValor(struct TNo* No)
{
    struct TNo* atual= No;
    while(atual->esq!=NULL)
    {
        atual=atual->esq;
    }
    return atual;
}
 
/*Funcao para deletar um no da arvore*/
struct TNo* deleta(struct TNo *Atual, int valor)
{
    if(Atual==NULL) /*Se o no nao estiver na arvore, logo nao precisa excluir*/
    {
        return Atual;
    }
    if(valor<Atual->valor) /*Se o valor for menor que o do no atual pesquisado, ele verifica a esquerda do no atual*/
    {
        Atual->esq=deleta(Atual->esq,valor);
    }
    else if(valor> Atual->valor) /*Se o valor for maior que o do no atual pesquisado, ele verifica a direita do no atual*/
    {
        Atual->dir=deleta(Atual->dir,valor);
    }
    else  /*O no acabou sendo encontrado*/
    {
        if((Atual->esq==NULL)||(Atual->dir==NULL))  /*O no eh uma folha, por nao ter descendentes*/
        {
            struct TNo* temp=Atual->esq? Atual->esq: Atual->dir;
            if(temp==NULL) /*Se temp for nulo, logo o no atual fica nulo*/
            {
                temp=Atual;
                Atual=NULL;
            }
            else
            { /*Senao, o seu conteudo recebe o conteudo de temp*/
                *Atual=*temp;
            }
            free(temp); /*Libera o no da memoria*/
        }
        else  /*Se tiver filhos...*/
        {
            struct TNo* temp=minValor(Atual->dir); /*Pega o menor valor a direita do que serah deletado*/
            Atual->valor=temp->valor; /*O valor do no atual recebe do no temporario*/
            Atual->dir=deleta(Atual->dir,temp->valor); /*Chama a funcao deleta, a partir de seu valor a direita*/
        }
    }
    if(Atual==NULL)
    {
        return Atual;
    }
    /*Parte do codigo semelhante ao da funcao de inserir, para ver o balanceamento da arvore*/
    Atual->tamanho=1+maximo(tamanho(Atual->esq),tamanho(Atual->dir));
 
    int balancea=balanca(Atual);
 
    if(balancea>1 && balanca(Atual->esq)>=0)
    {
        return RR(Atual);
    }
    if(balancea>1 && balanca(Atual->esq)<0)
    {
        Atual->esq=LL(Atual->esq);
        return RR(Atual);
    }
    if(balancea<-1 && balanca(Atual->dir)<=0)
    {
        return LL(Atual);
    }
    if(balancea<-1 && balanca(Atual->dir)>0)
    {
        Atual->dir=RR(Atual->dir);
        return LL(Atual);
    }
    return Atual;
}
 
/*Funcao para obter a altura da arvore, a partir de um no*/
int Altura(struct TNo *Raiz, int *altura, int aux, int *tam)
{
    if(Raiz==NULL)
    {
        return;
    }
    if(Raiz->esq!=NULL)
    {
        Altura(Raiz->esq, altura, aux+1, tam);
    }
    if(Raiz->dir!=NULL)
    {
        Altura(Raiz->dir, altura, aux+1, tam);
    }
    if(aux>=*altura)
    {
        *altura=aux;
    }
    *tam+=1;
}
 
/*Funcao para pesquisar os nos, insere se nao tiver na arvore, deleta se ja ter na arvore*/
struct TNo* pesquisa(struct TNo *Raiz, struct TNo *Atual,int valor)
{
    if(Atual==NULL)  /*Se a nossa arvore for vazia, cria um novo no*/
    {
        return NovoNo(valor);
    }
    /*Se o valor a direita nao for vazio e o valor pesquisado for maior que
    o no atual, pesquisa o descendente a direita do atual*/
    if(Atual->dir!=NULL && valor>Atual->valor)
    {
        pesquisa(Raiz,Atual->dir,valor);
    }
    /*Se o valor a direita for vazio e o valor for maior que o no atual, insere o novo no a direita do atual*/
    else if(Atual->dir==NULL && valor>Atual->valor)
    {
        Raiz=insere(Raiz,valor);
    }
    /*Se o valor da esquerda nao for vazio e o valor pesquisado for menor que
    o no atual, pesquisa o descendente a esquerda do atual*/
    else if(Atual->esq!=NULL && valor<Atual->valor)
    {
        pesquisa(Raiz,Atual->esq,valor);
    }
    /*Se o valor da esquerda for vazio e o valor for menor que o no atual, insere o novo no a esquerda do atual*/
    else if(Atual->esq==NULL && valor<Atual->valor)
    {
        Raiz=insere(Raiz,valor);
    }
    /*Se o valor estiver na arvore, chama a funcao para deletar esse no*/
    else if(valor==Atual->valor)
    {
        Atual=deleta(Raiz,valor);
    }
    return Atual;
}
 
/*Funcao para busca um no, e mostra o seu tamanho na esqueda e direita*/
struct TNo* busca(struct TNo *Raiz, int valor)
{
    if(Raiz!=NULL)  /*Se o no estiver na arvore, faz o que segue*/
    {
        if(Raiz->valor==valor)  /*Se o valor da raiz for igual ao valor para busca, retorna o no*/
        {
            return Raiz;
        }
        else
        {
            if(valor<Raiz->valor)  /*Se o valor buscado for menor que o no atual, busca o no a esquerda*/
            {
                return busca(Raiz->esq,valor);
            }
            else  /*Se o valor buscado for maior que o no atual, busca o no a direita*/
            {
                return busca(Raiz->dir,valor);
            }
        }
    }
    return 0; /*Se o valor nao estiver na arvore, retorna 0*/
}
 
/*Funcao main*/
int main ()
{
    int numeros, numPesquisa;
    int tamanho=0, alturaesq=0, alturadir=0, altura=0;
    struct TNo *raiz=NULL; /*Gera um no raiz vazio*/
    scanf("%d",&numeros);
    while(numeros!=-1)  /*Insere os nos na arvore, enquanto nao digitar -1*/
    {
        raiz=insere(raiz,numeros);
        scanf("%d",&numeros);
    }
 
    Altura(raiz->esq, &alturaesq,1,&tamanho); /*Obtem a altura da arvore do lado esquerdo*/
    Altura(raiz->dir, &alturadir,1,&tamanho); /*Obtem a altura da arvore do lado direito*/
    if(alturaesq>alturadir)  /*Se o altura do lado esquerdo for maior que o direito, altura recebe a altura de esquerdo*/
    {
        altura=alturaesq;
    }
    else  /*Senao, recebe a altura do lado direito*/
    {
        altura=alturadir;
    }
    printf("%d, %d, %d\n", altura, alturaesq, alturadir); /*Imprime as alturas*/
 
    scanf("%d",&numeros); /*Agora os numeros serao inseridos se nao tiver na arvore, e excluidos se tiverem*/
    while(numeros!=-1)
    {
        raiz=pesquisa(raiz,raiz,numeros);
        scanf("%d",&numeros);
    }
 
    tamanho=0,alturaesq=0,alturadir=0,altura=0; /*Reseta as variaveis*/
    scanf("%d",&numPesquisa);
    raiz=busca(raiz,numPesquisa); /*Busca um valor para encontrar a altura deste no a esquerda e direita*/
    if(raiz==0)  /*Se o valor retornar 0, significa que nao foi encontrado na arvore*/
    {
        printf("Valor nao encontrado");
    }
    else  /*Senao, busca a altura a partir desse no, do lado esquerdo e direito*/
    {
        Altura(raiz->esq, &alturaesq,1,&tamanho);
        Altura(raiz->dir, &alturadir,1,&tamanho);
        if(alturaesq>alturadir)
        {
            altura=alturaesq;
        }
        else
        {
            altura=alturadir;
        }
        printf("%d, %d, %d\n",altura, alturaesq, alturadir); /*Imprime as alturas*/
    }
    return 0;
}
