#include <TFile.h>
#include <TTree.h>
#include <ExRootTreeReader.h>
#include <TClonesArray.h>
#include <TSystem.h>

void cut()
{
    gSystem->Load("");
    TFile *origin_file = new TFile("origin.root", "READ");
}