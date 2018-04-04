#pragma once
#ifndef TWOMAX_H
#define TWOMAX_H
#include<string>
#include<time.h>
#include<algorithm>




using namespace std;
 typedef struct // structure of the data it holds the all the values
 {
	vector<vector<bool>>Population;
	vector<double>FitnessValues;
	vector<vector<bool>>Populationforcrossover;
	 vector<vector<bool>>CrossMutatePopulation;
}Chromostruct;

 class Knapsackdata// class for holding the data
{public:
	
     	int populationsize;
		int individualsize;
	   double tau;
	   double CrossoverProbablity;
	   double MutationProbablity;	
	int Dlimit;
};
 class Initialize// class of processing of GA
{
	public:	
	void FitnessComputation(Knapsackdata & data, Chromostruct & val);// fitness computation
	void GenerateChromo(Knapsackdata & data, Chromostruct & val);// Generate chromosomes
	void Tournament(Knapsackdata & data, Chromostruct & val);//Tournament selection
	void CrossOver(Knapsackdata & data, Chromostruct & val,int NumofPoint);// Cross over
	void OverlapSelection(Knapsackdata & data, Chromostruct & val);//overlap selection
	void SharingMethod(Knapsackdata & data, Chromostruct & val);// sharing method hammind distance
	void SaveResults(Knapsackdata & data, Chromostruct & val,ofstream & myfile);// store the results into text file
};
 void Initialize::SaveResults(Knapsackdata & data, Chromostruct & val,ofstream & myfile)
 {
	
	 /*.............Compute the normal Fitness of from the population...............*/
	 vector<double>goalfitness;
	for(int i=0;i<data.populationsize;i++)
	{
		int zeros=0,ones=0;
		for(int j=0;j<data.individualsize;j++)
		{
			if (val.Population[i][j]==false)
				zeros++;// count xi=0 
			else
				ones++;// count xi=1 which is count individuals
		}
		if (ones>zeros)
		goalfitness.push_back(ones);
		else
			goalfitness.push_back(zeros);	
	}
 /*.............Compute the normal Fitness of from the population...............*/
/*.............Store results...............*/
	 double sum=0;
	 double maximum = 0;
	 for(int i=0;i<goalfitness.size();i++)
	{		sum+=goalfitness[i];
		   if(goalfitness[i]>maximum)// get the maximum
		    maximum=goalfitness[i];
	 }

	 cout<<maximum<<" "<<sum/goalfitness.size()<<endl;// show output
	 myfile<<maximum<<" "<<sum/goalfitness.size()<<endl;// store the file 
/*.............Store results...............*/
 }

 inline double HummingDistance(vector<bool>seq1,vector<bool>seq2,int D)
{
	double hDistance = 0;
	
	for(int i=0; i<seq1.size(); i++) 
		if(seq1[i] != seq2[i]) //count score if it is not matching
			hDistance++; 
	
	if (hDistance>D)// if Distance exceds 30 then we setup to 0
		hDistance=0;
	else 
		hDistance=1-(hDistance/D);//if Distance does not exceds 30 then we select it
	
	return hDistance ; 
}
 void  Initialize::SharingMethod(Knapsackdata & data, Chromostruct & val)
 {
	 for(int i=0;i<data.populationsize;i++)
	{
			double zeta=0;
			for(int j=0;j<data.populationsize;j++)
			{
					double hamming;
					hamming=HummingDistance(val.Population[i],val.Population[j],data.Dlimit);//Hamming distance check mismatch and add the score 
					if(i !=j )
					zeta=zeta+hamming;// sum up the humming distance expect the identical that is why i is not equal to j		
			}		
			if (zeta==0)// if zeta is zero then continue with old fitness value
			{	
			val.FitnessValues[i]=val.FitnessValues[i];
	
			}else //if not the we modify the fitness value f'=f/zeta
			{ 
				val.FitnessValues[i]=val.FitnessValues[i]/(double)zeta;
			}
			
	}
}
 void Initialize::OverlapSelection(Knapsackdata & data, Chromostruct & val)
 {
	 
	 vector<int> map(val.FitnessValues.size());
	// we sort the population for overlap selection. we use the fitness values for sorting
	for(int i=0;i<val.FitnessValues.size();i++)
      map[i]=i;

	sort( map.begin(),map.end(), [&](int x,int y){return val.FitnessValues[x]>val.FitnessValues[y];}); // we get the index of population

	vector<double>sortedftiness;
   vector<vector<bool>>sortedpopulation;
	 for(int i=0;i<data.populationsize;i++)
	 {
		 sortedftiness.push_back(val.FitnessValues[map[i]]);
		 sortedpopulation.push_back(val.Population[map[i]]);// we map the index of population to get the real one
	 }
	 val.Population=sortedpopulation;
	 val.FitnessValues=sortedftiness;
	 // Sorted population and fitness

	 double portion=(1-data.tau)*data.populationsize;
	 for(int i=portion;i<data.populationsize;i++)
	 {
		val.Population[i]= val.CrossMutatePopulation[i];//Worse (1- ¥ó) portion of the population are replaced with some of offspring

	 }

 }
