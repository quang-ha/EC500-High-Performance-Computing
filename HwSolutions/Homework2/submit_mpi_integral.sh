#! /bin/bash -l
# The -l specifies that we are loading modules
#
## Walltime limit
#$ -l h_rt=0:10:00
#
## Give the job a name.
#$ -N intSinMPI
#
## Redirect error output to standard output
#$ -j y
#
## What project to use. "paralg" is the project for the class
#$ -P paralg
#
## Ask for nodes with 4 cores, 4 cores total (so 1 node)
#$ -pe mpi_8_tasks_per_node 8

# Want more flags? Look here:
# http://www.bu.edu/tech/support/research/system-usage/running-jobs/submitting-jobs/

# Load the correct modules
module load gcc/5.3.0  # compiler
module load mpich/3.2  # consistent mpi compile

# Immediately form fused output/error file, besides the one with the default name.
exec >  ${SGE_O_WORKDIR}/${JOB_NAME}-${JOB_ID}.scc.out 2>&1

# Invoke mpirun.
# SGE sets $NSLOTS as the total number of processors (8 for this example) 
mpirun -np $NSLOTS ./integrate_sin_timing

exit

