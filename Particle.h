#pragma once

#include "glm.hpp"

using glm::vec3;

class Particle
{
public:
	Particle();
	Particle(const vec3&  position, const vec3&  velocity);
	~Particle(void);

	void		init(const vec3& position, const vec3& velocity);
	void		update(double time);
	
	void		setActive(bool active);
	void		setAcceleration(const vec3& acceleration);
	void		setVelocity(const vec3& velocity);
	void		setPosition(const vec3& position);

	const vec3	getPosition();
	
	const bool	isActive();

private:
	
	vec3		m_Position;
	vec3		m_Velocity;
	vec3		m_Acceleration;

	bool		m_IsActive;

};

