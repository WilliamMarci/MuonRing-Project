#include "mycsv.h"
#include <iostream>
#include <fstream>
#include <vector>
// #include <TClonesArray.h>

MeshgridLayer::MeshgridLayer(){
    this->layers = 1;
    this->xnum = 2;
    this->ynum = 2;
}
MeshgridLayer::MeshgridLayer(int x, int y, int layer, std::string name){
    this->layers = layer;
    this->xnum = x;
    this->ynum = y;
    this->name = name;
    this->data.resize(layer*x*y);
}
double MeshgridLayer::GetElement(int i, int j, int layer){
    return this->data[layer*xnum*ynum+i*ynum+j];
}
void MeshgridLayer::Element(int i, int j, int layer, double value){
    this->data[layer*xnum*ynum+i*ynum+j] = value;
}
void MeshgridLayer::OutputCSV(std::string path){
    // std::ofstream file;
    for (int k = 0; k < this->layers;k++){
        std::string filename;
        filename = path + this->name + "_" + std::to_string(k) + ".csv";
        std::ofstream files(filename);
        for (int i = 0; i < this->xnum; i++)
        {
            for (int j = 0; j < this->ynum; j++){
                files<<this->data[k*xnum*ynum+i*ynum+j]<<",";
            }
            files<<"\n";
        }
        files.close();
    }
}