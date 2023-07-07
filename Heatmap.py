"""
Heatmap.py
Revised 7/5/2023
Nathan Wiley - nwiley@uco.edu
"""

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import os

data = pd.read_csv('empty_field_img.csv')                                     # Load the CSV file into a pandas DataFrame
sns.heatmap(data, cmap = "viridis", xticklabels = False, yticklabels = False) # Generate the heatmap using Seaborn
plt.savefig('heatmap.png')                                                    # Save the heatmap as an image file