#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<omp.h>

double *x;
double *u;
double *ufinal;
int i;
double L;
int N; 
void print(char *name)
{
	FILE *output = fopen(name, "w+");
	for(i=0;i<N;i+=1) {
            fprintf(output, "%f %f\n",x[i],ufinal[i]);
			}
	fclose(output);
}

void initial(double delta_x)
{


    L = 4.0;
    N = ((int)(L/delta_x))+ 1;
    x = malloc(sizeof(double)*N);
    u = malloc(sizeof(double)*N);
    ufinal = malloc(sizeof(double)*N);
    for(i=0; i<N;i++){
        x[i] = delta_x*i;   
        u[i] = 0;
        if(x[i] < 2.0){
            u[i] = 1.0;
        }
        ufinal[i] = u[i];
    }
}

double flux(double uin)
{
    return 0.5 * uin*uin;
}



void Lax(double t_max, double delta_t, double delta_x){
    double F;
    int j;
    int N_t = (int) (t_max/delta_t);   
	int i;
	#pragma omp parallel for 
    for(i=0;i<N_t;i+=1){
        for(j=1;j<N-1;j+=1){
            ufinal[j] = 0.5*(u[j+1]+u[j-1]);
            ufinal[j]-= (0.5*delta_t/delta_x)*(flux(u[j+1]) - flux(u[j-1]) );
        }
        for(j=0;j<N;j+=1){
            u[j] = ufinal[j];
        }
    }
}




int main(int argc, char *argv[])
{
     initial(0.05);
     char filename[80];
	
    double tRealMax = 2.0;
    double tactual;
    double dx = 0.05;
    double dt = 0.5*dx;
    int conteo=0;
    while(tactual <= tRealMax){
     initial(dx);
     Lax(tactual,dt,dx);
     sprintf(filename,"datp%d.txt",conteo);
     print(filename);
        }
        
     tactual += 0.5;   
     conteo++;
return 0;
} 
