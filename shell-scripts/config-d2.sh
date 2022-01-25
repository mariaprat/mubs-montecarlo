# ~/mubs/main d n epsilon min_epsilon acceptation_rate n_attempts min_beta max_beta num_beta repetitions_beta_infinite results_filename
epsilon=1
min_epsilon=1e-10
acceptation_rate=0.4
n_attempts=1e5
min_beta=1
max_beta=5000
num_beta=1000
repetitions_beta_infinite=1e6

~/mubs/main 2 2 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d2n2" &
~/mubs/main 2 3 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d2n3" &
~/mubs/main 2 4 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d2n4-1" &
~/mubs/main 2 4 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d2n4-2" &
~/mubs/main 2 4 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d2n4-3" &
