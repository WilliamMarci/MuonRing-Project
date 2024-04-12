#include <TChain.h>
#include <ExRootClasses.h>
#include <ExRootTreeReader.h>
#include <TClonesArray.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include <TLorentzVector.h>

void cutsample()
{
    TLorentzVector v;
    auto file = new TFile("output.root", "RECREATE");
    auto tree = new TTree("tree", "tree");

    // Int_t nu_pid;
    std::vector<Int_t> nu_pid;
    // Float_t nu_px, nu_py, nu_pz, nu_e;
    std::vector<Float_t> nu_px, nu_py, nu_pz, nu_e;
    tree->Branch("nu_pid", &nu_pid );
    tree->Branch("nu_px",  &nu_px  );
    tree->Branch("nu_py",  &nu_py  );
    tree->Branch("nu_pz",  &nu_pz  );
    tree->Branch("nu_e",   &nu_e   );

    auto LHEF = new TChain("LHEF");
    LHEF->Add("/home/amadeus/Test/projectRingConfirm/muon_t_1.root");
    LHEF->Add("/home/amadeus/Test/projectRingConfirm/muon_t_2.root");
    LHEF->Add("/home/amadeus/Test/projectRingConfirm/muon_t_3.root");
    LHEF->Add("/home/amadeus/Test/projectRingConfirm/muon_t_4.root");
    // [TODO] Add more files if needed.
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
        if (ientry % 1000 == 0) std::cout << "Processing event " << ientry << std::endl;

        auto event = dynamic_cast<TRootLHEFEvent *>(eventArray->At(0));
        // [TODO] Process event here.

        Int_t nparticle = particleArray->GetEntries();
        for (Int_t iparticle = 0; iparticle < nparticle; iparticle++)
        {
            static std::vector<Int_t> nu_pid_list = {12, 14, 16};
            auto particle = dynamic_cast<TRootLHEFParticle *>(particleArray->UncheckedAt(iparticle));
            if(find(nu_pid_list.begin(), nu_pid_list.end(), particle->PID) == nu_pid_list.end()) continue;
            TVector3 boost;
            // boost.SetXYZ(0, 0, 0.997);
            // v.SetPxPyPzE(particle->Px, particle->Py, particle->Pz, particle->E);
            // v.Boost(boost);
            Double_t boost_px = v.Px();
            Double_t boost_py = v.Py();
            Double_t boost_pz = v.Pz();
            Double_t boost_e = v.E();
            nu_pid.push_back(particle->PID);
            nu_px.push_back(boost_px);
            nu_py.push_back(boost_py);
            nu_pz.push_back(boost_pz);
            nu_e.push_back(boost_e);
            // nu_px.push_back(particle->Px);
            // nu_py.push_back(particle->Py);
            // nu_pz.push_back(particle->Pz);
            // nu_e.push_back(particle->E);
            // nu_pid particle->PID;

            // break;  // [XXX] Only the first occurance is considered.
        }
            tree->Fill();
    }

    tree->Write(nullptr, tree->kOverwrite);

    delete reader;
    delete LHEF;
    delete tree;
    delete file;
}