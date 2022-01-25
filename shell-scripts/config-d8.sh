# ~/mubs/main d n epsilon min_epsilon acceptation_rate n_attempts min_beta max_beta num_beta repetitions_beta_infinite results_filename
epsilon=1
min_epsilon=1e-10
acceptation_rate=0.4
n_attempts=1e5
min_beta=1
max_beta=5000
num_beta=1000
repetitions_beta_infinite=1e6

~/mubs/main 8 2 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n2" &
~/mubs/main 8 3 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n3" &
~/mubs/main 8 4 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n4" &
~/mubs/main 8 5 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n5" &
~/mubs/main 8 6 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n6" &
~/mubs/main 8 7 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n7" &
~/mubs/main 8 8 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n8" &
~/mubs/main 8 9 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n9" &
~/mubs/main 8 10 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n10-1" &
~/mubs/main 8 10 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n10-2" &
~/mubs/main 8 10 $epsilon $min_epsilon $acceptation_rate $n_attempts $min_beta $max_beta $num_beta $repetitions_beta_infinite "d8n10-3" &
