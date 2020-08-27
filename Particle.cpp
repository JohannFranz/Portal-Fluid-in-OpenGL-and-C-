#include "Particle.h"


Particle::Particle(void)
: m_IsActive(true)
, m_Acceleration(0.0f,-10.0f,0.0f)
{
}

Particle::Particle(const vec3&  position, const vec3&  velocity)
: m_IsActive(true)
, m_Acceleration(0.0f,-10.0f,0.0f)
{
	init(position, velocity);
}

Particle::~Particle(void)
{
}

void Particle::init(const vec3&  position, const vec3&  velocity)
{
	m_Position = position;
	m_Velocity = velocity;
}

void Particle::update(double time)
{
	m_Velocity += m_Acceleration*(float)time;
	m_Position += m_Velocity*(float)time;

	if (m_Position.y < 0.0f) 
		m_IsActive = false;
}

void Particle::setAcceleration(const vec3& acceleration)
{
	m_Acceleration = acceleration;
}

void Particle::setVelocity(const vec3& velocity)
{
	m_Velocity = velocity;
}

void Particle::setPosition(const vec3& position)
{
	m_Position = position;
}

void Particle::setActive(bool active)
{
	m_IsActive = active;
}

const vec3 Particle::getPosition()
{
	return m_Position;
}

const bool Particle::isActive()
{
	return m_IsActive;
}