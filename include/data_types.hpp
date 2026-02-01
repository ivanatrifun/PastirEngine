#pragma once
#ifndef __DATA_TYPES_HPP
#define __DATA_TYPES_HPP

template<typename T>
struct vec2 {
    T x,y;
};
typedef vec2<float> float2;

template<typename T>
struct vec3 {
    T x,y,z;
};
typedef vec3<float> float3;

// for some reason defined in sprite.cpp
float2 operator+(float2 a, float2 b);


#endif