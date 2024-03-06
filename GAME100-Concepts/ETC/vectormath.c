/**************************************************************************/
/***		Scott Fielder: vectormath 1986
/***            (Windows 95 version) 1997
/***		modified: 	May 2 1998
/***		perspective:	July 15 1999
/***		matrix stack class Feb 2000
/***		updated naming conventions and some return values: Oct 2004
/**************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "vectormath.h"


V_Matrix4 UNIT_MATRIX  = {
    	{1.0, 0.0, 0.0, 0.0},
    	{0.0, 1.0, 0.0, 0.0},
    	{0.0, 0.0, 1.0, 0.0},
    	{0.0, 0.0, 0.0, 1.0}  };

V_Vector ORIGIN = {0.0,0.0,0.0};
V_Vector X_AXIS = {1.0,0.0,0.0};
V_Vector Y_AXIS = {0.0,1.0,0.0};
V_Vector Z_AXIS = {0.0,0.0,1.0};


bool V_CompareV(V_Vector v1, V_Vector v2){
	if( (v1[0]-v2[0]) == 0.0 &&
		(v1[1]-v2[1]) == 0.0 &&
		(v1[2]-v2[2]) == 0.0) {
			return true;
		}else{
			return false;
		}
}
/**************************************************/
/*** V_CopyV - Load a vector FLOAT		***/
/**************************************************/
void V_CopyV(V_Vector target,V_Vector source){
		target[0] = source[0];
        target[1] = source[1];
        target[2] = source[2];
}

/**************************************************/
/*** V_LoadV - Load a vector FLOAT		***/
/**************************************************/
void  V_LoadV(V_Vector v , FLOAT x, FLOAT y, FLOAT z){
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
void  V_LoadV(V_Vector v , FLOAT x, FLOAT y, FLOAT z,FLOAT w){
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}
/**************************************************/
/*** V_LoadV - Load a vector FLOAT		***/
/**************************************************/
void  V_LoadV(float * v , float x, float y, float z,float w){
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

/**************************************************/
/***  V_Mag - Vector magnitude (FLOAT version)  ***/
/**************************************************/
FLOAT V_Mag(V_Vector a){
	return(sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]));
}




