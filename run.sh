#!/bin/zsh

clear
if [ "$1" = "n" ]; then
	norminette
else
	echo
	if make; then
		if [ "$1" = "-v" ]; then
			valgrind ./philo/philo "${@:2}"
		elif [ "$5" = "-v" ]; then
			valgrind ./philo/philo "$@[1, 4]"
		elif [ "$6" = "-v" ]; then
			valgrind ./philo/philo "$@[1, 5]"
		else 
			./philo/philo "$@"
		fi
	fi
fi

echo "completed"