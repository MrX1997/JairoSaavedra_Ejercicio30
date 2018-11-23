rm *.png 
module load anaconda/python3

#cd $PBS_O_WORKDIR

gcc nladveccionserie.c -lm -o nlaserial
./nladveccionserie

#Corre la version paralela
gcc omp_non_linear_advection.c -fopenmp -o nla
./nladveccionparalelo
#include<omp.h>
gcc ompwalk.c -fopenmp -o ompwalk
./ompwalk >> datosWalkomp.txt

gcc walk.c -fopenmp -o walk
./walk >> datosWalk.txt

python3 Grafica.py
rm *.txt nla nlaserial ompwalk
