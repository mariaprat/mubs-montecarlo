from statistics import mean
import sys
import os
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

def read_file(filename):
    with open(filename, 'r') as f:
        n = int(f.readline())
        d = int(f.readline())
        min_epsilon = float(f.readline())
        initial_epsilon = float(f.readline())
        acceptation_rate = float(f.readline())
        n_attempts = int(float(f.readline()))
        min_beta = float(f.readline())
        max_beta = float(f.readline())
        num_beta = int(float(f.readline()))
        initial_states = [[[] for i in range(d)] for i in range(n)]
        for i in range(n):
            for j in range(d):
                initial_states[i][j] = f.readline().split(' ')
                initial_states[i][j].pop()
            f.readline()
        f.readline()
        time_beta_finite = float(f.readline())
        time_beta_infinite = float(f.readline())
        beta_values = [float(num) for num in f.readline().split(' ')[:-1]]
        mean_values = [float(num) for num in f.readline().split(' ')[:-1]]
        result = float(f.readline())
        existence_result = float(f.readline())
        best_states = [[[] for i in range(d)] for i in range(n)]
        for i in range(n):
            for j in range(d):
                best_states[i][j] = f.readline().split(' ')[:-1]
            f.readline()
        f.readline()
        pairwise_scalar_products = [[[[] for i in range(d)] for i in range(n)] for i in range(n)]
        for i in range(n):
            for j in range(n):
                for k in range(d):
                    pairwise_scalar_products[i][j][k] = f.readline().split(' ')[:-1]
                f.readline()
            f.readline()
        f.readline()
    return [n, d, min_epsilon, initial_epsilon, acceptation_rate, n_attempts, min_beta, max_beta, 
    num_beta, time_beta_finite, time_beta_infinite, beta_values, mean_values, result, existence_result, 
    os.path.basename(filename)]

for i in range(1, len(sys.argv)):
    filename = sys.argv[i]
    results = read_file(filename)
    d = results[1]
    beta_values = results[11]
    mean_values = results[12]
    num_beta = results[8]
    result = results[13]
    existence_result = results[14] / d

    beta_finite_values = np.array(beta_values[:num_beta])
    mean_finite_values = np.array(mean_values[:num_beta]) / d

    plt.plot(beta_finite_values, mean_finite_values, linewidth=0.8)

plt.plot(beta_finite_values, [existence_result] * len(beta_finite_values), 'r--', linewidth=0.8)

plt.xlabel(r'$\beta$')
plt.ylabel(r'$\overline{W}$')

plt.savefig("plot.png", dpi=700)