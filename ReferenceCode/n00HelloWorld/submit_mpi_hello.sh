#! /bin/bash
#
## Walltime limit
#$ -l h_rt=2:00:00
#
## Give the job a name.
#$ -N submit_hello
#
## Redirect error output to standard output
#$ -j y
#
## What project to use. "paralg" is the project for the class
#$ -P paralg
#
## Ask for nodes with 4 cores, 8 cores total (so 2 nodes)
#$ -pe mpi_4_tasks_per_node 8 


# Immediately form fused output/error file, besides the one with the default name.
#exec >  ${SGE_O_WORKDIR}/${JOB_NAME}-${JOB_ID}.scc.out 2>&1

# Invoke mpirun.
# SGE sets $NSLOTS as the total number of processors (8 for this example) 
mpirun -np $NSLOTS ./mpi_hello

exit

