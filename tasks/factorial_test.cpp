#include <iostream>
#include <gtest/gtest.h>
#include "factorial.h"


TEST(FactorialTests, Positive1){
    EXPECT_EQ(720, factorial<6>::value);
}

TEST(FactorialTests, Positive2){
    EXPECT_EQ(6, factorial<3>::value);
}

TEST(FactorialTests, Zero){
    EXPECT_EQ(1, factorial<0>::value);
}

TEST(FactorialTests, Negative){
    EXPECT_EQ(1, factorial<-5>::value);
}