bool wayToSort(int i, int j) { return i < j; }

void Initialize::CrossOver(Knapsackdata & data, Chromostruct & val, int NumofPoint)// Cross over 
{
vector<vector<bool>>Crossed;
val.CrossMutatePopulation.clear();
	for(int i=0;i<val.Populationforcrossover.size();i=i+2)
	{	
		vector<int>position;
		for(int e=0;e<NumofPoint;e++)
		{
			bool isav=0;
			int ps=rand() % data.individualsize;
			while (1)
			{
			for(int f=0;f<position.size();f++)
				if(ps==position[f])
					isav=1;					
		     	else
				isav=0;
			ps=rand() % data.individualsize;// select random position for the crossover
			if (isav==0)
				break;
			}
			position.push_back(ps);		
		}
	
		std::sort(position.begin(), position.end(), wayToSort);// we sort the cross over point locations
		for(int j=i;j<i+2;j++)
		Crossed.push_back(val.Populationforcrossover[j]);

		vector<bool>offspring1,offspring2;
		double x= (((double) rand() / (RAND_MAX)));// Random from 0-1 check with crossover probaliity
		
		if (x<=data.CrossoverProbablity)//Do. 1 point crossover if prob less than 1.0
		{
					    int m=Crossed[0].size()/(NumofPoint+1);// divided the chromosomes
						double Pm= (((double) rand() / (RAND_MAX)));
										
						for(int p=0;p<Crossed[0].size();p++)
						{
							if(p<position[0])
							{
								offspring1.push_back(Crossed[0][p]);// flip the strings
								offspring2.push_back(Crossed[1][p]);// flip the strings
							}
							else if(p>=position[0] )
							{
								offspring1.push_back(Crossed[1][p]);// flip the strings
								offspring2.push_back(Crossed[0][p]);// flip the strings
					    	}
			}

			if(x<=data.MutationProbablity)// do mutation if probability falls from 0.001
				{
					int pos=rand() % (Crossed[0].size());									
					offspring1[pos]=~offspring1[pos];// flip the bits
			    	offspring1[pos]=~offspring1[pos];		// flip the bits
				}
												
				Crossed[0]=offspring1;
				Crossed[1]=offspring2;
			}
			val.CrossMutatePopulation.push_back(Crossed[0]);
			val.CrossMutatePopulation.push_back(Crossed[1]);
	}
}
void Initialize::Tournament(Knapsackdata & data, Chromostruct & val)// Tournament selection 
{
	val.Populationforcrossover.clear();
	    int x=0;
		for(int m=0;m<val.FitnessValues.size();m++)
		{
			while(1)
			{
				x=rand() % (val.FitnessValues.size());	
				 if(x !=m)
					 break;
			}
			if (val.FitnessValues[m]<val.FitnessValues[x])// Pair wise tournament check for the best
				{
					val.Populationforcrossover.push_back(val.Population[x]);
				}else
				{
					val.Populationforcrossover.push_back(val.Population[m]);
				}
		}
}
void Initialize::FitnessComputation(Knapsackdata & data,Chromostruct & val)// Population fitness computation
{
	val.FitnessValues.clear();
	for(int i=0;i<data.populationsize;i++)
	{
		int zeros=0,ones=0;
		for(int j=0;j<data.individualsize;j++)
		{
			if (val.Population[i][j]==false)
				zeros++;// count xi=0 
			else
				ones++;// count xi=1 (it counts individuals)
		}
		if (ones>zeros)//f(x)=max{u(x),u(x)}
			val.FitnessValues.push_back(ones);
		else
			val.FitnessValues.push_back(zeros);	
	}
	
}
void Initialize::GenerateChromo(Knapsackdata & data, Chromostruct & val)// generate the chromosomes 
{
	val.Population.clear();
	val.Population.reserve(data.populationsize);
	 srand ( time(NULL) );
	for(int i=0;i<data.populationsize;i++)
	{
		vector<bool>rnd;
		for (int j=0;j<(data.individualsize);j++)
			rnd.push_back(rand()%2);// Generate random bianary values 0 or 1 for total number item size			
		val.Population.push_back(rnd);// stores the chromosomes 		
	}
}
#endif TWOMAX_H





