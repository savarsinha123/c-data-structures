import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

NUM_POINTS = 100

path_name = os.getcwd()
file_names = os.listdir(path_name)

for file_name in file_names:
    if file_name.endswith(".csv"):
        function_name = file_name.rsplit('.', 1)[0]
        df = pd.read_csv(file_name, sep=',')
        average_interval = round(len(df) / NUM_POINTS)
        sizes = np.arange(1, len(df) + 1, 1)[::average_interval]
        times = np.array(df)
        average_times = []
        for i in range(round(len(df) / average_interval)):
            average_times.append(np.mean(times[average_interval*i:average_interval*(i+1)]))
        average_times = np.array(average_times)
        times_lim = np.percentile(times, 95)
        plt.figure()
        plt.scatter(sizes[:len(average_times)], average_times)
        plt.xlabel('Size (Number of Elements)')
        plt.ylabel('Time (Seconds)')
        plt.title(f'Time Complexity Graph for {function_name}')
        plt.xlim(0, sizes[-1])
        plt.ylim(0, times_lim)
        plt.savefig(f'figs/{function_name}.png')
        plt.close()
