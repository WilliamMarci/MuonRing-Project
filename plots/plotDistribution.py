import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt

# Load the data
edata = pd.read_csv('data/distribution_0.csv')
mdata = pd.read_csv('data/distribution_1.csv')
tdata = pd.read_csv('data/distribution_2.csv')
edata=edata.values
mdata=mdata.values
tdata=tdata.values

# Plot the data
plt.style.use('classic')
fig=plt.figure(figsize=(13,5))

ax1 = fig.add_subplot(131)
ax2 = fig.add_subplot(132)
ax3 = fig.add_subplot(133)

ax1.imshow(edata, cmap='gray', interpolation='nearest')
ax2.imshow(mdata, cmap='gray', interpolation='nearest')
ax3.imshow(tdata, cmap='gray', interpolation='nearest')

ax1.set_title('nu_e')
ax2.set_title('nu_mu')
ax3.set_title('nu_tau')


fig.savefig("figures/distribution.png", dpi=300)