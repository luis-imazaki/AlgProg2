#include <stdio.h>
#include <stdlib.h>

struct celula{
    int chave;
    celula *next;
};

void empilha(int x, celula **p){
    celula *novo;
    novo = (celula *) malloc(sizeof(celula));
    novo->next = *p;
    novo->chave = x; 
    *p =novo;
}

int desempilha(celula **p){
    celula *novo;
    int aux;
    novo = new celula();
    novo = *p;
    *p = novo->next;
    aux = novo->chave;
    free(novo);
    return aux;
}
int conta(celula *p){
    celula *aux;
    int cont=0;
    aux=p;
    while(aux!=NULL){
        cont++;
        aux = aux->next;
    }
    return cont;
}

void imprimeA(celula *p){
    celula *aux=p;
    if(aux==NULL){
        printf("Pilha vazia.\n");
    }
    while(aux!=NULL){
        printf("%d ",aux->chave);
        aux = aux->next;
    }
}

void imprimeB(celula *p){
    celula *aux=p;
    int *v;
    int num = conta(p);
    v = (int *) malloc(num*sizeof(int));
    v =  new int();
    if(p==NULL){
        printf("Pilha vazia.\n");
    }
    for(int i = 0; i < num; i++){
        *(v+i)= aux->chave;
        aux= aux->next;
    }
    for(int i = num-1; i >= 0; i--){
        printf("%d ", *(v+i));
    }
    free(v);
}

celula* reverse(celula *p){
    celula *aux=p, *aux2=p;
    int *v;
    int num = conta(p);
    v = (int *) malloc(num*sizeof(int));
    v =  new int();
    if(p==NULL){
        printf("Pilha vazia.\n");
    }
    for(int i = 0; i < num; i++){
        *(v+i)= aux->chave;
        aux= aux->next;
    }
    for(int i = num-1; i >= 0; i--){
        p->chave = *(v+i);
        p=p->next;
    }
    free(v);
    return aux2;
}

int main(){
    int op, x;
    struct celula *p=NULL;

    do{
        printf("\nDigite 0 para: Finalizar.\n");
        printf("Digite 1 para: Empilhar.\n");
        printf("Digite 2 para: Desempilhar.\n");
        printf("Digite 3 para: Contar.\n");
        printf("Digite 4 para: Imprimir A.\n");
        printf("Digite 5 para: Imprimir B.\n");
        printf("Digite 6 para: Reverter.\n");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            printf("Digite o primeiro valor da pilha.\n"); scanf("%d",&x);
            empilha(x, &p);
            break;
        
        case 2:
            if(p==NULL){
                printf("Pilha vazia.\n");
            }
            else{
                desempilha(&p);
            }
            break;
        case 3:
            printf("O total de elemento na lista é: %d\n",conta(p));
            break;
        case 4:
            imprimeA(p);
            break;
        case 5:
            imprimeB(p);
            break;
        case 6:
            p=reverse(p);
            break;
        }
    }while(op!=0);
    free(p);
}
