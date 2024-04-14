#ifndef MYCSV_H
#define MYCSV_H
#include <iostream>
#include <fstream>
#include <vector>
class MeshgridLayer
{
    private:
        int layers;
        int xnum, ynum;
        std::string name;
        std::vector<double> data;
        // std::vector<std::vector<Double_t>> data;
    public:
        MeshgridLayer();
        MeshgridLayer(int x, int y, int layer,std::string name);
        double GetElement(int i, int j, int layer);
        void Element(int i, int j, int layer, double value);
        void OutputCSV(std::string path = "");
};

#endif