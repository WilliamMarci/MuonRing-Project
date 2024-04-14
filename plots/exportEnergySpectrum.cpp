#include <TChain.h>
#include <TSystem.h>
#include <fstream>
#include <iostream>
#include <vector>

// #include "/home/amadeus/Test/MuonRing-Project/include/mycsv.h"

void exportEnergySpectrum(int x,int y ){
    // gSystem->Load("/home/amadeus/Test/MuonRing-Project/include/mycsv.so");
    auto tree = new TChain("save");
    tree->Add("data/distribution.root");
    std::map<int, int> lookupTable = {{12, 0}, {-12, 0}, {14, 1}, {-14, 1},{16, 2}, {-16, 2}};
    auto getVal = [&lookupTable](int key) { return lookupTable.count(key) ? lookupTable[key] : -1; };
    Long64_t nentry = tree->GetEntries();
    Int_t xBlock, yBlock;
    // std::cout<<nentry<<std::endl;
    std::vector<Int_t> *nu_pid=0, *part_k=0;
    // Int_t nu_pid[100], part_k[100];
    // Double_t nu_px[100], nu_py[100], nu_pz[100], nu_e[100];
    std::vector<Double_t> *nu_px=0, *nu_py=0, *nu_pz=0, *nu_e=0;
    // auto nu_px, nu_py, nu_pz, *nu_e;
    
    tree->SetBranchAddress("nu_pid", &nu_pid);
    tree->SetBranchAddress("nu_px", &nu_px);
    tree->SetBranchAddress("nu_py", &nu_py);
    tree->SetBranchAddress("nu_pz", &nu_pz);
    tree->SetBranchAddress("nu_e", &nu_e);
    tree->SetBranchAddress("part_k", &part_k);
    tree->SetBranchAddress("xBlock", &xBlock);
    tree->SetBranchAddress("yBlock", &yBlock);

    std::vector<double> energySpectrum0;
    std::vector<double> energySpectrum1;
    std::vector<double> energySpectrum2;

    for(int ientry = 0; ientry < nentry; ientry++){
        tree->GetEntry(ientry);
        if (xBlock == x && yBlock == y){
            for (size_t j = 0; j < nu_pid->size(); j++){
                if (getVal(nu_pid->at(j)) == 0){
                    energySpectrum0.push_back(nu_e->at(j));// what you need
                }
                else if (getVal(nu_pid->at(j)) == 1){
                    energySpectrum1.push_back(nu_e->at(j));
                }
                else if (getVal(nu_pid->at(j)) == 2){
                    energySpectrum2.push_back(nu_e->at(j));
                }
            }
        }
        
    }
    std::ofstream file0("data/energySpectrum0.csv");
    std::ofstream file1("data/energySpectrum1.csv");
    std::ofstream file2("data/energySpectrum2.csv");
    for (size_t i = 0; i < energySpectrum0.size(); i++){
        file0<<energySpectrum0[i]<<",";
    }
    for (size_t i = 0; i < energySpectrum1.size(); i++){
        file1<<energySpectrum1[i]<<",";
    }
    for (size_t i = 0; i < energySpectrum2.size(); i++){
        file2<<energySpectrum2[i]<<",";
    }
    file0.close();
    file1.close();
    file2.close();
}