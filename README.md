# File introduction

-   raydetect_simple.cpp
    -   boost the coordinate from mass-center coordinate
    -   caculate particles come though gird
    -   save as csv file
    -   use`root raydetect_simple.cpp` to run 
-   lorentzBoost.cpp
    -   (NOW) cut, only left neutrino
    -   need manual input:`gSystem->Load("/home/amadeus/Software/MadGraph/ExRootAnalysis/libExRootAnalysis.so"); gSystem->Load("libPhysics");`

-   include/physRay.h & include/physRay.cpp
    -   detect if ray cross block area
    -   caculate the possibility of neutrino oscillation

-   draw.py
    -   draw the distribution of neutrino detect data(.csv) to png
    -   (Optional) Logarithmic coordinates
-   peak.py
    -   find average, max, min num of neutrino

# request

-   ROOT
-   Pandas
-   Matplotlib
-   Numpy
