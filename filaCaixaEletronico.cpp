/* Aluno: ALEXANDRE SANTOS CAVALCANTE – Turma: CC4Q68 – Matricula: N384425 */ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Estruturas e variaveis para fila
const int tamanhoMAX = 100;

typedef struct FILA{
    int total;
    int inicio, fim;
    int clientes[tamanhoMAX];
};

//Variaveis para fila do caixa eletronico
int cronometro; 
int expediente;
int clientesAtendidos;
int tempoDeEspera;
int caixa[3];
int timeProxClient;
int tempoMarcado; 

//Funoes referente ao funcionamento de fila
void initFila(FILA *fila);
int filaIsEmpty(FILA *fila);
int filaIsFull(FILA *fila);
void insereFila(FILA *fila, int numero);
int tiraFila(FILA *fila);
void realoca(int &i);

//Funcoes referente a simulacao da fila do caixa eletronico
int clienteChegou();
int transacaoCliente();
char* convertTime(int segundos);
void simulacao();

int main(){
    int resp;
    int cont=1;
    do{
        system("cls");
        printf("---------------------------------------\nSIMULACAO %d - FILA DO CAIXA ELETRONICO",cont);
        simulacao();
        printf("\n1. Nova Simulacao\n0. Sair\n> ");
        setbuf(stdin,NULL);
        scanf("%d",&resp);
        cont++;
    }while(resp==1);
}

void simulacao(){
    FILA *clientes = (FILA *)malloc(sizeof(FILA));
    initFila(clientes);

    cronometro = 0; //Unidade de tempo em segundos
    expediente = 21600; //6h = 21600s
    clientesAtendidos=0;
    tempoDeEspera = 0;

    timeProxClient=0;
    tempoMarcado=0;

    for(int i=0;i<3;i++){
        caixa[i]=0;
    }
    
    srand((unsigned)time(NULL));

    //Ira executar ate atingir o horario do expediente ou quando ainda ter clientes na fila
    while(cronometro<=expediente||!filaIsEmpty(clientes)){
        
        //so ira inserir clientes se estiver dentro do expediente
        if(cronometro<=expediente){
            if(clienteChegou()){
                insereFila(clientes,cronometro);
                clientesAtendidos++;
            }
        }
        
        
        for(int x=0;x<3;x++){
            if(!filaIsEmpty(clientes)&&caixa[x]==0){
                
                int tempoChegada;
                tempoChegada = tiraFila(clientes);
                tempoDeEspera += cronometro-tempoChegada;
                caixa[x] = transacaoCliente(); //retorna o tempo de ocupacao para aquele caixa
                
            }
        }

        for(int y=0;y<3;y++){
            if(caixa[y]!=0){
                caixa[y]-=1; //-1 segundo
            }
        }

        cronometro++; //+1 segundo
    }
    cronometro--;
    //Resultados
    printf("\n---------------------------------------\nFIM DE EXPEDIENTE!\n");
    printf("Tempo de expediante: %s\n",convertTime(expediente));
    printf("Tempo de atendimento: %s\n",convertTime(cronometro));
    printf("Total de clientes: %d clientes\n",clientesAtendidos);
    printf("Tempo total de espera: %s segundos\n",convertTime(tempoDeEspera));
    printf("Tempo media de espera: %s\n\n",convertTime(tempoDeEspera/clientesAtendidos));
    free(clientes);
}

int clienteChegou(){
    //define se o proximo cliente virá num período de 1min
    int segundos;
    
    if(timeProxClient==0&&cronometro==0){
        segundos = (rand()%60)+1;
        timeProxClient = segundos;
        tempoMarcado = cronometro+timeProxClient;
        return rand()%2;
    }else if(cronometro==tempoMarcado){
        segundos = (rand()%60)+1;
        timeProxClient = segundos;
        tempoMarcado = cronometro+timeProxClient;
        return 1;
    }else{
        return 0;
    }
}

int transacaoCliente(){
    int qtdOperacoes = rand()%5+1;
    int tempoDeUso =0;
    int numOperacao;

    for(int i=0;i<qtdOperacoes;i++){
        numOperacao=rand()%5+1;
        
        if(numOperacao==1){
            tempoDeUso+=10;
        }
        if(numOperacao==2){
            tempoDeUso+=20;
        }
        if(numOperacao==3){
            tempoDeUso+=30;
        }
        if(numOperacao==4){
            tempoDeUso+=40;
        }
        if(numOperacao==5){
            tempoDeUso+=50;
        }
    }

    return tempoDeUso;
}

char* convertTime(int segundos){
    char* resultado = (char *)malloc(sizeof(char)*60);
    strcpy(resultado,"");
    char seg[5],min[5],hora[5];
    int hours, minutes, seconds;

    if(segundos<60){
        sprintf(seg,"%ds",segundos);
        strcat(resultado,seg);
    }else if(segundos<3600){
        minutes = segundos/60;
        seconds = segundos%60;
        sprintf(min,"%dmin%ds",minutes,seconds);
        strcat(resultado,min);
    }

    if(segundos>=3600){
        hours = segundos/3600;
        minutes = (segundos%3600)/60;
        seconds = (segundos%3600)%60;
        sprintf(hora,"%dh%dmin%ds",hours,minutes,seconds);
        strcat(resultado,hora);
    }
    
    return resultado;
}

void initFila(FILA *fila){
    fila->total=0;
    fila->inicio=0;
    fila->fim=0;
}

int filaIsEmpty(FILA *fila){
    return fila->total==0;
}

int filaIsFull(FILA *fila){
    return fila->total==tamanhoMAX;
}

void realoca(int &i){
    i++;
    if(i>tamanhoMAX-1){
        i=0;
    }
}

void insereFila(FILA *fila, int numero){
    if(!filaIsFull(fila)){
        fila->clientes[fila->fim]= numero;
        realoca(fila->fim);
        fila->total+=1;
    }
}

int tiraFila(FILA *fila){
    int tempoDeChegada;
    if(!filaIsEmpty(fila)){
        tempoDeChegada = fila->clientes[fila->inicio];
        realoca(fila->inicio);
        fila->total-=1;
        return tempoDeChegada;
    }
}