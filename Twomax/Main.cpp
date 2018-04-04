#include<iostream>
#include<vector>
#include<fstream>
#include <string>
#include "TwoMax.h"
#include <math.h>
#include<time.h>

using namespace std;
// Here we are going to show you an implimentation of the 0-1 Knapsack problem 

//
int main()// main funtion
{
	/*.............Initiliaze the structure.............*/
	Knapsackdata  obj;// Create constructor of the class which holds the parameters of the GA
	Initialize init;
	obj.populationsize=100;//Population Size is 100 and each chromosomes has binary value which is 0 & 1 for 50 times.
	obj.individualsize=50;	
	obj.CrossoverProbablity=1.0;//Set up the cross over probability 
	obj.MutationProbablity=0.01;	
	int numberofpoint=1;//One Point Cross over
	obj.tau=0.5;
	obj.Dlimit=30;
   cout<<"Two Max Problems"<<endl;
	Chromostruct param;
	/*.............Initiliaze the population.............*/

	init.GenerateChromo(obj,param);// Generate Initial Chromosomes to individual length
	init.FitnessComputation(obj,param);// compute the fitness
	int iteration=0;
	cout<<"Please see the output file at the base directory after iteration"<<endl;
	ofstream myfile("Output.txt");// store the output results the first column is fitness and second column is average fitness
	/*.................GA begins..............................*/
	while(iteration<100)// iterate until 300
	{

	init.Tournament(obj,param);// Tournament selection we setup the 
	init.CrossOver(obj,param,numberofpoint);//Peform cross over of two parents and create two offespring it has 1 point cross over;
	init.OverlapSelection(obj,param);// Perform the overlap selection on generated offspring, we keep 0.5 portion with old population and replace it with new population.
	init.FitnessComputation(obj,param);// compute the fitness
	init.SharingMethod(obj,param);// The sharing method used to 
	init.SaveResults(obj,param,myfile);// Save the Results
	iteration++;

	}
	/*.................GA ends..............................*/
	for(int i=0;i<10;i++)// print ot 10 first populations
	{
		for(int j=0;j<obj.individualsize;j++)	
		cout<<param.Population[i][j];
		cout<<endl;
	}
	myfile.close();


	cin>>iteration;
	return 0;
}
