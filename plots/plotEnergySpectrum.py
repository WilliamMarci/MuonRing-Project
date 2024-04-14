import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

# Load the data
    
    
try:
    edata = pd.read_csv('data/energySpectrum0.csv',header=None)
    edata=edata.values
except:
    edata=np.array([0])
try:
    mdata = pd.read_csv('data/energySpectrum1.csv',header=None)
    mdata=mdata.values
except:
    mdata=np.array([0])
try:
    tdata = pd.read_csv('data/energySpectrum2.csv',header=None)
    tdata=tdata.values
except:
    tdata=np.array([0])
# Plot the data
plt.style.use('classic')
# fig=plt.figure(figsize=(9, 3.5),sharex=True, sharey=True, squeeze=True)

fig,ax=plt.subplots(1,3,figsize=(13, 5),sharex=True, sharey=True, squeeze=True)
# ax[0] = fig.add_subplot(131)
# ax[1] = fig.add_subplot(132)
# ax[2] = fig.add_subplot(133)

ax[0].hist(edata[0], bins=50, histtype='step')
ax[1].hist(mdata[0], bins=50, histtype='step')
ax[2].hist(tdata[0], bins=50, histtype='step')

ax[0].set_title('nu_e')
ax[1].set_title('nu_mu')
ax[2].set_title('nu_tau')
ax[0].set_xlabel('GeV')
ax[1].set_xlabel('GeV')
ax[2].set_xlabel('GeV')
# ax[0].tick_params(labelsize=4)
# ax[1].tick_params(labelsize=4)
# ax[2].tick_params(labelsize=4)
x=2*int(sys.argv[1])-120
y=120-2*int(sys.argv[2])

#set title
plt.suptitle('Energy Spectrum'+'['+str(x)+','+str(y)+']')
fig.savefig("figures/energy.png", dpi=300)