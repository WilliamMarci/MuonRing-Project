
#include <TChain.h>
#include <ExRootClasses.h>
#include <ExRootTreeReader.h>
#include <TClonesArray.h>
#include <iostream>
#include <vector>
#include <algorithm>

void test()
{
    auto file = new TFile("branch.root", "RECREATE");
    // auto file2 = new TFile("branch2.root", "RECREATE");
    auto tree = new TTree("tree", "tree");
    std::vector<Int_t> nu_pid, part_k;
    std::vector<Float_t> nu_px, nu_py, nu_pz, nu_e;
    Int_t xBlock, yBlock;
    tree->Branch("nu_pid", &nu_pid);
    tree->Branch("nu_px", &nu_px);
    tree->Branch("nu_py", &nu_py);
    tree->Branch("nu_pz", &nu_pz);
    tree->Branch("nu_e", &nu_e);
    tree->Branch("part_k", &part_k);
    tree->Branch("xBlock", &xBlock);
    tree->Branch("yBlock", &yBlock);

    // std::cout<<"Start"<<std::endl;
    for (size_t i = 0; i < 23; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            for (Int_t k = 0; k < 10; k++)
            {
                // std::cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<std::endl;
                xBlock = i;
                yBlock = j;
                part_k.clear();
                nu_pid.clear();
                nu_px.clear();
                nu_py.clear();
                nu_pz.clear();
                nu_e.clear();
                for (size_t n = 0; n < 100; n++)
                {

                    Float_t nm = 1.0;
                    part_k.push_back(k);
                    nu_pid.push_back(nm);
                    nu_px.push_back(nm);
                    nu_py.push_back(nm);
                    nu_pz.push_back(nm);
                    nu_e.push_back(nm);
                }
            }
            tree->Fill();
        }
    }
    tree->Write();
    // tree->Write(nullptr, tree->kOverwrite);
    // file->Close();
    std::cout << "Done" << std::endl;
    delete tree;
    delete file;
}