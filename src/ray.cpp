// standard library
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>
// User library
// #include "include/physRay.h"
#include "/home/amadeus/Test/MuonRing-Project/include/physRay.h"

void ray()
{
    // open muon source
    auto source_root = new TFile("conf/sources.root", "READ");
    auto source_tree = dynamic_cast<TTree *>(source_root->Get("tree"));
    Long64_t source_entries = source_tree->GetEntries();

    // create output file
    auto save_root = new TFile("data/distribution.root", "RECREATE");
    auto save_tree = new TTree("save", "save");

    // add save branch
    save_root->cd();
    Int_t xBlock, yBlock;
    std::vector<Int_t> nu_pid, part_k;
    std::vector<Double_t> nu_px, nu_py, nu_pz, nu_e;
    save_tree->Branch("nu_pid", &nu_pid);
    save_tree->Branch("nu_px", &nu_px);
    save_tree->Branch("nu_py", &nu_py);
    save_tree->Branch("nu_pz", &nu_pz);
    save_tree->Branch("nu_e", &nu_e);
    save_tree->Branch("part_k", &part_k);
    save_tree->Branch("xBlock", &xBlock);
    save_tree->Branch("yBlock", &yBlock);

    // read source file
    source_root->cd();
    Int_t src_pid;
    Double_t src_e, src_px, src_py, src_pz;
    source_tree->SetBranchAddress("PID", &src_pid);
    source_tree->SetBranchAddress("PX", &src_px);
    source_tree->SetBranchAddress("PY", &src_py);
    source_tree->SetBranchAddress("PZ", &src_pz);
    source_tree->SetBranchAddress("E", &src_e);

    // muonring env arguments
    Double_t ringRadius = 100.0; // meter
    Double_t mirgin = 20.0;
    Double_t xRange[2] = {-ringRadius - mirgin, ringRadius + mirgin};
    Double_t yRange[2] = {-ringRadius - mirgin, ringRadius + mirgin};
    Double_t zRange[2] = {-1, 1};

    // detector arguments
    int nx = 120;
    int ny = 120;
    int knum = 100;
    Double_t xStep = (xRange[1] - xRange[0]) / nx;
    Double_t yStep = (yRange[1] - yRange[0]) / ny;
    Double_t zStep = (zRange[1] - zRange[0]);
    Double_t kStep = 2 * TMath::Pi() / knum;

    // Init Boost variable
    TLorentzVector vec;
    Double_t boostPx = 0;
    Double_t boostPy = 0;
    Double_t boostPz = 0;
    Double_t boostE = 0;

    Double_t Ox = 0;
    Double_t Oy = 0;
    Double_t rayOrigin[3] = {0, 0, 0};

    Double_t rayDirection[3] = {0, 0, 0};
    Double_t boxOrigin[3] = {0, 0, 0};
    Double_t boxSize[3] = {0, 0, 0};
    Double_t crossDistant = 0;

    Double_t distanceOrigin = 0;

    TVector3 velocity;    // beam direction
    Double_t beta = 0.99498743710662; // the beam speed :light speed

    for (int i = 0; i < nx;i++){
        for (int j = 0; j < ny;j++){
            std::cout<<"\rProcess:" << i*nx+j <<"/"<<nx*ny<<std::flush;
            for (int k = 0; k < knum;k++){
                xBlock = i;
                yBlock = j;
                part_k.clear();
                nu_pid.clear();
                nu_px.clear();
                nu_py.clear();
                nu_pz.clear();
                nu_e.clear();
                for (int n = 0; n < source_entries;n++){
                    source_tree->GetEntry(n);
                    vec.SetPxPyPzE(src_px, src_py, src_pz, src_e);
                    velocity.SetXYZ(beta*TMath::Sin(k*kStep),-beta*TMath::Cos(k*kStep), 0);
                    // velocity.SetXYZ(-beta,0,0);
                    vec.Boost(velocity);
                    // vec.RotateZ(k*kStep+TMath::Pi()/2);

                    boostPx = vec.Px();
                    boostPy = vec.Py();
                    boostPz = vec.Pz();
                    boostE = vec.E();
                    Ox = ringRadius * TMath::Cos(k * kStep);
                    Oy = ringRadius * TMath::Sin(k * kStep);
                    rayOrigin[0] = Ox;
                    rayOrigin[1] = Oy;
                    rayOrigin[2] = 0;

                    rayDirection[0] = boostPx/boostE;
                    rayDirection[1] = boostPy/boostE;
                    rayDirection[2] = boostPz/boostE;
                    boxOrigin[0] = xRange[0] + i * xStep;
                    boxOrigin[1] = yRange[0] + j * xStep;
                    boxOrigin[2] = zRange[0];

                    // std::cout<<"RaO"<<rayOrigin[0]<<","<<rayOrigin[1]<<","<<rayOrigin[2] <<"\n"<<"raD"<<rayDirection[0]<<","<<rayDirection[1]<<","<<rayDirection[2]<<"\n";
                    boxSize[0] = xStep;
                    boxSize[1] = yStep;
                    boxSize[2] = zStep;
                    distanceOrigin = distance(rayOrigin, boxOrigin);
                    if (isRayIntersectingBox(rayOrigin, rayDirection, boxOrigin, boxSize)){
                        part_k.push_back(k);
                        nu_pid.push_back(src_pid);
                        nu_px.push_back(boostPx);
                        nu_py.push_back(boostPy);
                        nu_pz.push_back(boostPz);
                        nu_e.push_back(boostE);
                    }
                }
                save_tree->Fill();
            }
        }
    }
    std::cout<<"\rProcess Done.             "<<std::flush;
    save_root->cd();
    save_tree->Write(nullptr, save_tree->kOverwrite);
    // source_root->Close();
    delete save_tree;
    delete save_root;
    delete source_tree;
    delete source_root;
}