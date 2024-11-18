#include <gtest/gtest.h>
#include "../vec.h"

// TEST(A, B){
//     EXPECT_FALSE(true);
// }

TEST(VecTests, ctors1){
    vec<float, 3> v(1.0f, 4.5f, 8.3f);
    EXPECT_EQ(4.5f, v[1]);
}

TEST(VecTests, ctors2){
    vec<float, 2> v(0.24f, 4.5f);
    EXPECT_EQ(0.24f, v[0]);
}

TEST(VecTests, sum){
    vec<float, 2> v1(0.5f, 4.5f);
    vec<float, 2> v2(3.0f, 10.0f);
    vec<float, 2> vSum = v1 + v2;
    EXPECT_EQ(3.5f, vSum[0]);
    EXPECT_EQ(14.5f, vSum[1]);
}

TEST(VecTests, dif){
    vec<float, 2> v1(0.5f, 4.5f);
    vec<float, 2> v2(3.0f, 10.0f);
    vec<float, 2> vDif = v1 - v2;
    EXPECT_EQ(-2.5f, vDif[0]);
    EXPECT_EQ(-5.5, vDif[1]);
}

TEST(VecTests, prod){
    vec<float, 2> v1(0.5f, 4.5f);
    vec<float, 2> v2(3.0f, 10.0f);
    float prod = v1 * v2;
    EXPECT_EQ(46.5f, prod);
}

TEST(VecTests, negative){
    vec<float, 2> v1(0.5f, 4.5f);
    vec<float, 2> v2 = - v1;
    EXPECT_EQ(-0.5f, v2[0]);
    EXPECT_EQ(-4.5, v2[1]);
}