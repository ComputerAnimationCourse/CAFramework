#pragma once

#include "vec3.h"
#include "vec4.h"

#define MAT4_EPSILON 0.000001f

struct mat4 {
	union {
		float data[16]; // [c0r0, c0r1, c0r1, c0r1, c1r0, ..., c3r3]
		struct { // Each vec4 is a column of the matrix
			vec4 right;
			vec4 up;
			vec4 forward;
			vec4 position; // translation is the last vector to store
		};
		struct {
			//		    row 0	  row 1	    row 2	  row 3
			/*col 0*/ float xx; float xy; float xz; float xw;
			/*col 1*/ float yx; float yy; float yz; float yw;
			/*col 2*/ float zx; float zy; float zz; float zw;
			/*col 3*/ float tx; float ty; float tz; float tw;
		};
		struct { // column-row notation
			float c0r0; float c0r1; float c0r2; float c0r3;
			float c1r0; float c1r1; float c1r2; float c1r3;
			float c2r0; float c2r1; float c2r2; float c2r3;
			float c3r0; float c3r1; float c3r2; float c3r3;
		};
		struct { // row-column notation
			float r0c0; float r1c0; float r2c0; float r3c0;
			float r0c1; float r1c1; float r2c1; float r3c1;
			float r0c2; float r1c2; float r2c2; float r3c2;
			float r0c3; float r1c3; float r2c3; float r3c3;
		};
	}; // End union
	inline mat4() : // Identity matrix
		xx(1), xy(0), xz(0), xw(0),
		yx(0), yy(1), yz(0), yw(0),
		zx(0), zy(0), zz(1), zw(0),
		tx(0), ty(0), tz(0), tw(1) { }
	inline mat4(float* fv) :
		xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
		yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
		zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
		tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) { }
	inline mat4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33) :
		xx(_00), xy(_01), xz(_02), xw(_03),
		yx(_10), yy(_11), yz(_12), yw(_13),
		zx(_20), zy(_21), zz(_22), zw(_23),
		tx(_30), ty(_31), tz(_32), tw(_33) { }
}; // end mat4 struct

bool operator==(const mat4& a, const mat4& b);
bool operator!=(const mat4& a, const mat4& b);
mat4 operator+(const mat4& a, const mat4& b);
mat4 operator*(const mat4& a, float f);
mat4 operator*(const mat4& a, const mat4& b);
vec4 operator*(const mat4& m, const vec4& v);

vec3 transform_vector(const mat4& m, const vec3& v);
vec3 transform_point(const mat4& m, const vec3& v);
vec3 transform_point(const mat4& m, const vec3& v, float& w);

void transpose(mat4& m);
mat4 transposed(const mat4& m);
float determinant(const mat4& m);
mat4 adjugate(const mat4& m);
mat4 inverse(const mat4& m);
void invert(mat4& m);

mat4 frustum(float l, float r, float b, float t, float n, float f);
mat4 perspective(float fov, float aspect, float n, float f);
mat4 orthographic(float l, float r, float b, float t, float n, float f);
mat4 look_at(const vec3& position, const vec3& target, const vec3& up);

mat4 translate(const mat4& m, const vec3& v);
mat4 scale(const mat4& m, const vec3& v);