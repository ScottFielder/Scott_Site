
#include "VMath.h"
using namespace GAME_Lib;
 

Vec3 VMath::reflect(Vec3 v, Plane p){
	Vec3 result;
	float scalar = 2.0f * dot(v,p);
	Vec3 temp = p * scalar;
	result = v - temp;
	return result;
}

Vec3 VMath::reflect2(Vec3 v, Plane p){
	Vec3 result;
	float length  = mag(v);
	v = normalize(v);
	float scalar = 2.0f * dot(v,p);
	Vec3 temp = p * scalar;
	result = v - temp;
	result  = result *  length;
	return result;
}




float VMath::distance(const Vec3 &a, const Vec3 &b){
	Vec3 r  = a - b;
	return(mag(r));
}

float VMath::distance(const Vec3 &v, const Plane &p){
	return v.x*p.x + v.y*p.y + v.z*p.z - p.d;
}

float VMath::distance(const Sphere &s, const Plane &p){
	return distance((Vec3)s,p) - s.r;
}
