#include <iostream>
#include <gtest/gtest.h>
#include "../templates.h"

// TEST(A, B){
//     EXPECT_FALSE(true);
// }

TEST(TemplateTests, ctors1){
    int a = 11;
    float b = 10;
    std::string c = "ads";
    std::array<int, 100> d = {};
    const int* e = nullptr;
    EXPECT_EQ(1, X(a));
}

TEST(TemplateTests, ctors2){
    int a = 11;
    float b = 10;
    std::string c = "ads";
    std::array<int, 100> d = {};
    const int* e = nullptr;
    EXPECT_EQ(2, X(a, b));
}

TEST(TemplateTests, ctors3){
    int a = 11;
    float b = 10;
    std::string c = "ads";
    std::array<int, 100> d = {};
    const int* e = nullptr;
    EXPECT_EQ(3, X(a, b, c));
}

TEST(TemplateTests, ctors4){
    int a = 11;
    float b = 10;
    std::string c = "ads";
    std::array<int, 100> d = {};
    const int* e = nullptr;
    EXPECT_EQ(4, X(a, b, c, d));
}

TEST(TemplateTests, ctors5){
    int a = 11;
    float b = 10;
    std::string c = "ads";
    std::array<int, 100> d = {};
    const int* e = nullptr;
    EXPECT_EQ(5, X(a, b, c, d, e));
}