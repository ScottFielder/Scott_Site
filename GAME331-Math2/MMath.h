#pragma once
#include "Matrix.h"
///  A class devoted to graphics related Math - OpenGL style
namespace  GAME_Lib {

	class MMath {
	public:
		static Matrix rotate(float angle, float x, float y, float z);
		static Matrix translate(float x, float y, float z);
		static Matrix scale(float x, float y, float z);
		static Matrix perspective(float fovy, float aspect, float zNear, float zFar);


		/// It was just derived a different way, test it if you wish
		///static Matrix perspectiveOld(float fFov, float fAspect, float zMin, float zMax);


		static Matrix orthographic(float xMin, float xMax,
								   float yMin, float yMax,
								   float zMin, float zMax);
		static Matrix lookAt(float eyeX, float eyeY, float eyeZ,
							 float atX,  float atY,  float atZ,
							 float upX,  float upY,  float upZ);
		static Matrix lookAt(const Vec3& eye, const Vec3& at, const Vec3& up);
							
		static Matrix transpose(const Matrix m);
		static Matrix inverse(const Matrix m);
	};

}