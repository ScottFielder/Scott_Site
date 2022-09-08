#pragma once
#include <stdio.h>	/// Needed for the printf statement, could have used cin and cout but I have issues.  
#include "Vector.h"

namespace  GAME_Lib {
	/// These are the default vectors of the eye according to OpenGL
	///	                             |+Y
	///   origin(0.0f,0.0f,0.0f);    |
	///   up(0.0f,1.0f,0.0f);        |_____+X
	///   forward(0.0f,0.0f,-1.0f); /
	///                            /
	///                          +Z
	///
	class Matrix  {

		/// Let's just make sure that all is clear about how this matrix is layed out. 
	
		/// How a matrix is really layed out is pretty much abitrary but we need to agree
		/// and the world has agreed - except for microsoft - on the right-hand rule. 
		/// First, the 4x4 matrix is really just an array of 16 numbers.  
		/// We need to think of the array as a matrix in the following way
		/// 4x4 matrix - COLUMN MAJOR - The OpenGL, science, physics, mathematics and engineering way. 
		///	0  4  8  12        [0][0]  [1][0]  [2][0]  [3][0]   
		///	1  5  9  13  (or)  [0][1]  [1][1]  [2][1]  [3][1]
		///	2  6  10 14        [0][2]  [1][2]  [2][2]  [3][2]
		///	3  7  11 15        [0][3]  [1][3]  [2][3]  [3][3]
	private:
		float  m[16];
	public:
		
		/// Now I can use the structure itself as an array.
		/// When overloading the [] operator you need to declair one
		/// to read the array and one to write to the array. 
		///  Returns a const rvalue
		inline const float operator [] (int index) const {  
			return *(m + index); 
		}

		/// This one is for writing to the structure as if where an array 
		/// it returns a lvalue
		inline float& operator [] ( int index ) { 
			return *(m + index); 
		}

	
		/// Constuctors
		inline Matrix(float m0, float m1, float m2, float m3,
               float m4, float m5, float m6, float m7,
               float m8, float m9, float m10, float m11,
               float m12, float m13, float m14, float m15) {
				m[0] =  m0;   m[4] = m4;   m[8] =  m8;   m[12] = m12;
				m[1] =  m1;   m[5] = m5;   m[9] =  m9;   m[13] = m13;
				m[2] =  m2;   m[6] = m6;   m[10] = m10;  m[14] = m14;
				m[3] =  m3;	  m[7] = m7;   m[11] = m11;	 m[15] = m15;
		}

		/// Create the unit matrix probably the most common way of initializing a matrix
		inline Matrix( const float d = 1.0f ) { 
			if(d == 1.0f) {
				loadIdentity();
			} else {
				m[0] =  d;   m[4] = d;   m[8] =  d;   m[12] = d;
				m[1] =  d;   m[5] = d;   m[9] =  d;   m[13] = d;
				m[2] =  d;   m[6] = d;   m[10] = d;   m[14] = d;
				m[3] =  d;	 m[7] = d;   m[11] = d;	  m[15] = d;
			}
		}
		

		/// Creates the identity matrix
		inline void loadIdentity(){
			m[0] =  1.0f;   m[4] = 0.0f;   m[8] =  0.0f;   m[12] = 0.0f;
			m[1] =  0.0f;   m[5] = 1.0f;   m[9] =  0.0f;   m[13] = 0.0f;
			m[2] =  0.0f;   m[6] = 0.0f;   m[10] = 1.0f;   m[14] = 0.0f;
			m[3] =  0.0f;   m[7] = 0.0f;   m[11] = 0.0f;   m[15] = 1.0f;
		}



