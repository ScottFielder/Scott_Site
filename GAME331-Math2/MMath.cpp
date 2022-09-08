#include "VMath.h"
#include "MMath.h"
using namespace GAME_Lib;


///Tested Feb 2 2013 SSF
 Matrix MMath::rotate(float angle, float x, float y, float z){
	float cosang, sinang, cosm;
	Matrix m;
	Vec3 rotAxis(x,y,z);
	rotAxis = VMath::normalize(rotAxis);
	
	angle *= DEGREES_TO_RADIANS;

	cosang = cos(angle);
	sinang = sin(angle);
	cosm = (1.0f - cosang);

	m[0] = (rotAxis.x * rotAxis.x * cosm) + cosang;
	m[1] = (rotAxis.x * rotAxis.y * cosm) + (rotAxis.z * sinang);
	m[2] = (rotAxis.x * rotAxis.z * cosm) - (rotAxis.y * sinang);
	m[3] = 0.0;
	m[4] = (rotAxis.x * rotAxis.y * cosm) - (rotAxis.z * sinang);
	m[5] = (rotAxis.y * rotAxis.y * cosm) + cosang;
	m[6] = (rotAxis.y * rotAxis.z * cosm) + (rotAxis.x * sinang);
	m[7] = 0.0;
	m[8] = (rotAxis.x * rotAxis.z * cosm) + (rotAxis.y * sinang);
	m[9] = (rotAxis.y * rotAxis.z * cosm) - (rotAxis.x * sinang);
	m[10] =(rotAxis.z * rotAxis.z * cosm) + cosang;
	m[11] = 0.0;
	m[12] = 0.0;	
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
	return m;
}

/// As derived in GAME331 
Matrix MMath::perspective(float fovy, float aspect, float zNear, float zFar){
	float cot = 1.0f / tan(fovy* 0.5f * DEGREES_TO_RADIANS);
	/// Don't forget this looks row centric but it really is a column matrix - right-hand rule rules
	return Matrix(cot/aspect, 0.0f,   0.0f,                             0.0f,
			      0.0f,		  cot,	  0.0f, 	                        0.0f,
			      0.0f,       0.0f,   (zNear+zFar)/(zNear-zFar),       -1.0,
			      0.0,        0.0,    (2.0f*zNear*zFar)/(zNear-zFar),   0.0);
}

/*** This is how I derived it long ago, but the math works out the same!
Matrix MMath::perspectiveOld(float fFov, float fAspect, float zMin, float zMax){
	Matrix m;
	float yMax = zMin * tanf(fFov * 0.5f * DEGREES_TO_RADIANS);
	float yMin = -yMax;
	float xMin = yMin * fAspect;
	float xMax = -xMin;   
	m[0] = (2.0f * zMin) / (xMax - xMin);
	m[5] = (2.0f * zMin) / (yMax - yMin);
	m[8] = (xMax + xMin) / (xMax - xMin);
	m[9] = (yMax + yMin) / (yMax - yMin);
	m[10] = -((zMax + zMin) / (zMax - zMin));
	m[11] = -1.0f;
	m[14] = -((2.0f * (zMax*zMin))/(zMax - zMin));
	m[15] = 0.0f;
	return m;
}***/



/// Not tested but I'll bet I'm right
Matrix MMath::orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax){
	Matrix m;
	m[0] = 2.0f / (xMax - xMin);
	m[5] = 2.0f / (yMax - yMin);
	m[10] = -2.0f / (zMax - zMin);
	m[12] = -((xMax + xMin) / (xMax - xMin));
	m[13] = -((yMax + yMin) / (yMax - yMin));
	m[14] = -((zMax + zMin) / (zMax - zMin));
	m[15] = 1.0f;
	return m;
}

/// At first glance, it might look like this matrix 
/// is written left-handed or transposed, it has not. 
/// Remember how memory is layed out. It is still column based.  
///Tested Feb 1 2013 SSF  
Matrix MMath::translate(float x, float y, float z){
	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, 1.0f, 0.0f,
				  x,    y,    z,	1.0f);  
}

Matrix MMath::scale(float x, float y, float z){
	return Matrix(x,	0.0f, 0.0f, 0.0f,
				  0.0f, y   , 0.0f, 0.0f,
				  0.0f, 0.0f, z,    0.0f,
				  0.0f, 0.0f, 0.0f,	1.0f); 
}

///Tested Feb 1 2013 SSF
Matrix MMath::lookAt(float eyeX, float eyeY, float eyeZ,
			float atX, float atY, float atZ,
			float upX, float upY, float upZ){

	

	Vec3 at(atX,atY,atZ);
	Vec3 up(upX,upY,upZ);
	Vec3 eye(eyeX,eyeY,eyeZ);

	Matrix result;

	Vec3 forward = VMath::normalize(at - eye);
	up = VMath::normalize(up);
	Vec3 side = VMath::normalize( VMath::cross(forward,up));
	up = VMath::cross(side,forward);

	result[0] = side.x;
	result[1] = side.y;
	result[2] = side.z;
	result[3] = 0.0;

	result[4] = up.x;
	result[5] = up.y;
	result[6] = up.z;
	result[7] = 0.0;

	result[8]  = -forward.x;
	result[9]  = -forward.y;
	result[10] = -forward.z;
	result[11] = 0.0;
	
	result[12] = -VMath::dot(side,eye);	
	result[13] = -VMath::dot(up,eye);
	result[14] =  VMath::dot(forward,eye);
	result[15] = 1.0;

	return result;
}

Matrix MMath::lookAt(const Vec3& eye, const Vec3& at,  const Vec3& up){
	return lookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);
}

/// Take the transpose of a matrix, swap row with columns 
Matrix MMath::transpose(const Matrix m){
	return Matrix(m[0*4], m[0*4 + 1], m[0*4 + 2], m[0*4 + 3],
				  m[1*4], m[1*4 + 1], m[1*4 + 2], m[1*4 + 3],
				  m[2*4], m[2*4 + 1], m[2*4 + 2], m[2*4 + 3],
				  m[3*4], m[3*4 + 1], m[3*4 + 2], m[3*4 + 3]);
}

/// 2x2 inverse is easy, 3x3 is a pain, 4x4 no way, I wrote a program to generate this code
Matrix MMath::inverse(const Matrix m) {
		Matrix inverseM;
		float det;

		inverseM[0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		inverseM[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
		inverseM[2] =  m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
		inverseM[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
		inverseM[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		inverseM[5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
		inverseM[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
		inverseM[7] =  m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
		inverseM[8] =  m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
		inverseM[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
		inverseM[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
		inverseM[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
		inverseM[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
		inverseM[13] =  m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
		inverseM[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
		inverseM[15] =  m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

		det = m[0] * inverseM[0] + m[1] * inverseM[4] + m[2] * inverseM[8] + m[3] * inverseM[12];
		
#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( fabs(det) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
#endif
		det = 1.0f / det;
		for (int i = 0; i < 16; i++){
			inverseM[i] *= det;
		}
		return inverseM;
}