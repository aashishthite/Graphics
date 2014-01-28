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
		GLint distance;
		GLint fov;
		GLint orient_lattitude;
		GLint orient_longitude;
		GLint orient_spin;
		GLint position_lattitude;
		GLint position_longitude;
		GLint nearplane;
		GLint farplane;
		bool draw;
		void DrawCamera_frustum(void);
		void DrawCamera_body(glm::mat4 modelview);
	public:
		camera(GLint Distance, GLint Fov, GLint O_lat, GLint O_long, GLint O_spin, GLint P_lat, GLint P_long, GLint Near, GLint Far, bool Draw);
		void SetupCamera(window* win, glm::mat4 & projection, glm::mat4 & modelview);
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
};