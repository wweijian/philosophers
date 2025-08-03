every time a thing begins: 
odd eats
even thinks

eat:
grab left fork, right fork
-> left fork prints take fork, right fork prints eating
increments timing (usleep) -> not super necessary but it helps to synchronize the process

// 03.08.25

1) should all the philosopher maintain on their individual thread? is it possible?
	-> check in school
	if they do: then they need to call ph_eat from the ph_think
	if they don't, then we can detach them and put them at the end of the queue

2) the odd philo problem
	how do i get the one extra person to wait another eating time? 
	current thought: just add one extra think at the front 
	but i also need to account for the fact that now everybody has to think twice as long

3) how long to think in general?

4) how should the sim end? 
	monitoring script starts, it shoudl check for two things:
		>> max_eat, if everyone has eaten max
		>> end_sim = 1
		>> philo died 

5) A message announcing a philosopher’s death must be displayed within 10 ms of
	their actual death
	need a way to calculate the death

---
3 scenarios in terms of number of philosopher
	1) solo --> sure die
	2) even --> takes 1 turn to eat again
	3) odd --> takes 2 turns to eat again

		[i want to add a return from print mutex so that no one can print again] // okay i can't this will cause segfault
		i want to add a return from print that says if someone dies, i'll stop printing
		--> i also think changes need to make to the monitoring script so that people have time to die properly 
		i can just use the monitoring script to detach everyone too i guess

Always print first then usleep

6 scenarios in terms of eat/sleep/die
for even:
	if time_to_eat < time_to_die (odd: eat, even: thinks then die, no sleep)
	if time_to_eat + time_to_sleep < time_to_die (odd: eat, sleep then die)
	if time_to_eat + time_to_sleep => time_to_die (no die)
for odd:
	if time_to_eat < time_to_die (odd: eat, even: thinks then die, no sleep)
	if time_to_eat * 2 < time_to_die (odd: eat and sleep, even: eat, last: die)
	only survives if time_to_eat > 2 x time_to_die 