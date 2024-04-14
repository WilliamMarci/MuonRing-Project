source /usr/local/bin/thisroot.sh
export CPLUS_INCLUDE_PATH=$HOME/Library/ExRootAnalysis/ExRootAnalysis
export LD_LIBRARY_PATH=$HOME/Library/ExRootAnalysis
root src/cut.cpp -q -l
root src/ray.cpp -q -l
root -e 'gSystem->Load("/home/amadeus/Test/MuonRing-Project/include/mycsv.so");' -q plots/exportDistribution.cpp -l
echo "Done."