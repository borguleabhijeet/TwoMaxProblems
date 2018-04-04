# TwoMaxProblems
This report we present about Two Max problem. As we have learned about maintaining the diversity of population.  
In our problem, the given data is as follows: -
Individual size=50;
Population size=100;
Crossover probability=1.0 it means we did crossover to every parents.
The mutation probability=0.01
The humming distance threshold=30

1. Initialize population: Generate chromosomes
A. We generate 0-1 chromosomes. The individual size is 50 
B. The population size 100

2. Check the Fitness: Check the fitness of the generated population
A. Based on counting 1’s and 0’s occurrence individual we select the best for fitness


3. Selection of population: Selection procedure is Tournament selection
A. The pair wise tournament generates the new populations base on fitness values

4. Cross Over: 1-point crossover
A. After the selection step 3, we apply one-point crossover

5. Overlap Selection/Elitism:
A. We sort the population based on fitness in descending order.
B. We keep 0.5 portion of the of population and rest we replace it with new population after step 4.

6. Sharing Method:
A. We generate the hamming distance of between population. If the hamming distance is greater than 30 we set it 0 
B. Then we modify the fitness value by summing over hamming distance.
C. While summing over hamming distance we skip identical individuals.
7. Go back to Tournament Selection
A. The fitness and population is continued with selection procedure.
Flow Chart: 

