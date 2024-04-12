#include <iostream>
#include <TFile.h>
#include <TVectorT.h>
#include <math.h>
// #include <vector.h>
// #include "physRay.h" //just for test
void PrintVector2(Double_t *vector){
    size_t dimension = 2;
    printf("[ ");
    for (size_t i = 0; i < dimension; i++)
    {
        printf("%g ", vector[i]);
    }
    printf("]\n");
}

void PrintVector3(Double_t *vector){
    size_t dimension = 3;
    printf("[ ");
    for (size_t i = 0; i < dimension; i++)
    {
        printf("%g ", vector[i]);
    }
    printf("]\n");
}

Double_t norm2D(Double_t* vector){
    Double_t normval = 0;
    for (size_t i = 0; i < 2 ; i++)
    {
        normval += vector[i] * vector[i];
    }
    normval=std::sqrt(normval);
    return normval;
}

Double_t* multiply2D(Double_t* vector, Double_t scalar){
    Double_t* result = new Double_t[2];
    // Double_t result[2];
    for (size_t i = 0; i < 2; i++)
    {
        result[i] = vector[i] * scalar;
    }
    return result;
}

Double_t* Vec3to2(Double_t* vector,int axis){
    Double_t* result = new Double_t[2];
    if (axis==0)
    {
        result[0] = vector[1];
        result[1] = vector[2];
    }
    else if (axis==1)
    {
        result[0] = vector[0];
        result[1] = vector[2];
    }
    else if (axis==2)
    {
        result[0] = vector[0];
        result[1] = vector[1];
    }
    else
    {
        printf("Error: axis should be 0, 1 or 2\n");
    }
    return result;
}

