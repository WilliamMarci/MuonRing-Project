//standard library
#include <fstream>
#include <iostream>
//ROOT library
#include <TFile.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TTree.h>
#include <TVector3.h>
//User library
#include "include/physRay.h"

void ray()
{
    //open muon source
    TFile *sourec_root = new TFile("source.root", "RECREATE");
    
}