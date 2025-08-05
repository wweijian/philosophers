
%./philo
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]

min for any time to be 60 

< TEST 1 -- 1 philo>

%./philo 1 x y z a

0 philo 0 is thinking
0 philo 0 has taken a fork
2853228035 philo 0 died

0 should think because philo is not eating or sleeping
then philo should die because it cannot pick up a second fork
simulation ends
remember to unlock the mutext of the first fork

TEST 2 -- EVEN PHILO

Even philo should just eat alteratively
Should they think? I think it's okay either way 

[DIE < EAT (X SLEEP)]

%./philo 1 60 70 z a

regardless of the sleep timing, the even guy shoudl die whlie waiting for a fork
because there is no time for the even guy to pick up a fork and eat due to the duration
of eat on the first guy

0 philo 0 is thinking
0 philo 1 has taken a fork
0 philo 1 is eating
60 philo 0 died
OPERATION SUCCESS!

[DIE = EAT (X SLEEP)]

%./philo 1 60 60 z a

either odd or even philo will die doesn't matter
odd dies right after eating 
even dies not being able to pick up the fork in time

[DIE > EAT]

this really depends on sleep time
the above 2 functions doesn't really care about sleep

[DIE >= EAT + SLEEP]

no one should die
because eat then sleep then eat again

[DIE < EAT + SLEEP]

odd philo dies  