import matplotlib.pyplot as plt
import numpy as np

data=np.loadtxt("edx_spectrum.csv")
plt.hist(data, bins=200)
plt.xlabel("energy (keV)")
plt.ylabel("photons")
plt.grid(True)
plt.show()

