
#include <TFile.h>

// Double_t norm2D(Double_t *vector, Size_t dimension);

// Double_t * multiply(Double_t *vector, Double_t scalar, Size_t dimension);
//define constants

double SIN_2_THETA_13_SQUARE = 0.0219;
double SIN_THETA_23_SQUARE = 0.58;
double SIN_2_THETA_23_SQUARE=0.93;
double COS_THETA_23_SQUARE = 0.624;

double COS_THETA_13_POWER4 = 0.9558;
double DELTA_M_21_SQUARE = 7.39e-5;
double DELTA_M_31_SQUARE = -2.5e-3;
double DELTA_M_32_SQUARE = 2.5e-3;

Double_t* Vec3to2(Double_t *vector, int axis);

bool isRayIntersectingRectangle(Double_t *rayOrigin, Double_t *rayDirection, Double_t *rectangleOrigin, Double_t *rectangleSize);

bool isRayIntersectingBox(Double_t *rayOrigin, Double_t *rayDirection, Double_t *boxOrigin, Double_t *boxSize);

bool isRayIntersectingBox(Double_t *rayOrigin, Double_t *rayDirection, Double_t *boxOrigin, Double_t *boxSize);

Double_t distance(Double_t *point1, Double_t *point2);

Double_t ocillationProbability(Double_t E, Double_t L, int begin_flavor, int end_flavor);

#include "physRay.cpp"