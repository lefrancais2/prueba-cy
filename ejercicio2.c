#include <stdio.h>
#include <string.h>

#define NPROS 5

struct parameters{
  char proceso[10];
  int t_ejecucion;
  int t_llegada;
  int t_comienzo;
  int t_finalizacion;
  int t_retorno;
  int t_espera;
};

/*
int shorterExecutionTime(struct parameters *vector)
@param *vector vector de tipo srcut parameters
@brief calcular el menor tiempo de ejecucion que no tenga realizado su proceso
*/
int shorterExecutionTime(struct parameters *vector);

int main() {
  struct parameters params[NPROS];
  int i=0,count=1,index,before,ind[NPROS];

  strcpy(params[0].proceso,"A");
  params[0].t_ejecucion = 8;
  params[0].t_llegada = 0;
  params[0].t_comienzo = 0;
  params[0].t_finalizacion = params[0].t_ejecucion;
  params[0].t_retorno = params[0].t_finalizacion;
  params[0].t_espera = 0;

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

  for (i = 1; i < NPROS; i++){
    params[i].t_comienzo = 0;
  }
printf("acabado\n");
  printf("Proceso | t_ejecucion | t_llegada | t_comienzo | t_finalizacion | t_retorno | t_espera\n");
  printf("---------------------------------------------------------------------------------------\n");

  ind[0] = 0;
  while(count < NPROS){
    index = shorterExecutionTime(params);
    if(count == 1){
      params[index].t_comienzo = params[0].t_finalizacion;
    }else{
      params[index].t_comienzo = params[before].t_finalizacion;
    }
    params[index].t_finalizacion = params[index].t_comienzo + params[index].t_ejecucion;
    before = index;
    ind[count]=index;
    count++;
  }

  for (i = 0; i < NPROS; i++) {
    index = ind[i];
    params[index].t_retorno = params[index].t_finalizacion - params[index].t_llegada;
    params[index].t_espera = params[index].t_retorno - params[index].t_ejecucion;
    printf("    %s\t\t%d\t   %d\t\t%d\t\t%d\t    %d\t\t%d\n",params[index].proceso,params[index].t_ejecucion,params[index].t_llegada,params[index].t_comienzo,
      params[index].t_finalizacion,params[index].t_retorno,params[index].t_espera);
  }

  return 0;
}

int shorterExecutionTime(struct parameters *vector){
  int menor,index=1;
  for (int i = 1; i < NPROS; i++){
    if(vector[i].t_comienzo == 0){
      menor=vector[i].t_ejecucion;
      index = i;
      for (int j = 1; j < NPROS; j++){
        if((menor > vector[j].t_ejecucion) && (vector[j].t_comienzo == 0)){
          menor = vector[j].t_ejecucion;
          index = j;
        }
      }
    }
  }
  return index;
}