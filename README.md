# particlesAccelerator
Program calculating drift tubes length in a electron accelerator.

Program calculating gaps length between the different accelerating electric fields in a particle accelerator.
	Electric fields are generated between two "drift tubes" wich are at different potentials, so that gap length is
	the length of the drift tube.
	This length must be speed*(signal_period/2). Particles are therefore simulated to get their speed.
  
Output file:
	aFrequency \t firstTubeLength \t secondTubeLength \t ...
	anotherfrequency \t firstTubeLength \t secondTubeLength \t ...
	...
