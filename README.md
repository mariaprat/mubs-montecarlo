This is a Monte Carlo method that finds mutually unbiased bases using Bell inequalities.

# Usage

To build the project:

```bash
make
```

To check the existence of 3 MUBs in dimension 2:

```bash
# ./main d n $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite filename
./main 2 3 1 1e-10 0.4 1e4 1 5000 1000 1e4 "d2n3" 
```

To plot the results:

```bash
python3 plot_results.py d2n3
```
