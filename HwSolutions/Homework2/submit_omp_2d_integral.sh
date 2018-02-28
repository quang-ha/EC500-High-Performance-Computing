#! /bin/bash -l
# The -l specifies that we are loading modules
#
## Walltime limit
#$ -l h_rt=0:10:00
#
## Give the job a name.
#$ -N int2dOMP
#
## Redirect error output to standard output
#$ -j y
#
## What project to use. "paralg" is the project for the class
#$ -P paralg
#
## Ask for 4 cores
#$ -pe omp 4

# Want more flags? Look here:
# http://www.bu.edu/tech/support/research/system-usage/running-jobs/submitting-jobs/

# Load the correct modules
module load gcc/5.3.0  # compiler
module load mpich/3.2  # consistent mpi compile

# Immediately form fused output/error file, besides the one with the default name.
exec >  ${SGE_O_WORKDIR}/${JOB_NAME}-${JOB_ID}.scc.out 2>&1

echo "Hello from process ${HOSTNAME}"

export OMP_NUM_THREADS=${NSLOTS}
./integrate_2d_omp_timing

exit

