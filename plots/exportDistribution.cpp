#include <TChain.h>
#include <TSystem.h>
#include "/home/amadeus/Test/MuonRing-Project/include/mycsv.h"



void exportDistribution(){
    gSystem->Load("/home/amadeus/Test/MuonRing-Project/include/mycsv.so");
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
    int x = 0;
    int y = 0;
    for (Long64_t i = 0; i < nentry; i++)
    {
        tree->GetEntry(i);
        if (x < xBlock)
            x = xBlock;
        if (y < yBlock)
            y = yBlock;
    }
    // MeshgridLayer meshgrid(23, 10, 3, "distribution");
    MeshgridLayer meshgrid(x + 1, y + 1, 3, "distribution");
    // std::cout<< nentry << std::endl;
    for (Long64_t i = 0; i < nentry; i++)
    {
        tree->GetEntry(i);
        for (size_t j = 0; j < nu_pid->size(); j++)
        {   
            // std::cout<<nu_pid->at(j)<<std::endl;
            double value =meshgrid.GetElement(xBlock, yBlock, getVal(nu_pid->at(j)));
            value = value + 1;
            meshgrid.Element(xBlock, yBlock, getVal(nu_pid->at(j)), value);
        }
    }
    // std::cout<< nentry << std::endl;
    meshgrid.OutputCSV("data/");
    // delete tree;
    std::cout<<"\rExport Distribution"<<std::endl;
    tree->Delete();
}