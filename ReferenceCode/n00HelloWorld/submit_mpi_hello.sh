#!/bin/sh
#
# Ask for nodes with 4 cores, 8 cores total (so 2 nodes)
#$ -pe mpi_4_tasks_per_node 8
#
### What project to use. This is the project for the class.
#$ -P paralg
#
# Invoke mpirun.
# SGE sets $NSLOTS as the total number of processors (8 for this example) 
#
mpirun -np $NSLOTS ./mpi_hello

exit

