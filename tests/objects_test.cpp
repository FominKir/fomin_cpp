#include <iostream>
#include <gtest/gtest.h>
#include "../vec.h"
#include "../RayMarching/Material.h"
#include "../RayMarching/Object.h"
// #include "../RayMarching/Ray.h"
// #include "../RayMarching/Scene.h"
#include "../RayMarching/Texture.h"

// TEST(A, B){
//     EXPECT_FALSE(true);
// }

TEST(ObjTests, boxTest){
    vec3 point(-2.5, 5.1, 7.5);
    Texture defaultTexture;
    Material defaultMaterial(defaultTexture);
    std::unique_ptr<Object> testBox(new Box(vec3(0, 10, 5), vec3(5, 15, 10), &defaultMaterial));
    float dist = testBox->SDF(point);
    vec3 norm = testBox->getNorm(point);
    EXPECT_EQ(0, dist);
    EXPECT_EQ(0, norm[0]);
    EXPECT_EQ(-1, norm[1]);
    EXPECT_EQ(0, norm[2]);
}
