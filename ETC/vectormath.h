#ifndef _VECTORMATH_H_
#define _VECTORMATH_H_
#include <math.h>
#ifndef FLOAT
#define FLOAT double
#endif
/***************************************
Coordinate system according to Vectormath
                |+Y
                |
                |____+X
               /
              /
             +Z
****************************************/
#define V_VERYSMALL 1.0e-20
///M_PI sould be defined in math.h. If not define it here
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#ifndef M_2PI
#define M_2PI 3.1415926535897932384626433832795*2.0
#endif

#ifndef RADtoDEG
#define RADtoDEG        180.0/M_PI
#endif
#ifndef DEGtoRAD
#define DEGtoRAD        M_PI/180.00
#endif

#define SIN(A)	sin((A))
#define COS(A)	cos((A))
#define TAN(A)	tan((A))
#define COT(A)	(1.0/tan((A)))



typedef FLOAT   V_Vector[4];
typedef FLOAT   V_Matrix3[3][3];
typedef FLOAT   V_Matrix4[4][4];
typedef FLOAT   V_Matrix[16];
typedef FLOAT   V_Plane[4];/// ax + by + cz + d = 0
typedef FLOAT	V_Tensor[3][3];
/// The first three are the center and w is the radius
typedef FLOAT   V_Sphere[4];

extern V_Matrix4 UNIT_MATRIX;
extern V_Vector ORIGIN,X_AXIS,Y_AXIS,Z_AXIS;

bool	V_CompareV(V_Vector, V_Vector);
void	V_CopyV(V_Vector ,V_Vector );
void	V_LoadV(V_Vector, FLOAT,FLOAT,FLOAT);
inline void    V_LoadV(V_Vector v , FLOAT x, FLOAT y, FLOAT z,FLOAT w);
void	V_LoadV(float*, float,float,float,float);
FLOAT	V_Mag(V_Vector);
FLOAT	V_SqMag(V_Vector);
FLOAT 	V_Norm(V_Vector);
void 	V_MultMat3(V_Matrix3, V_Matrix3, V_Matrix3);
void 	V_MultMat4(V_Matrix4, V_Matrix4, V_Matrix4);
void 	V_Cross(V_Vector a , V_Vector b , V_Vector target);
FLOAT	V_Dot(V_Vector, V_Vector);
void 	V_Trans33(V_Vector, V_Matrix3, V_Vector);
void 	V_Trans34(V_Vector, V_Matrix4, V_Vector);
FLOAT	V_Dist(V_Vector, V_Vector);
FLOAT	V_Distsq(V_Vector, V_Vector);
void 	V_Copy(V_Vector, V_Vector);
void 	V_Add(V_Vector, V_Vector, V_Vector);
void 	V_Sub(V_Vector, V_Vector, V_Vector);
void 	V_Mult(V_Vector, V_Vector,FLOAT);
void 	V_Neg(V_Vector);
void 	V_Normal(V_Vector, V_Vector, V_Vector);
FLOAT	V_NAngle(V_Vector, V_Vector);
FLOAT	V_Angle(V_Vector, V_Vector);
FLOAT	V_Angle3(V_Vector, V_Vector, V_Vector);
FLOAT	V_Dihedral(V_Vector, V_Vector, V_Vector, V_Vector);
void 	V_RotateVector3(V_Matrix3, FLOAT, V_Vector);
void 	V_Translate4(V_Matrix4, V_Vector);
void 	V_Scale4( V_Matrix4 , V_Vector );
void 	V_Scale( V_Matrix , V_Vector );///SSF new 
void 	V_RotateVector4(V_Matrix4, FLOAT, V_Vector);
void 	V_RotateAxis3(V_Matrix3, FLOAT, int);
void 	V_RotateAxis4(V_Matrix4, FLOAT, int);
void 	V_PrintMatrix4(V_Matrix4,char*);
void 	V_PrintV(V_Vector,char*);
void 	V_TransposeMatrix4(V_Matrix4 , V_Matrix4);
void 	V_PrintMatrix4(V_Matrix4 ,char *);
void 	V_PrintV(V_Vector ,char *);
void	V_PrintVd(V_Vector a,char *string);
void 	V_TransposeMatrix4(V_Matrix4 , V_Matrix4);
void 	V_BackTransformMatrix4(V_Matrix4 , V_Matrix4);
void	V_FormShadowMatrix(V_Vector light, V_Vector normal, V_Matrix4 matrix);
void	V_FormPlaneEquation(V_Vector v1, V_Vector v2,V_Vector v3,V_Plane plane);
void	V_FormPlaneEquation(V_Vector v1,V_Vector normal,V_Plane plane);
FLOAT	V_DistToPlane(V_Vector v1, V_Plane p);



class	V_Rectf { /// this is a double version of the CRect class in Windows
public:
		FLOAT x1;	/// usually left
		FLOAT y1;
		FLOAT x2;
		FLOAT y2;	/// usually bottom
public:
		void	SetRect(FLOAT,FLOAT,FLOAT,FLOAT);
		void	SetRect(V_Vector,V_Vector);
		void	SetRectEmpty();
		FLOAT	Height();
		FLOAT	Width();
};

class	V_MatrixStack {
	private:
		V_Matrix4 *matrixStack;
		int matrixStackDepth;
		int currentMatrix;
	public:
		V_MatrixStack();
		V_MatrixStack(int);
	   ~V_MatrixStack();
		void 	PushMatrix();
		void 	PopMatrix();
		void 	LoadUnitMatrix();
		void 	LoadRotationMatrix(FLOAT, V_Vector);
		void 	LoadRotationMatrix(FLOAT,FLOAT,FLOAT,FLOAT);
		void 	LoadTranslationMatrix(FLOAT,FLOAT,FLOAT);
		void 	LoadScaleMatrix(FLOAT , FLOAT , FLOAT );
		void 	LoadMatrix(const V_Matrix4);
		void 	LoadPerspective(FLOAT,FLOAT,FLOAT,FLOAT);
		void	GetMatrix(V_Matrix4);
		V_Matrix4* GetMatrix();
		void	TransposeMatrix();
		void	BackTransformMatrix();
		void	V3(V_Vector);
		void	V3(V_Vector,FLOAT,FLOAT,FLOAT);
		void	V3(V_Vector,V_Vector);
};

#endif /*_VECTORMATH_H_*/
