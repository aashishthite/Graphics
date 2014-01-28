#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"
#include "constants.h"

class window;
class camera
{
	private:
		GLfloat origin_y_bias;
		GLfloat distance;
		GLfloat fov;
		GLfloat orient_lattitude;
		GLfloat orient_longitude;
		GLfloat orient_spin;
		GLfloat position_lattitude;
		GLfloat position_longitude;
		GLfloat nearplane;
		GLfloat farplane;
		bool draw;
		void DrawCamera_frustum(void);
		void DrawCamera_body(glm::mat4 modelview);
	public:
		camera(GLfloat Ybias, GLfloat Distance, GLfloat Fov, GLfloat O_lat, GLfloat O_long, GLfloat O_spin, GLfloat P_lat, GLfloat P_long, GLfloat Near, GLfloat Far, bool Draw);
		void SetupCamera(GLfloat AR, glm::mat4 & projection, glm::mat4 & modelview);
		void DrawCamera(void);
		void IncrementDistance(void);
		void DecrementDistance(void);
		void IncrementFov(void);
		void DecrementFov(void);
		void Increment_orient_lattitude(void);
		void Decrement_orient_lattitude(void);
		void Increment_orient_longitude(void);
		void Decrement_orient_longitude(void);
		void Increment_orient_spin(void);
		void Decrement_orient_spin(void);
		void Increment_position_lattitude(void);
		void Decrement_position_lattitude(void);
		void Increment_position_longitude(void);
		void Decrement_position_longitude(void);
		void IncrementNearplane(void);
		void DecrementNearplane(void);
		void IncrementFarplane(void);
		void DecrementFarplane(void);
		void FlipDraw(void);

		void SetFOV(GLfloat);
		void SetYBias(GLfloat);
		void SetDistance(GLfloat);
		void SetOrientLat(GLfloat);
		void SetOrientLong(GLfloat);
		void SetOrientSpin(GLfloat);
		void SetPosLat(GLfloat);
		void SetPosLong(GLfloat);

		GLfloat GetYBias(void);
		GLfloat GetDistance(void);
		GLfloat GetPosLat(void);
		GLfloat GetPosLong(void);
};