#!/bin/bash

#SBATCH -t 00:05:00
#SBATCH -n 1
#SBATCH -N 1
#SBATCH --job-name=DependentJob
#SBATCH -mail-type=end
#SBATCH -mail-user=tina.gholamy229@gmail.com
#SBATCH -p normal
#SBATCH -A tinagh

echo "Dependent job ran at: " `date`