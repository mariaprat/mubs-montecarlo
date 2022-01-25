# ~/mubs/main d n epsilon min_epsilon acceptation_rate n_attempts min_beta max_beta num_beta repetitions_beta_infinite results_filename
epsilon=1
min_epsilon=1e-10
acceptation_rate=0.4
n_attempts=1e5
min_beta=1
max_beta=5000
num_beta=1000
repetitions_beta_infinite=1e6

~/mubs/main 9 2 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d9n2" &
~/mubs/main 9 3 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d9n3" &
~/mubs/main 9 4 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d9n4" &
~/mubs/main 9 5 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d9n5" &
~/mubs/main 9 6 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d9n6" &
