#Purpose: This bash script will sleep for 5 seconds

#!/bin/bash

#SBATCH -t 00:05:00
#SBATCH -n 1
#SBATCH -N 1
#SBATCH --job-name=ExampleJob
#SBATCH --mail-type=end
#SBATCH --mail-user=tina.gholamy229@gmail.com
#SBATCH  -p normal
##SBATCH -A tinagh


echo "Job started at: " `date` #the same as: $(date)
sleep 5
echo "Job finished at: " `date` #the same as: $(date)





