#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NPROS     5
#define QUANTUM   3

struct parametros{
  char proceso[10];
  char s_comienzo[50];
  char s_finalizacion[50];
  int t_ejecucion;
  int t_llegada;
  int t_comienzo;
  int t_finalizacion;
  int t_retorno;
  int t_espera;
};

/*
int countTimeComplete(struct parametros *params)
@param struct parametros *params
@brief cuenta el tiempo de ejecucion completo de todos los procesos 

*/
int countTimeComplete(struct parametros *params);

/*
int indexMaxFin(struct parametros *params)
@param struct parametros *params
@brief busca el indice del ultimo proceso ejecutado a traves del maximo valor de tiempo de finalizacion
*/
int indexMaxFind(struct parametros *params);

/*
void writeSpace(struct parametros *params)
@param struct parametros *params
@brief inicializa el char
*/
void writeSpace(struct parametros *params);

/*
void timeRestComplete(int *aux,int *vector,int n)
@param aux parametro por referencia del contador de tiempo de los procesos realizados
@param *vector pasa el valor de un elemento del vector
@param n tiempo de ejecucion que le resta a un proceso
@brief asigna por referencia a aux, contabiliza el tiempo total ya ejecutado por los procesos
*/
void timeRestComplete(int *aux,int *vector,int n);

int main(){
  struct parametros params[NPROS];

  //ind obtiene el indice del proceso reciente ejecutado
  //t_complete_alg -> lleva el tiempo completo del round robin de todos los procesos
  int cont=0,i=0,j=0,t_complete_alg=0,ind;
  char s_num[10];

  strcpy(params[0].proceso,"A");
  params[0].t_ejecucion = 8;
  params[0].t_llegada = 0;

  strcpy(params[1].proceso,"B");
  params[1].t_ejecucion = 4;
  params[1].t_llegada = 1;

  strcpy(params[2].proceso,"C");
  params[2].t_ejecucion = 9;
  params[2].t_llegada = 2;

  strcpy(params[3].proceso,"D");
  params[3].t_ejecucion = 5;
  params[3].t_llegada = 3;

  strcpy(params[4].proceso,"E");
  params[4].t_ejecucion = 2;
  params[4].t_llegada = 4;

  int t_rest_exec[5],p_realizado[5];
  int complete = countTimeComplete(params);

  for (i = 0; i < NPROS; i++){
    t_rest_exec[i] = params[i].t_ejecucion;//copia el tiempo de ejecucion de un proceso a t_rest_exec
    params[i].t_comienzo = 0;
    params[i].t_finalizacion = 0;
    p_realizado[i] = 0;//si un proceso tiene 0 en su indice, es que aun tiene por ejecutarse
  }
  writeSpace(params);

  printf("Proceso\t    T_ejecucion\t   T_llegada\tT_comienzo\tT_finalizacion\tT_retorno\tT_espera\n");
  printf("-----------------------------------------------------------------------------------------------------\n");
  i=0;

    while(t_complete_alg < complete){
      if(t_complete_alg > 0)ind = indexMaxFind(params);

      //asigna a params[i].t_comienzo el tiempo de finalizacion del anterior proceso ejecutado
      if((i == 0) && (t_complete_alg > 0))params[0].t_comienzo = params[ind].t_finalizacion;
      if(i > 0)params[i].t_comienzo = params[ind].t_finalizacion;
      
      //si t_rest_exec es mayor que el quantum
      if(t_rest_exec[i] > QUANTUM){

        sprintf(s_num,"%d",params[i].t_comienzo);
        strcat(params[i].s_comienzo,s_num);

        strcat(params[i].s_comienzo,"-");

        timeRestComplete(&t_complete_alg,&t_rest_exec[i],QUANTUM);
        params[i].t_finalizacion = t_complete_alg;

        sprintf(s_num,"%d",params[i].t_finalizacion);
        strcat(params[i].s_finalizacion,s_num);
        strcat(params[i].s_finalizacion,"-");

      }else{
        if(t_rest_exec[i] > 0){
          sprintf(s_num,"%d",params[i].t_comienzo);
          strcat(params[i].s_comienzo,s_num);

          cont = t_rest_exec[i];
          timeRestComplete(&t_complete_alg,&t_rest_exec[i],cont);
          params[i].t_finalizacion = t_complete_alg;

          sprintf(s_num,"%d",params[i].t_finalizacion);
          strcat(params[i].s_finalizacion,s_num);
        }
      }
      if(t_rest_exec[i] == 0)p_realizado[i] = 1;
      i++;
      if(i == NPROS)i=0;
    }

  for (i = 0; i < NPROS; i++){
    params[i].t_retorno = params[i].t_finalizacion - params[i].t_llegada;
    params[i].t_espera = params[i].t_retorno - params[i].t_ejecucion;
    printf("%s\t\t%d\t\t%d\t%s\t\t%s\t\t%d\t\t%d\n",params[i].proceso,params[i].t_ejecucion,params[i].t_llegada
      ,params[i].s_comienzo,params[i].s_finalizacion,params[i].t_retorno,params[i].t_espera);
  }

  return 0;

}

int countTimeComplete(struct parametros *params){
  int aux=0;
  for (int i = 0; i < NPROS; i++){
    aux += params[i].t_ejecucion;
  }
  return aux;
}

int indexMaxFind(struct parametros *params){
  int aux = params[0].t_finalizacion,index=0;
  for (int i = 1; i < NPROS; i++){
    if(aux < params[i].t_finalizacion){
      aux = params[i].t_finalizacion;
      index=i;
    }
  }
  return index;
}

void writeSpace(struct parametros *params){
  for (int i = 0; i < NPROS; i++){
    strcpy(params[i].s_comienzo,"");
    strcpy(params[i].s_finalizacion,"");
  }
}

void timeRestComplete(int *aux,int *vector,int n){
  for (int i = 0; i < n; i++){
    *vector = *vector - 1;
    (*aux)++;
  }
}