bool isRayIntersectingRectangle(Double_t* rayOrigin, Double_t* rayDirection, Double_t* rectangleOrigin, Double_t* rectangleSize){
    if (norm2D(rayDirection)==0){
        if (rayOrigin[0] >= rectangleOrigin[0] && rayOrigin[0] <= rectangleOrigin[0] + rectangleSize[0] && rayOrigin[1] >= rectangleOrigin[1] && rayOrigin[1] <= rectangleOrigin[1] + rectangleSize[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Double_t* rayNormal = multiply2D(rayDirection, 1.0 / norm2D(rayDirection));
    // Double_t rayNormal[2] = {1, 1};
    Double_t tmin, tmax, ymin, ymax;
    tmin = (rectangleOrigin[0] - rayOrigin[0]) / rayNormal[0];
    tmax = (rectangleOrigin[0] + rectangleSize[0] - rayOrigin[0]) / rayNormal[0];
    if (tmin > tmax)
    {
        Double_t temp = tmin;
        tmin = tmax;
        tmax = temp;
    }
    ymin = rayOrigin[1] + tmin * rayNormal[1];
    ymax = rayOrigin[1] + tmax * rayNormal[1];
    delete[] rayNormal;
    if (ymin>rectangleOrigin[1]+rectangleSize[1] || ymax<rectangleOrigin[1])
    {
        return false;
    }
    return true;
}

// Double_t* crossDistantInBox(Double_t* rayOrigin, Double_t* rayDirection, Double_t* boxOrigin, Double_t* boxSize){
//     Double_t* point_in[3]={0,0,0};
//     Double_t* point_out[3]={0,0,0};
// }



bool isRayIntersectingBoxQ(Double_t* rayOrigin, Double_t* rayDirection, Double_t* boxOrigin, Double_t* boxSize){
    bool isIntersectingX, isIntersectingY, isIntersectingZ;

    Double_t X_rayOrigin[2] = {rayOrigin[1], rayOrigin[2]};
    Double_t X_rayDirection[2] = {rayDirection[1], rayDirection[2]};
    Double_t X_boxOrigin[2] = {boxOrigin[1], boxOrigin[2]};
    Double_t X_boxSize[2] = {boxSize[1], boxSize[2]};
    isIntersectingX = isRayIntersectingRectangle(X_rayOrigin, X_rayDirection, X_boxOrigin, X_boxSize);
    return true;
    }

bool isRayIntersectingBox(Double_t* rayOrigin, Double_t* rayDirection, Double_t* boxOrigin, Double_t* boxSize){
    bool isIntersectingX, isIntersectingY, isIntersectingZ;

    Double_t X_rayOrigin[2] = {rayOrigin[1], rayOrigin[2]};
    Double_t X_rayDirection[2] = {rayDirection[1], rayDirection[2]};
    Double_t X_boxOrigin[2] = {boxOrigin[1], boxOrigin[2]};
    Double_t X_boxSize[2] = {boxSize[1], boxSize[2]};
    isIntersectingX = isRayIntersectingRectangle(X_rayOrigin, X_rayDirection, X_boxOrigin, X_boxSize);

    Double_t Y_rayOrigin[2] = {rayOrigin[0], rayOrigin[2]};
    Double_t Y_rayDirection[2] = {rayDirection[0], rayDirection[2]};
    Double_t Y_boxOrigin[2] = {boxOrigin[0], boxOrigin[2]};
    Double_t Y_boxSize[2] = {boxSize[0], boxSize[2]};
    isIntersectingY = isRayIntersectingRectangle(Y_rayOrigin, Y_rayDirection, Y_boxOrigin, Y_boxSize);

    Double_t Z_rayOrigin[2] = {rayOrigin[0], rayOrigin[1]};
    Double_t Z_rayDirection[2] = {rayDirection[0], rayDirection[1]};
    Double_t Z_boxOrigin[2] = {boxOrigin[0], boxOrigin[1]};
    Double_t Z_boxSize[2] = {boxSize[0], boxSize[1]};
    isIntersectingZ = isRayIntersectingRectangle(Z_rayOrigin, Z_rayDirection, Z_boxOrigin, Z_boxSize);

    return (isIntersectingX && isIntersectingY && isIntersectingZ);
}

Double_t distance(Double_t* point1, Double_t* point2){
    Double_t distance = 0;
    for (size_t i = 0; i < 3; i++)
    {
        distance += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    distance = std::sqrt(distance);
    return distance;
}

Double_t ocillationProbability(Double_t E,Double_t L,int begin_flavor,int end_flavor){
    // e,mu,tau as 0,1,2
    if (begin_flavor==0&&end_flavor==1)
    {
        return SIN_2_THETA_13_SQUARE * SIN_THETA_23_SQUARE * std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E)*std::sin(1.27 * DELTA_M_32_SQUARE * L /1000/ E);
    }
    else if (begin_flavor==1&&end_flavor==0)
    {
        return SIN_2_THETA_13_SQUARE * SIN_THETA_23_SQUARE * std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E)*std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E);
    }
    else if (begin_flavor==1 && end_flavor==2)
    {
        return SIN_2_THETA_23_SQUARE*COS_THETA_13_POWER4*std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E)*std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E);
    }
    else if (begin_flavor==2 && end_flavor==1)
    {
        return 0;
    }
    else if (begin_flavor==0 && end_flavor==2)
    {
        return SIN_2_THETA_13_SQUARE*COS_THETA_23_SQUARE*std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E)*std::sin(1.27 * DELTA_M_32_SQUARE * L/1000 / E);
    }
    else if (begin_flavor==2 && end_flavor==0){
        return 0;
    }
    else{
        return 0;
    }
}
// #include <iostream>
// #include <TFile.h>
// #include <TVectorT.h>
// #include <math.h>
// // #include <vector.h>
// // #include "myio.h" //just for test
// void PrintVector2(Double_t *vector){
//     Size_t dimension = 2; // sizeof(vector);
//     printf("[ ");
//     for (size_t i = 0; i < dimension; i++)
//     {
//         printf("%g ", vector[i]);
//     }
//     printf("]\n");
// }
// void PrintVector3(Double_t *vector){
//     Size_t dimension = 3; // sizeof(vector);
//     printf("[ ");
//     for (size_t i = 0; i < dimension; i++)
//     {
//         printf("%g ", vector[i]);
//     }
//     printf("]\n");
// }
// //norm of vector
// Double_t norm(Double_t* vector, Size_t dimension){
//     Double_t norm = 0;
//     // Size_t dimension = sizeof(vector);
//     // printf("dimension: %d\n", dimension);
//     for (size_t i = 0; i < dimension ; i++)
//     {
//         norm += vector[i] * vector[i];
//     }
//     norm=std::sqrt(norm);
//     return norm;
// }

