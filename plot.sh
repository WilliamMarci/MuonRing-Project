#which point x, y
python plots/plotDistribution.py
echo "Plot distribution done."
if [ "$1" != "" ] && [ "$2" != "" ];
then  
echo "Getting energy spectrum for point $1, $2..."
root  -e 'gSystem->Load("/home/amadeus/Test/MuonRing-Project/include/mycsv.so");' -b -q -l  "plots/exportEnergySpectrum.cpp+($1,$2)"
# rm plots/exportEnergySpectrum_cpp.d
# rm plots/exportEnergySpectrum_cpp.so
# rm plots/exportEnergySpectrum_cpp_ACLiC_dict_rdict.pcm
echo "Plotting energy spectrum for point $1, $2..."
python plots/plotEnergySpectrum.py $1 $2
echo "Done."
fi