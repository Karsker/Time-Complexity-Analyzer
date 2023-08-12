import matplotlib.pyplot as plt
import numpy as np

def generateGraphs(runTimes, inputVals):
    x_vals = np.array(inputVals)
    for runTime in runTimes:
        y_vals = np.array(runTime)
        arr = np.empty(len(runTime)-1, dtype=float)
        plt.plot(x_vals, y_vals)
        plt.show()
        