// //multiplication of vector and scalar
// Double_t* multiply(Double_t* vector, Double_t scalar, Size_t dimension){
//     // Size_t dimension = sizeof(vector);
//     Double_t* result = new Double_t[2];
//     for (size_t i = 0; i < dimension; i++)
//     {
//         result[i] = vector[i] * scalar;
//     }
//     // delete[] result;
//     return result;
// }

// //axis: 0->x, 1->y, 2->z
// Double_t* Vec3to2(Double_t* vector,int axis){
//     Double_t* result = new Double_t[2];
//     if (axis==0)
//     {
//         result[0] = vector[1];
//         result[1] = vector[2];
//     }
//     else if (axis==1)
//     {
//         result[0] = vector[0];
//         result[1] = vector[2];
//     }
//     else if (axis==2)
//     {
//         result[0] = vector[0];
//         result[1] = vector[1];
//     }
//     else
//     {
//         printf("Error: axis should be 0, 1 or 2\n");
//     }
//     return result;
// }

// //check if ray is intersecting rectangle
// bool isRayIntersectingRectangle(Double_t* rayOrigin, Double_t* rayDirection, Double_t* rectangleOrigin, Double_t* rectangleSize){
//     if (norm(rayDirection,2)==0){
//         if (rayOrigin[0] >= rectangleOrigin[0] && rayOrigin[0] <= rectangleOrigin[0] + rectangleSize[0] && rayOrigin[1] >= rectangleOrigin[1] && rayOrigin[1] <= rectangleOrigin[1] + rectangleSize[1])
//         {
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//     }
//     Double_t* rayNormal;
//     Double_t tmin, tmax, ymin, ymax;
//     rayNormal = multiply(rayDirection, 1.0 / norm(rayDirection,2),2);
//     // PrintVector2(rayNormal);
//     tmin = (rectangleOrigin[0] - rayOrigin[0]) / rayNormal[0];
//     tmax = (rectangleOrigin[0] + rectangleSize[0] - rayOrigin[0]) / rayNormal[0];
//     if (tmin > tmax)
//     {
//         Double_t temp = tmin;
//         tmin = tmax;
//         tmax = temp;
//     }
//     ymin = rayOrigin[1] + tmin * rayNormal[1];
//     ymax = rayOrigin[1] + tmax * rayNormal[1];
//     if (ymin>rectangleOrigin[1]+rectangleSize[1] || ymax<rectangleOrigin[1])
//     {
//         return false;
//     }
//     return true;

// }

// //check if ray is intersecting box region
// bool isRayIntersectingBox(Double_t* rayOrigin, Double_t* rayDirection, Double_t* boxOrigin, Double_t* boxSize){
//     bool isIntersectingX, isIntersectingY, isIntersectingZ;
    
//     Double_t X_rayOrigin[2] = {rayOrigin[1], rayOrigin[2]};
//     Double_t X_rayDirection[2] = {rayDirection[1], rayDirection[2]};
//     Double_t X_boxOrigin[2] = {boxOrigin[1], boxOrigin[2]};
//     Double_t X_boxSize[2] = {boxSize[1], boxSize[2]};
//     isIntersectingX = isRayIntersectingRectangle(X_rayOrigin, X_rayDirection, X_boxOrigin, X_boxSize);