		/// Multiply two 4x4 matricies. 
		/// Grrr, I never liked mulipling maticies - but it needs to be done. 
		inline const Matrix operator*(const Matrix& n) const {	
			///Matrix c; /// This is how i did it in 1980
			///for(int i=0;i<4;i++) {
			///		for(int j=0;j<4;j++) {
			///			c[i*4+j] = (m[i*4+0] * n[0*4+j]) + (m[i*4+1] * n[1*4+j]) + (m[i*4+2] * n[2*4+j]) + (m[i*4+3] * n[3*4+j]);	
			///		}
			///}
			return Matrix ( m[0*4+0] * n[0*4+0] + m[0*4+1] * n[1*4+0] + m[0*4+2] * n[2*4+0] + m[0*4+3] * n[3*4+0],
							m[0*4+0] * n[0*4+1] + m[0*4+1] * n[1*4+1] + m[0*4+2] * n[2*4+1] + m[0*4+3] * n[3*4+1],
							m[0*4+0] * n[0*4+2] + m[0*4+1] * n[1*4+2] + m[0*4+2] * n[2*4+2] + m[0*4+3] * n[3*4+2],
							m[0*4+0] * n[0*4+3] + m[0*4+1] * n[1*4+3] + m[0*4+2] * n[2*4+3] + m[0*4+3] * n[3*4+3],
							m[1*4+0] * n[0*4+0] + m[1*4+1] * n[1*4+0] + m[1*4+2] * n[2*4+0] + m[1*4+3] * n[3*4+0],
							m[1*4+0] * n[0*4+1] + m[1*4+1] * n[1*4+1] + m[1*4+2] * n[2*4+1] + m[1*4+3] * n[3*4+1],
							m[1*4+0] * n[0*4+2] + m[1*4+1] * n[1*4+2] + m[1*4+2] * n[2*4+2] + m[1*4+3] * n[3*4+2],
							m[1*4+0] * n[0*4+3] + m[1*4+1] * n[1*4+3] + m[1*4+2] * n[2*4+3] + m[1*4+3] * n[3*4+3],
							m[2*4+0] * n[0*4+0] + m[2*4+1] * n[1*4+0] + m[2*4+2] * n[2*4+0] + m[2*4+3] * n[3*4+0],
							m[2*4+0] * n[0*4+1] + m[2*4+1] * n[1*4+1] + m[2*4+2] * n[2*4+1] + m[2*4+3] * n[3*4+1],
							m[2*4+0] * n[0*4+2] + m[2*4+1] * n[1*4+2] + m[2*4+2] * n[2*4+2] + m[2*4+3] * n[3*4+2],
							m[2*4+0] * n[0*4+3] + m[2*4+1] * n[1*4+3] + m[2*4+2] * n[2*4+3] + m[2*4+3] * n[3*4+3],
							m[3*4+0] * n[0*4+0] + m[3*4+1] * n[1*4+0] + m[3*4+2] * n[2*4+0] + m[3*4+3] * n[3*4+0],
							m[3*4+0] * n[0*4+1] + m[3*4+1] * n[1*4+1] + m[3*4+2] * n[2*4+1] + m[3*4+3] * n[3*4+1],
							m[3*4+0] * n[0*4+2] + m[3*4+1] * n[1*4+2] + m[3*4+2] * n[2*4+2] + m[3*4+3] * n[3*4+2],
							m[3*4+0] * n[0*4+3] + m[3*4+1] * n[1*4+3] + m[3*4+2] * n[2*4+3] + m[3*4+3] * n[3*4+3] );
		
	}
		/// Multipling a matrix by itself is probably the most commom
		/// ("this" is the address of the matrix. "*this" de-references that address
		inline Matrix& operator*=(const Matrix& n) { 
			*this =  *this * n;
			return *this; 
		}

		/// Multiply a Vec4 by this matrix and return the resulting vector
		inline Vec4 operator* (const Vec4& v) const {
			
			float x  =  v.x * m[0] + v.y * m[4] + v.z * m[8]  + v.w * m[12];
			float y  =  v.x * m[1] + v.y * m[5] + v.z * m[9]  + v.w * m[13];
			float z  =  v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14];
			float w  =  v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15];
			return Vec4(x,y,z,w);
		}
	
		
		inline void print() const {
			printf("%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n\n",
				m[0], m[4], m[8],  m[12],
				m[1], m[5], m[9],  m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]);
		}
		
		/// These allow me convert from type Matrix to const float * without issues
		inline operator float* () { return static_cast<float*>( &m[0] ); }
		inline operator const float* () const { return static_cast<const float*>( &m[0]); }
			
	};


	class Matrix3  {
		/// 3x3 matrix - COLUMN MAJOR - The OpenGL, science, physics, mathematics and engineering way. 
		///	0	3	6			
		///	1	4	7	 
		///	2	5	8			
		
	private:
		float  m[9];
	public:
		
		/// Now I can use the structure itself as an array.
		/// When overloading the [] operator you need to declair one
		/// to read the array and one to write to the array. 
		///  Returns a const rvalue
		inline const float operator [] (int index) const {  
			return *(m + index); 
		}

		/// This one is for writing to the structure as if where an array 
		/// it returns a lvalue
		inline float& operator [] ( int index ) { 
			return *(m + index); 
		}

	
		/// Constuctors
		inline Matrix3(float xx, float yx, float zx, 
               float xy, float yy, float zy,
               float xz, float yz, float zz) {       
				m[0] =  xx;   m[3] = xy;   m[6] =  xz;  
				m[1] =  yx;   m[4] = yy;   m[7] =  yz;
				m[2] =  zx;   m[5] = zy;   m[8] =  zz;
				
		}

		/// Create the unit matrix probably the most common way of initializing a matrix
		inline Matrix3( const float d = 1.0f ) { 
			if(d == 1.0f) {
				loadIdentity();
			} else {
				m[0] =  d;   m[3] = d;   m[6] =  d;  
				m[1] =  d;   m[4] = d;   m[7] =  d;  
				m[2] =  d;   m[5] = d;   m[8] =  d;  
			
			}
		}
		

		/// Creates the identity matrix
		inline void loadIdentity(){
			m[0] =  1.0f;   m[3] = 0.0f;   m[6] =  0.0f;   
			m[1] =  0.0f;   m[4] = 1.0f;   m[7] =  0.0f; 
			m[2] =  0.0f;   m[5] = 0.0f;   m[8] =  1.0f; 
			
		}

		/// Extracts the inner 3x3 from a 4x4 matrix
		inline Matrix3 operator = (const Matrix& m){
			return Matrix3(m[0],m[1],m[2],
						   m[4],m[5],m[6],
						   m[8],m[9],m[10]);
		}
	};

}