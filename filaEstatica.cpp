#include <stdio.h>
#include <stdlib.h>

const int tamanho = 5;

typedef struct FILA{
    int total;
    int inicio, fim;
    int dados[tamanho];
};

void initFila(FILA *fila);
int isEmpty(FILA *fila);
int isFull(FILA *fila);
void insereFila(FILA *fila, int numero);
void tiraFila(FILA *fila);
void realoca(int &i);
void mostraFila(FILA *fila);

int main(){
    FILA *fila = (FILA *)malloc(sizeof(FILA));
    initFila(fila);

    char op;
    
    do{
        system("cls");   
        printf("1 - Inserir na fila\n");
        printf("2 - Remover da fila\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("> ");
        scanf("%c",&op);
        
        if(op=='1'){
            system("cls");
            int numero;
            printf("Digite um numero: ");
            scanf("%d",&numero);
            insereFila(fila,numero);
            printf("\n");
            system("pause");
        }

        if(op=='2'){
            system("cls");
            tiraFila(fila);
            printf("\n");
            system("pause");
        }

        if(op=='3'){
            system("cls");
            mostraFila(fila);
            printf("\n");
            system("pause");
        }

    }while(op!='0');



    free(fila);
    printf("\nPonteiro liberado");
}

void initFila(FILA *fila){
    fila->total=0;
    fila->inicio=0;
    fila->fim=0;
}

int isEmpty(FILA *fila){
    return fila->total==0;
}

int isFull(FILA *fila){
    return fila->total==tamanho;
}

void insereFila(FILA *fila, int numero){
    if(!isFull(fila)){
        fila->dados[fila->fim]= numero;
        realoca(fila->fim);
        fila->total+=1;
    }else{
        printf("\nFila cheia!\n");
    }
}

void tiraFila(FILA *fila){
    int removido;
    if(!isEmpty(fila)){
        removido = fila->dados[fila->inicio];
        realoca(fila->inicio);
        fila->total-=1;
        printf("\nNumero removido: %d",removido);
    }else{
        printf("\nFila Vazia!\n");
    }
}

void realoca(int &i){
    i = i+1;
    if(i>tamanho-1){
        i = 0;
    }
}


void mostraFila(FILA *fila){
    int indice = fila->inicio;
    
    printf("\nElementos da fila:\n");
    for(int i=0;i<fila->total;i++){
        printf("%5d",fila->dados[indice]);
        if(indice>=tamanho-1){
            indice=0;
        }else{
            indice++;
        }
        
    }

    printf("\nTotal: %d",fila->total);

}