//     Double_t Y_rayOrigin[2] = {rayOrigin[0], rayOrigin[2]};
//     Double_t Y_rayDirection[2] = {rayDirection[0], rayDirection[2]};
//     Double_t Y_boxOrigin[2] = {boxOrigin[0], boxOrigin[2]};
//     Double_t Y_boxSize[2] = {boxSize[0], boxSize[2]};
//     isIntersectingY = isRayIntersectingRectangle(Y_rayOrigin, Y_rayDirection, Y_boxOrigin, Y_boxSize);

//     Double_t Z_rayOrigin[2] = {rayOrigin[0], rayOrigin[1]};
//     Double_t Z_rayDirection[2] = {rayDirection[0], rayDirection[1]};
//     Double_t Z_boxOrigin[2] = {boxOrigin[0], boxOrigin[1]};
//     Double_t Z_boxSize[2] = {boxSize[0], boxSize[1]};
//     isIntersectingZ = isRayIntersectingRectangle(Z_rayOrigin, Z_rayDirection, Z_boxOrigin, Z_boxSize);

//     return (isIntersectingX && isIntersectingY && isIntersectingZ);

//     // Double_t* X_rayOrigin = Vec3to2(rayOrigin, 0);
//     // Double_t* X_rayDirection = Vec3to2(rayDirection, 0);
//     // Double_t* X_boxOrigin = Vec3to2(boxOrigin, 0);
//     // Double_t* X_boxSize = Vec3to2(boxSize, 0);
//     // isIntersectingX = isRayIntersectingRectangle(X_rayOrigin, X_rayDirection, X_boxOrigin, X_boxSize);
//     // Double_t* Y_rayOrigin = Vec3to2(rayOrigin, 1);
//     // Double_t* Y_rayDirection = Vec3to2(rayDirection, 1);
//     // Double_t* Y_boxOrigin = Vec3to2(boxOrigin, 1);
//     // Double_t* Y_boxSize = Vec3to2(boxSize, 1);
//     // isIntersectingY = isRayIntersectingRectangle(Y_rayOrigin, Y_rayDirection, Y_boxOrigin, Y_boxSize);
//     // Double_t* Z_rayOrigin = Vec3to2(rayOrigin, 2);
//     // Double_t* Z_rayDirection = Vec3to2(rayDirection, 2);
//     // Double_t* Z_boxOrigin = Vec3to2(boxOrigin, 2);
//     // Double_t* Z_boxSize = Vec3to2(boxSize, 2);
//     // isIntersectingZ = isRayIntersectingRectangle(Z_rayOrigin, Z_rayDirection, Z_boxOrigin, Z_boxSize);

//     // // Double_t* rayNormal;
//     // // printf("◎rayDirection: "); //check output
//     // // PrintVector3(rayDirection);
//     // // printf("◎norm: %f\n",norm(rayDirection,3));
//     // // rayNormal = multiply(rayDirection, 1.0 / norm(rayDirection,3),3);
//     // // printf("◎rayNormal: "); //check output
//     // // PrintVector3(rayNormal);

//     // if (isIntersectingX && isIntersectingY && isIntersectingZ)
//     // {
//     //     return true;
//     // }
//     // else
//     // {
//     //     return false;
//     // }

// }

// //check if ray is intersecting box region in ROOT
// // bool isRayIntersectingBoxT(TVectorT<Double_t> rayOrigin, TVectorT<Double_t> rayDirection, TVectorT<Double_t> boxOrigin, TVectorT<Double_t> boxSize){
// //     Double_t* newRayOrigin = new Double_t[3];
// //     Double_t* newRayDirection = new Double_t[3];
// //     Double_t* newBoxOrigin = new Double_t[3];
// //     Double_t* newBoxSize = new Double_t[3];
// //     for (size_t i = 0; i < 3; i++)
// //     {
// //         newRayOrigin[i] = rayOrigin[i];
// //         newRayDirection[i] = rayDirection[i];
// //         newBoxOrigin[i] = boxOrigin[i];
// //         newBoxSize[i] = boxSize[i];
// //     }
// //     return isRayIntersectingBox(newRayOrigin, newRayDirection, newBoxOrigin, newBoxSize);

// // }