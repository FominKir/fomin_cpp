#include <iostream>
#include <gtest/gtest.h>
#include "../vec.h"
#include "../vec_functions.h"

TEST(VFuncTests, min1){
    vec<float, 3> a(1.0f, 6.7f, 8.123f);
    vec<float, 3> b(2.002f, 4.5f, 12.4f);
    vec<float, 3> v = min(a, b);
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(4.5f, v[1]);
    EXPECT_EQ(8.123f, v[2]);
}

TEST(VFuncTests, min2){
    vec<float, 3> a(1.0f, 6.7f, 8.123f);
    float b = 6.7f;
    vec<float, 3> v = min(a, b);
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(6.7f, v[1]);
    EXPECT_EQ(6.7f, v[2]);
}

TEST(VFuncTests, max1){
    vec<float, 3> a(1.0f, 6.7f, 8.123f);
    vec<float, 3> b(2.002f, 4.5f, 12.4f);
    vec<float, 3> v = max(a, b);
    EXPECT_EQ(2.002f, v[0]);
    EXPECT_EQ(6.7f, v[1]);
    EXPECT_EQ(12.4f, v[2]);
}

TEST(VFuncTests, max2){
    vec<float, 3> a(1.0f, 6.7f, 8.123f);
    float b = 6.7f;
    vec<float, 3> v = max(a, b);
    EXPECT_EQ(6.7f, v[0]);
    EXPECT_EQ(6.7f, v[1]);
    EXPECT_EQ(8.123f, v[2]);
}

TEST(VFuncTests, clamp1){
    vec<float, 3> a(1.0f, 6.7f, 8.123f);
    vec<float, 3> minVal(-4.5, 7.5f, -12.4f);
    vec<float, 3> maxVal(2.002f, 8.5f, 4.4f);
    vec<float, 3> v = clamp(a, minVal, maxVal);
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(7.5f, v[1]);
    EXPECT_EQ(4.4f, v[2]);
}

TEST(VFuncTests, clamp2){
    vec<float, 3> a(1.0f, 6.7f, 8.123f);
    float minVal = 5.0f;
    float maxVal = 8.11f;
    vec<float, 3> v = clamp(a, minVal, maxVal);
    EXPECT_EQ(5.0f, v[0]);
    EXPECT_EQ(6.7f, v[1]);
    EXPECT_EQ(8.11f, v[2]);
}

TEST(VFuncTests, mix1){
    vec<float, 3> a(10.0f, 20.0f, 40.0f);
    vec<float, 3> b(50.0f, 60.0f, -100.0f);
    vec<float, 3> wb(1.0f, 0.5f, 0.75f);
    vec<float, 3> v = mix(a, b, wb);
    EXPECT_EQ(50.0f, v[0]);
    EXPECT_EQ(40.0f, v[1]);
    EXPECT_EQ(-65.0f, v[2]);
}

TEST(VFuncTests, mix2){
    vec<float, 3> a(10.0f, 20.0f, 40.0f);
    vec<float, 3> b(50.0f, 60.0f, -100.0f);
    float wb = 0.25;
    vec<float, 3> v = mix(a, b, wb);
    EXPECT_EQ(20.0f, v[0]);
    EXPECT_EQ(30.0f, v[1]);
    EXPECT_EQ(5.0f, v[2]);
}

TEST(VFuncTests, cross1){
    vec<float, 3> a(1.0f, 0.0f, 0.0f);
    vec<float, 3> b(0.0f, 1.0f, 0.0f);
    vec<float, 3> v = cross(a, b);
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
    EXPECT_EQ(1.0f, v[2]);
}

TEST(VFuncTests, cross2){
    vec<float, 3> a(1.0f, 2.0f, 3.0f);
    vec<float, 3> b(3.0f, 2.0f, 1.0f);
    vec<float, 3> v = cross(a, b);
    EXPECT_EQ(-4.0f, v[0]);
    EXPECT_EQ(8.0f, v[1]);
    EXPECT_EQ(-4.0f, v[2]);
}

TEST(VFuncTests, cross3){
    vec<float, 3> a(1.0f, 2.0f, 3.0f);
    vec<float, 3> b(1.0f, 2.0f, 3.0f);
    vec<float, 3> v = cross(a, b);
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}

TEST(VFuncTests, dot){
    vec<float, 3> a(1.0f, 2.0f, 3.0f);
    vec<float, 3> b(3.0f, 2.0f, 1.0f);
    float v = dot(a, b);
    EXPECT_EQ(10.0f, v);
}

TEST(VFuncTests, length){
    vec<float, 3> a(2.0f, 3.0f, 6.0f);
    float v = length(a);
    EXPECT_EQ(7.0f, v);
}

TEST(VFuncTests, distance){
    vec<float, 3> a(3.0f, 0.0f, 0.0f);
    vec<float, 3> b(0.0f, 4.0f, 0.0f);
    float v = distance(a, b);
    EXPECT_EQ(5.0f, v);
}

TEST(VFuncTests, normalize){
    vec<float, 3> a(10.0f, 0.0f, 0.0f);
    vec<float, 3> v = normalize(a);
    EXPECT_EQ(1.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}

TEST(VFuncTests, reflect){
    vec<float, 3> i(11.0f, 12.0f);
    vec<float, 3> n(0.0f, 1.0f);
    vec<float, 3> v = reflect(i, n);
    EXPECT_EQ(11.0f, v[0]);
    EXPECT_EQ(-12.0f, v[1]);
}

TEST(VFuncTests, refractIn){
    vec<float, 3> i(0.0f, -1.0f, 0.0f);
    vec<float, 3> n(0.0f, 1.0f, 0.0f);
    float r = 1.0f;
    vec3 v = refract(i, n, r);
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(-1.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}

TEST(VFuncTests, refractOut){
    vec<float, 3> i(0.0f, 1.0f, 0.0f);
    vec<float, 3> n(0.0f, -1.0f, 0.0f);
    float r = 1.0f;
    vec3 v = refract(i, n, r);
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(1.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}

TEST(VFuncTests, abs){
    vec<float, 3> i(10.0f, -1.0f, -20.3f);
    vec3 v = abs(i);
    EXPECT_EQ(10.0f, v[0]);
    EXPECT_EQ(1.0f, v[1]);
    EXPECT_EQ(20.3f, v[2]);
}