/***********************************************************/
/***  V_SMag - Vector squared magnitude (FLOAT version)  ***/
/***********************************************************/
FLOAT V_SqMag(V_Vector a)
{
	return(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}



/***************************************************/
/***  V_Norm - Normalize vector (FLOAT version)  ***/
/***************************************************/
FLOAT V_Norm(V_Vector a)
{
	FLOAT result;

	result = sqrt(V_Dot(a, a));
	if ( result < V_VERYSMALL ) {
		a[0] = 0.0; a[1] = 0.0; a[2] = 0.0;
		return(0.0);
	}
	
	a[0] = a[0] / result;
	a[1] = a[1] / result;
	a[2] = a[2] / result;

	return(result);
}

/***********************************************************************/
/***  V_Normt - Normalize vector w/ given tolerance (FLOAT version)  ***/
/***********************************************************************/
FLOAT V_Normt(V_Vector a, FLOAT tolerance)
{
	FLOAT result;
	int i;

	result = sqrt(V_Dot(a, a));
	if ( result < tolerance ) {
		a[0] = 0.0; a[1] = 0.0; a[2] = 0.0;
		return(0.0);
	}
	for (i=0;i<3;i++) {
		a[i] = a[i] / result;
	}
	return(result);
}

/************************************************************/
/***  V_MultMat3 - 3X3 Matrix Multiplier (FLOAT version)  ***/
/************************************************************/
void V_MultMat3(V_Matrix3 a, V_Matrix3 b, V_Matrix3 c)
{
	short i, j, k;

	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			c[i][j] = 0.0;
			for(k=0;k<3;k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

/************************************************************/
/***  V_MultMat4 - 4X4 Matrix Multiplier (FLOAT version)  ***/
/************************************************************/
void V_MultMat4(V_Matrix4 a, V_Matrix4 b, V_Matrix4 d){
	short i, j, k;
	V_Matrix4 c;

	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			c[i][j] = 0.0;
			for(k=0;k<4;k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	memcpy(d,c,sizeof(V_Matrix4));

}

/********************************************************/
/***  V_Cross - Vector Cross Product (FLOAT version)  ***/
/********************************************************/
void V_Cross(V_Vector a, V_Vector b, V_Vector target){
	static int x=0, y=1, z=2;

	target[x] = a[y] * b[z] - a[z] * b[y];
	target[y] = a[z] * b[x] - a[x] * b[z];
	target[z] = a[x] * b[y] - a[y] * b[x];
}


/****************************************************/
/***  V_Dot - Vector Dot Product (FLOAT version)  ***/
/****************************************************/
FLOAT V_Dot(V_Vector a, V_Vector b){
	return((a[0] * b[0] + a[1] * b[1] + a[2] * b[2]));
}


/***********************************************************************/
/***  V_Trans33 - Transform 3D Vector by 3X3 matrix (FLOAT version)  ***/
/***********************************************************************/
void V_Trans33(V_Vector v, V_Matrix3 m, V_Vector newv){
	static int x=0, y=1, z=2;
	V_Vector temp;

	if ( v == newv ) { /*** need to use temporary variable ***/
		temp[x] = v[x] * m[0][0] + v[y] * m[1][0] + v[z] * m[2][0];
		temp[y] = v[x] * m[0][1] + v[y] * m[1][1] + v[z] * m[2][1];
		temp[z] = v[x] * m[0][2] + v[y] * m[1][2] + v[z] * m[2][2];

		newv[x] = temp[x];
		newv[y] = temp[y];
		newv[z] = temp[z];
	}
	else {
		newv[x] = v[x] * m[0][0] + v[y] * m[1][0] + v[z] * m[2][0];
		newv[y] = v[x] * m[0][1] + v[y] * m[1][1] + v[z] * m[2][1];
		newv[z] = v[x] * m[0][2] + v[y] * m[1][2] + v[z] * m[2][2];
	}
}


/***********************************************************************/
/***  V_Trans34 - Transform 3D Vector by 4X4 matrix (FLOAT version)  ***/
/***********************************************************************/
void V_Trans34(V_Vector newv, V_Matrix4 m, V_Vector v){
	static int x=0, y=1, z=2;
	V_Vector temp;

	if ( v == newv ) { /*** need to use temporary variable ***/
		temp[x] = v[x] * m[0][0] + v[y] * m[1][0] + v[z] * m[2][0] + m[3][0];
		temp[y] = v[x] * m[0][1] + v[y] * m[1][1] + v[z] * m[2][1] + m[3][1];
		temp[z] = v[x] * m[0][2] + v[y] * m[1][2] + v[z] * m[2][2] + m[3][2];

		newv[x] = temp[x];
		newv[y] = temp[y];
		newv[z] = temp[z];
	}
	else {
		newv[x] = v[x] * m[0][0] + v[y] * m[1][0] + v[z] * m[2][0] + m[3][0];
		newv[y] = v[x] * m[0][1] + v[y] * m[1][1] + v[z] * m[2][1] + m[3][1];
		newv[z] = v[x] * m[0][2] + v[y] * m[1][2] + v[z] * m[2][2] + m[3][2];
	}
}

/**************************************************************/
/***  V_Dist - Distance between two points (FLOAT version)  ***/
/**************************************************************/
FLOAT V_Dist(V_Vector a, V_Vector b){
	FLOAT c[3];
	V_Sub(c,a,b);
	return(V_Mag(c));
}


/****************************************************************/
/***  V_Distsq - Distance squared between two points (FLOAT version)  ***/
/****************************************************************/
FLOAT V_Distsq(V_Vector a, V_Vector b){
	FLOAT c[3];
	V_Sub(c,a, b);
	return(V_SqMag(c));
}


/*************************************************/
/***  V_Add - Vector Addition (FLOAT version)  ***/
/*************************************************/
void V_Add(V_Vector target, V_Vector b, V_Vector c){
	target[0] = b[0] + c[0];
	target[1] = b[1] + c[1];
	target[2] = b[2] + c[2];
}


/****************************************************/
/***  V_Sub - Vector Subtraction (FLOAT version)  ***/
/****************************************************/
void V_Sub(V_Vector target, V_Vector b, V_Vector c){
	target[0] = b[0] - c[0];
	target[1] = b[1] - c[1];
	target[2] = b[2] - c[2];
}

/********************************************************/
/***  V_Mult - Vector Multiplication (FLOAT version)  ***/
/********************************************************/
void V_Mult( V_Vector target, V_Vector source, FLOAT scalar){
	target[0] = scalar * source[0];
	target[1] = scalar * source[1];
	target[2] = scalar * source[2];
}


/*************************************************/
/***  V_Neg - Vector Negation (FLOAT version)  ***/
/*************************************************/
void V_Neg(V_Vector a){
	a[0] = -a[0];
	a[1] = -a[1];
	a[2] = -a[2];
}

/**************************************************/
/***  V_Normal - Normal Vector (FLOAT version)  ***/
/**************************************************/
/***NEED TO HANDLE NORMALIZE ERRORS***/
void V_Normal(V_Vector v1, V_Vector v2, V_Vector u){
	V_Cross(v1, v2, u);
	V_Norm(u);
}

/*********************************************************************/
/***  V_NAngle - Angle between normalized vectors (FLOAT version)  ***/
/*********************************************************************/
FLOAT V_NAngle(V_Vector v1, V_Vector v2){
	FLOAT sign;
	sign = V_Dot(v1,v2);
	return(acos(sign));
}

/*********************************************************/
/***  V_Angle - Angle between vectors (FLOAT version)  ***/
/*********************************************************/
/***NEED TO HANDLE NORMALIZE ERRORS***/
FLOAT V_Angle(V_Vector a, V_Vector b){
	V_Vector v1, v2, v3;

	memcpy(v1, a, sizeof(V_Vector));
	memcpy(v2, b, sizeof(V_Vector));
	V_Norm(v1);
	V_Norm(v2);
	V_Cross(v1, v2, v3);
	return((FLOAT)atan2(V_Mag(v3), V_Dot(v1, v2)));
}

/*****************************************************************/
/***  V_Angle3 - Angle formed by three points (FLOAT version)  ***/
/*****************************************************************/
/***NEED TO HANDLE NORMALIZE ERRORS***/
FLOAT V_Angle3(V_Vector v1, V_Vector v2, V_Vector v3){
	V_Vector a, b;

	V_Sub(a,v1, v2);
	V_Sub(b,v3, v2);
	V_Norm(a);
	V_Norm(b);
	return(V_Angle(a, b));
}



/***************************************************************************/
/***  V_Dihedral - Dihedral angle formed by four points (FLOAT version)  ***/
/***************************************************************************/
/***NEED TO HANDLE NORMALIZE ERRORS***/
FLOAT V_Dihedral(V_Vector v1, V_Vector v2, V_Vector v3, V_Vector v4){
	V_Vector a, b, c, d, e, u1, u2;
	FLOAT angle, sign;

	V_Sub(a,v1, v2);
	V_Norm(a);
	V_Sub(b,v3, v2);
	V_Norm(b);
	V_Cross(a, b, u1);
	V_Norm(u1);

	V_Sub(c,v2, v3);
	V_Sub(d,v4, v3);
	V_Norm(c);
	V_Norm(d);
	V_Cross(c, d, u2);
	V_Norm(u2);

	V_Cross(u2, u1, e);

	angle = atan2(V_Mag(e), V_Dot(u1, u2));

	V_Norm(e);  /*** for dihedral angles of ~0 or ~180 vector returned is {0.0, 0.0, 0.0} ***/
	sign = V_Dot(b,e);

	return((sign >= 0.0) ? angle : -angle);
}


/*****************************************************************************/
/***  V_RotateVector3 - Form 3X3 matrix to rotate about a vector   ***/
/*****************************************************************************/
void V_RotateVector3(V_Matrix3 rm, FLOAT angle, V_Vector v){
	static int x=0, y=1, z=2;
	FLOAT cosang, sinang, cosm;

	cosang = (FLOAT)COS(angle);
	sinang = (FLOAT) SIN(angle);
	cosm = (FLOAT)(1.0 - cosang);

	rm[0][0] = (v[x] * v[x] * cosm) + cosang;
	rm[0][1] = (v[x] * v[y] * cosm) - v[z] * sinang;
	rm[0][2] = (v[x] * v[z] * cosm) + v[y] * sinang;
	rm[1][0] = (v[x] * v[y] * cosm) + v[z] * sinang;
	rm[1][1] = (v[y] * v[y] * cosm) + cosang;
	rm[1][2] = (v[y] * v[z] * cosm) - v[x] * sinang;
	rm[2][0] = (v[x] * v[z] * cosm) - v[y] * sinang;
	rm[2][1] = (v[y] * v[z] * cosm) + v[x] * sinang;
	rm[2][2] = (v[z] * v[z] * cosm) + cosang;
}

/*****************************************************************************/
/***  V_RotateVector4 - Form 4X4 matrix to rotate about a vector   ***/
/***************************************************************************/
void V_RotateVector4(V_Matrix4 rm, FLOAT angle, V_Vector v){
	FLOAT cosang, sinang, cosm;

	cosang = (FLOAT) COS(angle);
	sinang = (FLOAT) SIN(angle);
	cosm = (FLOAT)(1.0 - cosang);

	rm[0][0] = (v[0] * v[0] * cosm) + cosang;
	rm[0][1] = (v[0] * v[1] * cosm) - v[2] * sinang;
	rm[0][2] = (v[0] * v[2] * cosm) + v[1] * sinang;
	rm[0][3] = 0.0;
	rm[1][0] = (v[0] * v[1] * cosm) + v[2] * sinang;
	rm[1][1] = (v[1] * v[1] * cosm) + cosang;
	rm[1][2] = (v[1] * v[2] * cosm) - v[0] * sinang;
	rm[1][3] = 0.0;
	rm[2][0] = (v[0] * v[2] * cosm) - v[1] * sinang;
	rm[2][1] = (v[1] * v[2] * cosm) + v[0] * sinang;
	rm[2][2] = (v[2] * v[2] * cosm) + cosang;
	rm[2][3] = 0.0;
	rm[3][0] = 0.0;
	rm[3][1] = 0.0;
	rm[3][2] = 0.0;
	rm[3][3] = 1.0;
}



/**************************************************************************/
/***  V_RotateAxis3 - Form 3X3 matrix to rotate about an axis (FLOAT )  ***/
/**************************************************************************/
void V_RotateAxis3(V_Matrix3 rm, FLOAT angle, int axischar){
	FLOAT cosa, sina;

	cosa = COS(angle);
	sina = SIN(angle);

	switch(axischar)
	{
	case 'x':
		rm[0][0] = 1.0;   rm[0][1] = 0.0;   rm[0][2] = 0.0;
		rm[1][0] = 0.0;   rm[1][1] = cosa;  rm[1][2] = sina;
		rm[2][0] = 0.0;   rm[2][1] = -sina; rm[2][2] = cosa;
		break;
	case 'y':
		rm[0][0] = cosa;  rm[0][1] = 0.0;   rm[0][2] = -sina;
		rm[1][0] = 0.0;   rm[1][1] = 1.0;   rm[1][2] = 0.0;
		rm[2][0] = sina;  rm[2][1] = 0.0;   rm[2][2] = cosa;
		break;
	case 'z':
		rm[0][0] = cosa;  rm[0][1] = sina;  rm[0][2] = 0.0;
		rm[1][0] = -sina; rm[1][1] = cosa;  rm[1][2] = 0.0;
		rm[2][0] = 0.0;   rm[2][1] = 0.0;   rm[2][2] = 1.0;
		break;
	default:
		rm[0][0] = 1.0;   rm[0][1] = 0.0;   rm[0][2] = 0.0;
		rm[1][0] = 0.0;   rm[1][1] = 1.0;   rm[1][2] = 0.0;
		rm[2][0] = 0.0;   rm[2][1] = 0.0;   rm[2][2] = 1.0;
		break;
	}
}



/***************************************************************************/
/***  V_RotateAxis4 - Form 4X4 matrix to rotate about an axis (FLOAT )  ***/
/**************************************************************************/
void V_RotateAxis4(V_Matrix4 rm, FLOAT angle, int axischar){
	FLOAT cosa, sina;

	cosa = COS(angle);
	sina = SIN(angle);

	switch(axischar)
	{
	case 'x':
		rm[0][0] = 1.0;   rm[0][1] = 0.0;   rm[0][2] = 0.0;   rm[0][3] = 0.0;
		rm[1][0] = 0.0;   rm[1][1] = cosa;  rm[1][2] = sina;  rm[1][3] = 0.0;
		rm[2][0] = 0.0;   rm[2][1] = -sina; rm[2][2] = cosa;  rm[2][3] = 0.0;
		rm[3][0] = 0.0;   rm[3][1] = 0.0;   rm[3][2] = 0.0;   rm[3][3] = 1.0;
		break;
	case 'y':
		rm[0][0] = cosa;  rm[0][1] = 0.0;   rm[0][2] = -sina; rm[0][3] = 0.0;
		rm[1][0] = 0.0;   rm[1][1] = 1.0;   rm[1][2] = 0.0;   rm[1][3] = 0.0;
		rm[2][0] = sina;  rm[2][1] = 0.0;   rm[2][2] = cosa;  rm[2][3] = 0.0;
		rm[3][0] = 0.0;   rm[3][1] = 0.0;   rm[3][2] = 0.0;   rm[3][3] = 1.0;
		break;
	case 'z':
		rm[0][0] = cosa;  rm[0][1] = sina;  rm[0][2] = 0.0;   rm[0][3] = 0.0;
		rm[1][0] = -sina; rm[1][1] = cosa;  rm[1][2] = 0.0;   rm[1][3] = 0.0;
		rm[2][0] = 0.0;   rm[2][1] = 0.0;   rm[2][2] = 1.0;   rm[2][3] = 0.0;
		rm[3][0] = 0.0;   rm[3][1] = 0.0;   rm[3][2] = 0.0;   rm[3][3] = 1.0;
		break;
	default:
		rm[0][0] = 1.0;   rm[0][1] = 0.0;   rm[0][2] = 0.0;   rm[0][3] = 0.0;
		rm[1][0] = 0.0;   rm[1][1] = 1.0;   rm[1][2] = 0.0;   rm[1][3] = 0.0;
		rm[2][0] = 0.0;   rm[2][1] = 0.0;   rm[2][2] = 1.0;   rm[2][3] = 0.0;
		rm[3][0] = 0.0;   rm[3][1] = 0.0;   rm[3][2] = 0.0;   rm[3][3] = 1.0;
		break;
	}
}



/*****************************************************************************/
/***  V_Scale4 - Form 4X4 matrix to scale a vector (FLOAT )         			***/
/***************************************************************************/
void V_Scale4( V_Matrix4 tm, V_Vector v){

	tm[0][0] = v[0];  tm[0][1] = 0.0;    tm[0][2] = 0.0;   tm[0][3] = 0.0;
	tm[1][0] = 0.0;   tm[1][1] = v[1];   tm[1][2] = 0.0;   tm[1][3] = 0.0;
	tm[2][0] = 0.0;   tm[2][1] = 0.0;    tm[2][2] = v[2];  tm[2][3] = 0.0;
	tm[3][0] = 0.0;   tm[3][1] = 0.0;  	 tm[3][2] = 0.0;   tm[3][3] = 1.0;
}
/**************************************************************************/
/***  V_Scale - Form 4X4 matrix to scale a vector (FLOAT )         	***/
/**************************************************************************/
/***#define tm(a,b) tm[(a)*4 +(b)]
void V_Scale( V_Matrix tm, V_Vector v){
	tm(0,0) = v[0];  tm(0,1) = 0.0;    tm(0,2) = 0.0;   tm(0,3) = 0.0;
	tm(1,0) = 0.0;   tm(1,1) = v[1];   tm(1,2) = 0.0;   tm(1,3) = 0.0;
	tm(2,0) = 0.0;   tm(2,1) = 0.0;    tm(2,2) = v[2];  tm(2,3) = 0.0;
	tm(3,0) = 0.0;   tm(3,1) = 0.0;    tm(3,2) = 0.0;   tm[3,3] = 1.0;
}
***/
/*****************************************************************************/
/***  V_Translate4 - Form 4X4 matrix to translate a vector          ***/
/*****************************************************************************/
void V_Translate4( V_Matrix4 tm, V_Vector v){

	tm[0][0] = 1.0;   tm[0][1] = 0.0;   tm[0][2] = 0.0;   tm[0][3] = 0.0;
	tm[1][0] = 0.0;   tm[1][1] = 1.0;   tm[1][2] = 0.0;   tm[1][3] = 0.0;
	tm[2][0] = 0.0;   tm[2][1] = 0.0;   tm[2][2] = 1.0;   tm[2][3] = 0.0;
	tm[3][0] = v[0];  tm[3][1] = v[1];  tm[3][2] = v[2];  tm[3][3] = 1.0;
}

void V_PrintMatrix4(V_Matrix4 a,char *string){
sprintf(string,"%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
a[0][0],a[0][1],a[0][2],a[0][3],a[1][0],a[1][1],a[1][2],a[1][3],a[2][0],a[2][1],
a[2][2],a[2][3],a[3][0],a[3][1],a[3][2],a[3][3]);
}

void V_PrintV(V_Vector a,char *string){
	printf("%s:(%f,%f,%f)\n",string,a[0],a[1],a[2]);
}

void V_PrintVd(V_Vector a,char *string){
	printf("%s:(%lf,%lf,%lf)\n",string,a[0],a[1],a[2]);
}

void V_TransposeMatrix4(V_Matrix4 a, V_Matrix4 b){
    a[0][0] = b[0][0];
    a[0][1] = b[1][0];
    a[0][2] = b[2][0];
    a[0][3] = b[3][0];
    a[1][0] = b[0][1];
    a[1][1] = b[1][1];
    a[1][2] = b[2][1];
    a[1][3] = b[3][1];
    a[2][0] = b[0][2];
    a[2][1] = b[1][2];
    a[2][2] = b[2][2];
    a[2][3] = b[3][2];
    a[3][0] = b[0][3];
    a[3][1] = b[1][3];
    a[3][2] = b[2][3];
    a[3][3] = b[3][3];
}

void V_BackTransformMatrix(V_Matrix4 a, V_Matrix4 b){
    a[0][0] = (FLOAT)1.0/b[0][0];
    a[0][1] = b[1][0];
    a[0][2] = b[2][0];
    a[0][3] = b[3][0];
    a[1][0] = b[0][1];
    a[1][1] = (FLOAT)1.0/b[1][1];
    a[1][2] = b[2][1];
    a[1][3] = b[3][1];
    a[2][0] = b[0][2];
    a[2][1] = b[1][2];
    a[2][2] = (FLOAT)1.0/b[2][2];
    a[2][3] = b[3][1];
    a[3][0] = -b[3][0] * a[0][0];
    a[3][1] = -b[3][1] * a[1][1];
    a[3][2] = -b[3][2] * a[2][2];
    a[3][3] = b[3][3];
}

/********************************************/
/***	Constuctors ***/
/********************************************/
	V_MatrixStack::V_MatrixStack(){
		V_MatrixStack(1);
	}
	V_MatrixStack::V_MatrixStack(int depth){
	matrixStackDepth = depth;
	matrixStack = NULL;
	if((matrixStack =
   		(V_Matrix4 *)malloc(matrixStackDepth * sizeof(V_Matrix4))) == NULL){
#ifdef _UTILITIES_H
		printf("Memory error in vectormath.c at line %d\n",__LINE__);
#endif
	}
   currentMatrix = 0;
   memcpy(matrixStack[currentMatrix],UNIT_MATRIX,sizeof(V_Matrix4));
}

/********************************************/
/*** Destructor ***/
/********************************************/
	V_MatrixStack::~V_MatrixStack(){
	if(matrixStack) free(matrixStack),matrixStack = NULL;
}

/********************************************/
/*** pushes the transformation matrix stack ***/
/********************************************/
void V_MatrixStack::PushMatrix(){
	if(currentMatrix + 1 >= matrixStackDepth)throw "Too many pushes in V_Math";
      
   matrixStack[currentMatrix + 1][0][0] = matrixStack[currentMatrix][0][0];
   matrixStack[currentMatrix + 1][0][1] = matrixStack[currentMatrix][0][1];
   matrixStack[currentMatrix + 1][0][2] = matrixStack[currentMatrix][0][2];
   matrixStack[currentMatrix + 1][0][3] = matrixStack[currentMatrix][0][3];
   matrixStack[currentMatrix + 1][1][0] = matrixStack[currentMatrix][1][0];
   matrixStack[currentMatrix + 1][1][1] = matrixStack[currentMatrix][1][1];
   matrixStack[currentMatrix + 1][1][2] = matrixStack[currentMatrix][1][2];
   matrixStack[currentMatrix + 1][1][3] = matrixStack[currentMatrix][1][3];
   matrixStack[currentMatrix + 1][2][0] = matrixStack[currentMatrix][2][0];
   matrixStack[currentMatrix + 1][2][1] = matrixStack[currentMatrix][2][1];
   matrixStack[currentMatrix + 1][2][2] = matrixStack[currentMatrix][2][2];
   matrixStack[currentMatrix + 1][2][3] = matrixStack[currentMatrix][2][3];
   matrixStack[currentMatrix + 1][3][0] = matrixStack[currentMatrix][3][0];
   matrixStack[currentMatrix + 1][3][1] = matrixStack[currentMatrix][3][1];
   matrixStack[currentMatrix + 1][3][2] = matrixStack[currentMatrix][3][2];
   matrixStack[currentMatrix + 1][3][3] = matrixStack[currentMatrix][3][3];
   currentMatrix++;

}

/********************************************/
/*** Pops the transformation matrix stack ***/
/********************************************/
void V_MatrixStack::PopMatrix(){
	if(currentMatrix -1 < 0){
	#ifdef _UTILITIES_H
  		 DebugBox(__FILE__,__LINE__,"Error: Too many pops");
	#endif
     	 return;
	}	
   --currentMatrix;
}



/********************************************************************/
/***  Load a rotation matrix onto the transformation matrix stack ***/
/********************************************************************/
void V_MatrixStack::LoadRotationMatrix(FLOAT angle, V_Vector v){
		V_Matrix4 rotationMatrix, copyOfTopMatrix;

    memcpy(copyOfTopMatrix,matrixStack[currentMatrix],sizeof(V_Matrix4));
    V_RotateVector4(rotationMatrix,-angle,v);
    V_MultMat4(rotationMatrix,copyOfTopMatrix,matrixStack[currentMatrix]);
}

/*************************************************************************/
/***  Load a UNIT matrix onto the transformation matrix stack ***/
/********************************************************************/
void V_MatrixStack::LoadUnitMatrix(){
   memcpy(matrixStack[currentMatrix],UNIT_MATRIX,sizeof(V_Matrix4));
}
/*************************************************************************/
/***  Load a scaling/shearing matrix onto the transformation matrix stack ***/
/********************************************************************/
void V_MatrixStack::LoadScaleMatrix(FLOAT dx, FLOAT dy, FLOAT dz){
	V_Matrix4 translationMatrix, copyOfTopMatrix;
	V_Vector v;
	V_LoadV(v,dx,dy,dz);
	memcpy(copyOfTopMatrix,matrixStack[currentMatrix],sizeof(V_Matrix4));
	V_Scale4(translationMatrix , v);
	V_MultMat4(translationMatrix,copyOfTopMatrix,matrixStack[currentMatrix]);
}

/*************************************************************************/
/***  Load a translation  matrix onto the transformation matrix stack ***/
/***********************************************************************/
void V_MatrixStack::LoadTranslationMatrix(FLOAT dx, FLOAT dy, FLOAT dz){
	V_Matrix4 translationMatrix, copyOfTopMatrix;
	V_Vector v;
	V_LoadV(v,dx,dy,dz);
	memcpy(copyOfTopMatrix,matrixStack[currentMatrix],sizeof(V_Matrix4));
	V_Translate4(translationMatrix , v);
	V_MultMat4(translationMatrix,copyOfTopMatrix,matrixStack[currentMatrix]);
}

/*************************************************************************/
/***  Load a matrix onto the transformation matrix stack ***/
/********************************************************************/
void V_MatrixStack::LoadMatrix(const V_Matrix4 m){
   matrixStack[currentMatrix][0][0] = m[0][0];
   matrixStack[currentMatrix][0][1] = m[0][1];
   matrixStack[currentMatrix][0][2] = m[0][2];
   matrixStack[currentMatrix][0][3] = m[0][3];
   matrixStack[currentMatrix][1][0] = m[1][0];
   matrixStack[currentMatrix][1][1] = m[1][1];
   matrixStack[currentMatrix][1][2] = m[1][2];
   matrixStack[currentMatrix][1][3] = m[1][3];
   matrixStack[currentMatrix][2][0] = m[2][0];
   matrixStack[currentMatrix][2][1] = m[2][1];
   matrixStack[currentMatrix][2][2] = m[2][2];
   matrixStack[currentMatrix][2][3] = m[2][3];
   matrixStack[currentMatrix][3][0] = m[3][0];
   matrixStack[currentMatrix][3][1] = m[3][1];
   matrixStack[currentMatrix][3][2] = m[3][2];
   matrixStack[currentMatrix][3][3] = m[3][3];
}
//////////////////////////////////////////////////////////////////////
///			  v2
///			 /
///			/
///        v1 ---- v3
//////////////////////////////////////////////////////////////////////
void V_FormPlaneEquation(V_Vector v1, V_Vector v2,V_Vector v3,V_Plane plane){
	V_Vector a,b;
	V_Sub(a, v2, v1);
    V_Sub(b, v3, v1);
	V_Cross(a,b,plane);
	V_Norm(plane);
    plane[3] = -(plane[0] * v1[0] + plane[1] * v1[1] + plane[2] * v1[2]);
}

void V_FormPlaneEquation(V_Vector v1,V_Vector normal,V_Plane plane){
	V_CopyV(plane, normal);
	/// -d = ax + by + cz
	plane[3] = -(normal[0] * v1[0] + normal[1] * v1[1] + normal[2] * v1[2]);
}
FLOAT V_DistToPlane(V_Vector v1, V_Plane p){
	return (p[0] * v1[0]) + (p[1] * v1[1]) + (p[2] * v1[2]) + p[3];
}

void V_FormShadowMatrix(V_Vector light, V_Plane vPlaneEquation, V_Matrix4 matrix){
	FLOAT* destMat = (FLOAT*)matrix;
	V_FormPlaneEquation(ORIGIN,Z_AXIS,X_AXIS,vPlaneEquation);
    // Dot product of plane and light position
    FLOAT dot =   vPlaneEquation[0]*light[0] + 
				vPlaneEquation[1]*light[1] + 
				vPlaneEquation[2]*light[2] + 
				vPlaneEquation[3]*light[3];

    destMat[0] = dot - light[0] * vPlaneEquation[0];
    destMat[4] = 0.0 - light[0] * vPlaneEquation[1];
    destMat[8] = 0.0 - light[0] * vPlaneEquation[2];
    destMat[12] = 0.0 - light[0] * vPlaneEquation[3];
    destMat[1] = 0.0 - light[1] * vPlaneEquation[0];
    destMat[5] = dot - light[1] * vPlaneEquation[1];
    destMat[9] = 0.0 - light[1] * vPlaneEquation[2];
    destMat[13] = 0.0 - light[1] * vPlaneEquation[3];
    destMat[2] = 0.0 - light[2] * vPlaneEquation[0];
    destMat[6] = 0.0 - light[2] * vPlaneEquation[1];
    destMat[10] = dot - light[2] * vPlaneEquation[2];
    destMat[14] = 0.0 - light[2] * vPlaneEquation[3];
    destMat[3] = 0.0 - light[3] * vPlaneEquation[0];
    destMat[7] = 0.0 - light[3] * vPlaneEquation[1];
    destMat[11] = 0.0 - light[3] * vPlaneEquation[2];
    destMat[15] = dot - light[3] * vPlaneEquation[3];
    }
    
//// SSF: Broken		
void V_MatrixStack::LoadPerspective(FLOAT fieldOfView,FLOAT aspectRatio,
							  FLOAT nearPlane, FLOAT farPlane){
	throw "broken";						  
	FLOAT coTangent;
	coTangent = (FLOAT)COT(fieldOfView / (FLOAT)20.0);
	matrixStack[currentMatrix][0][0] = coTangent / aspectRatio;
	matrixStack[currentMatrix][0][1] = 0.0;
	matrixStack[currentMatrix][0][2] = 0.0;
	matrixStack[currentMatrix][0][3] = 0.0;
	matrixStack[currentMatrix][1][0] = 0.0;
	matrixStack[currentMatrix][1][1] = coTangent;
	matrixStack[currentMatrix][1][2] = 0.0;
	matrixStack[currentMatrix][1][3] = 0.0;
	matrixStack[currentMatrix][2][0] = 0.0;
	matrixStack[currentMatrix][2][1] = 0.0;
	matrixStack[currentMatrix][2][2] =
   			-((farPlane + nearPlane)/(farPlane - nearPlane));
	matrixStack[currentMatrix][2][3] = -1.0;
	matrixStack[currentMatrix][3][0] = 0.0;
	matrixStack[currentMatrix][3][1] = 0.0;
	matrixStack[currentMatrix][3][2] =
   			((FLOAT)-2.0)*(farPlane*nearPlane)/(farPlane - nearPlane);
	matrixStack[currentMatrix][3][3] = 0.0;
}

void V_MatrixStack::GetMatrix(V_Matrix4 m){
	memcpy(m,matrixStack[currentMatrix],sizeof(V_Matrix4));
}
V_Matrix4* V_MatrixStack::GetMatrix(){
	return &matrixStack[currentMatrix];
}
//////////////////////////////////////////////////////////////
/// This routine replaces the current matrix with its transpose
//////////////////////////////////////////////////////////////
void V_MatrixStack::TransposeMatrix(){
	V_Matrix4 copyOfTopMatrix;
	memcpy(copyOfTopMatrix,matrixStack[currentMatrix],sizeof(V_Matrix4));
	V_TransposeMatrix4(matrixStack[currentMatrix], copyOfTopMatrix);
}

//////////////////////////////////////////////////////////////
/// This routine replaces the current matrix with its backtransform
/// The back transform should be just the inverse of the matrix
/// which is true for the 3x3 but translates need special care
//////////////////////////////////////////////////////////////
void V_MatrixStack::BackTransformMatrix(){
	V_Matrix4 copyOfTopMatrix;
	memcpy(copyOfTopMatrix,matrixStack[currentMatrix],sizeof(V_Matrix4));
	V_BackTransformMatrix(matrixStack[currentMatrix], copyOfTopMatrix);
}
//////////////////////////////////////////////////////////////
/// Transforms the vector by the current matrix
/// note: this routine modifies the vector sent it
//////////////////////////////////////////////////////////////
void V_MatrixStack::V3(V_Vector a){
	V_Trans34(a,matrixStack[currentMatrix],a);
}

//////////////////////////////////////////////////////////////
/// Transforms the x,y,z by the current matrix
/// and places the result in V_Vector a
//////////////////////////////////////////////////////////////
void V_MatrixStack::V3(V_Vector a, FLOAT x, FLOAT y, FLOAT z){
	V_Vector vTemp;
	vTemp[0] = x,vTemp[1] = y, vTemp[2] = z; 
	V_Trans34(a,matrixStack[currentMatrix],vTemp);
}

//////////////////////////////////////////////////////////////
/// Transforms the vector b by the current matrix
/// and places the result in V_Vector a
//////////////////////////////////////////////////////////////
void V_MatrixStack::V3(V_Vector a,V_Vector b){
	V_Trans34(a,matrixStack[currentMatrix],b);
}




void V_Rectf::SetRect(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2){
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}
void V_Rectf::SetRect(V_Vector v1,V_Vector v2){
	x1 = v1[0];
	x2 = v2[0];
	y1 = v1[1];
	y2 = v2[1];
}

void V_Rectf::SetRectEmpty(){
	x1=0.0;
	x2=0.0;
	y1=0.0;
	y2=0.0;
}

FLOAT V_Rectf::Width(){
	return(fabs(x2 - x1));
}

FLOAT V_Rectf::Height(){
	return(fabs(y2 - y1));
}





