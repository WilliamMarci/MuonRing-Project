#include <TChain.h>
#include <ExRootClasses.h>
#include <ExRootTreeReader.h>
#include <TClonesArray.h>
#include <iostream>
#include <vector>
#include <algorithm>

void cut()
{
    // Create file
    auto file = new TFile("conf/sources.root", "RECREATE");
    auto tree = new TTree("tree", "tree");

    std::vector<Int_t> nu_pid;
    std::vector<Float_t> nu_px, nu_py, nu_pz, nu_e;
    // set branch
    tree->Branch("nu_pid", &nu_pid);
    tree->Branch("nu_px", &nu_px);
    tree->Branch("nu_py", &nu_py);
    tree->Branch("nu_pz", &nu_pz);
    tree->Branch("nu_e", &nu_e);

    // Read file
    auto LHEF = new TChain("LHEF");
    LHEF->Add("/home/amadeus/Test/projectRingConfirm/muon_t_1.root");

    auto reader = new ExRootTreeReader(LHEF);
    auto eventArray = reader->UseBranch("Event");
    auto particleArray = reader->UseBranch("Particle");

    size_t nentry = reader->GetEntries();
    for (Long64_t ientry = 0; ientry < nentry; ientry++)
    {
        nu_pid.clear();
        nu_px.clear();
        nu_py.clear();
        nu_pz.clear();
        nu_e.clear();

        reader->ReadEntry(ientry);
        Int_t nparticle = particleArray->GetEntries();
        for (Int_t iparticle = 0; iparticle < nparticle; iparticle++)
        {
            static std::vector<Int_t> pid_list = {-16, -14, -12, 12, 14, 16};
            auto particle = dynamic_cast<TRootLHEFParticle *>(particleArray->UncheckedAt(iparticle));
            if (find(pid_list.begin(), pid_list.end(), particle->PID) == pid_list.end())
                continue;
            nu_pid.push_back(particle->PID);
            nu_px.push_back(particle->Px);
            nu_py.push_back(particle->Py);
            nu_pz.push_back(particle->Pz);
            nu_e.push_back(particle->E);
        }
        tree->Fill();
    }
    tree->Write(nullptr, tree->kOverwrite);

    delete reader;
    delete LHEF;
    delete tree;
    delete file;
}