/*
	Program calculating gaps length between the different accelerating electric fields in a particle accelerator.
	Electric fields are generated between two "drift tubes" wich are at different potentials, so that gap length is
	the length of the drift tube.
	This length must be speed*(signal_period/2). Particles are therefore simulated to get their speed.

	Output file:

	aFrequency \t firstTubeLength \t secondTubeLength \t ...
	anotherfrequency \t firstTubeLength \t secondTubeLength \t ...
	...
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double particleNewSpeed(double particlePreviousSpeed, double particleMass, double particleWork){
		//Computes the new speed of a particle
		double c = 299792458.0;
		double v_I = particlePreviousSpeed;
		double m = particleMass;
		double W = particleWork;

		//Work-energy theorem (relativistic version)
		double v_F = c*sqrt(1-pow( (m*c*c)/( W+((1/(sqrt(1-(v_I*v_I)/(c*c)))-1))*(m*c*c)+(m*c*c) ) ,2.0));
		return v_F;
}

double distanceWithGap(double particleSpeed, double frequence, double gap){
	//Computes the length of a drift tube
	//Tube length must be 		l + gap = v * T/2    => 	l = v * T/2 -gap
	double l = particleSpeed * (1.0/frequence)/2.0 - gap;
	return l;
}

int main()
{
	printf("\t===== This program computes the speed of an electron under several electrostatic fields =====\n");

	//How many accelerations ?
	printf("Enter the number of successive accelerations: ");
	int nbAccelerations = 0;
	scanf("%d", &nbAccelerations);

	//Tension between two electrodes ?
	printf("Enter the tension (unit: V): ");
	int tension = 0;
	scanf("%d", &tension);
	int dTension = 0 - tension;

	//Signal frequence?
	printf("Enter the signal frequence (unit: Hz): ");
	float frequenceOrigin = 0;
	scanf("%f", &frequenceOrigin);

	//How much the frequency of this signal can sweep ?
	printf("Enter the range of frequency around the origin frequence that must be compute (unit: Hz): +-");
	float frequenceE = 0;
	scanf("%f", &frequenceE);

	float frequenceA = frequenceOrigin-frequenceE;
	float frequenceB = frequenceOrigin+frequenceE;

	printf("Enter the step between two frequencies (unit: Hz): ");
	float step = 0;
	scanf("%f", &step);

	//Gap between electrodes ?
	printf("Enter gap between electrodes (unit: m): ");
	double gap = 0.0;
	scanf("%lf", &gap);


	double initialSpeed = 0; // m/s.
	double particleMass = 9.109E-31; //Define particle mass kg.
	double particleTension = -1.602E-19; // C.

	double c = 299792458.0; // m/s.
	printf("\n");

	int j = 0;
	int i = 0;
	float frequence = 0; // Hz.

	remove("datas.txt");
	FILE* file = NULL;
	file = fopen("datas.txt", "w");


	for(j=0; j<(frequenceB-frequenceA)/step;j++){	//Each loop is in charge of ONE frequence

		frequence = frequenceA + j*step;
		fprintf(file, "%e", frequence);
		initialSpeed = 0.0;
			for(i=1; i<=nbAccelerations; i++)	//Each loop is in charge of ONE tube
			{
				double finalSpeed = particleNewSpeed(initialSpeed,particleMass,particleTension*dTension);
				fprintf(file, "\t%e", distanceWithGap(finalSpeed, frequence, gap));
				initialSpeed = finalSpeed;
			}
			fprintf(file, "\n");
	}
	return 0;
}
