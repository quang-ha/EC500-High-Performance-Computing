#! /bin/bash -l
# The -l specifies that we are loading modules
#
## Walltime limit
#$ -l h_rt=2:00:00
#
## Give the job a name.
#$ -N vec_add
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

# Print the machine name, since we aren't using MPI
echo "Machine name ${HOSTNAME} "

# Set OMP_NUM_THREADS. In this case, NSLOTS is the number of cores.
export OMP_NUM_THREADS=$NSLOTS

# Run the executable
./timing_vector_omp

exit

