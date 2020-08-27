#pragma once

enum
{
	NUM_OF_PARTICLES = 10
}; 

enum ParticleStatus
{
	showParticle = 0,
	showQuad = 1,
	showFluidLinear = 2,
	showFluidExponential = 3,

};

//integrate 120 times per second
const double	MIN_TIME_DELTA = 1/120;

const float		ZOOM_FACTOR = 0.3f;