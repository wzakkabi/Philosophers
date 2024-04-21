# Philosophers

## Description
The "Philosophers" project is an implementation of the dining philosophers problem in concurrent programming. This project involves simulating a scenario where a certain number of philosophers sit at a table with a bowl of spaghetti. Each philosopher alternates between thinking and eating, but they must contend with a limited number of forks on the table. The goal is to avoid deadlock and starvation while ensuring that each philosopher can eat without conflicts.

## Features
- Implements the dining philosophers problem using threads and mutexes.
- Ensures that philosophers follow the rules of alternately thinking and eating.
- Prevents deadlock and starvation by implementing proper synchronization mechanisms.
- Provides options for adjusting the number of philosophers, simulation duration, and other parameters.

## Getting Started
To run the "Philosophers" simulation, follow these steps:

1. Clone the repository to your local machine:
```shell
git clone https://github.com/wzakkabi/Philosophers.git
```
2. Compile the source files:
```shell
make
```
3. Run the executable with appropriate arguments:
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```shell
./philo 10 400 200 200
```

## Controls
- Use command-line arguments to adjust simulation parameters such as the number of philosophers, time intervals for actions, and the number of times each philosopher must eat before the simulation ends.

## Visualization
Optionally, you can visualize the simulation using a graphical representation of the dining table and philosophers. Visualization can aid in understanding the behavior of the philosophers and detecting potential issues such as deadlock or starvation.

## Credits
The "Philosophers" project was created by [walid zakkabi]. Special thanks to [(https://www.1337.ma/en/) and (https://www.42network.org)] for their contributions and support.

## Contact
If you have any questions, suggestions, or issues regarding "Philosophers", feel free to contact [wzakkabi@gmail.com] or open an issue on the GitHub repository.
