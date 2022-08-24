# Philosophers

<div>
<span>
	<img src="https://img.shields.io/badge/language-00599C?logo=C&logoColor=white&style=for-the-badge">
</span>
</div>

<div style="height: 10px"></div>

## 📄 Summary

The aim of this project is to solve dining philosophers problem formulated by Edsger Dijkstra.

It is an introduction to concurrent programming demanding to solve synchronization issues using threads, mutexes and semaphores.

## 🤔 Project description

<div style="height: 10px"></div>

**Rules**

• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.

• The philosophers alternatively **eat**, **think**, or **sleep**.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

• There are also forks on the table. There are **as many forks as philosophers**.

• Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.

• **When a philosopher has finished eating,** they put their forks back on the table and **start sleeping**. **Once awake, they start thinking again**. The simulation stops when  a philosopher dies of starvation.
    
   `eat → sleep → think`

- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

<div style="height: 10px"></div>

**Arguments**

`number_of_philosophers`: The number of philosophers and also the number
of forks.

`time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die

milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

`time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

`time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.

`number_of_times_each_philosopher_must_eat` (optional argument): If all
philosophers have eaten at least *number_of_times_each_philosopher_must_eat*
times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

- Each philosopher has a number ranging from 1 to number_of_philosophers.

- Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number `N` sits between philosopher number `N - 1` and philosopher number `N + 1`.

**Logs**

Any state change of a philosopher must be formatted as follows:
- *timestamp_in_ms X* has taken a fork
- *timestamp_in_ms X* is eating
- *timestamp_in_ms X* is sleeping
- *timestamp_in_ms X* is thinking
- *timestamp_in_ms X* died
Replace ***timestamp_in_ms*** with the current timestamp in milliseconds and ***X*** with the philosopher number.

### Requirements
<div style="height: 10px"></div>

**Mandatory part**

> **Every philosopher should be a thread**
>
> There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
>
> To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

**Bonus part**

> All the forks are put in the middle of the table.
>
> They have no states in memory but the number of available forks is represented by a semaphore.
>
> Each philosopher should be a process. But the main process should not be a philosopher.

## 🏁 How to run

<code>cd</code> to philo or philo_bonus folder

<code>make</code>

**Example**

	./philo_bonus 5 800 200 200

## 🛠 Tests

<details>
<div style="height: 10px"></div>
<summary>🔗 References</summary>
<div style="height: 10px"></div>

- [Philosophers visualizer](https://github.com/nafuka11/philosophers-visualizer)

- [ywake/Philosophers](https://github.com/ywake/Philosophers)

</details>

<div style="height: 10px"></div>

	./philo 2 400 200 200 - should die

	./philo 5 620 200 200 - shouldn't die

	./philo 4 410 200 200 10 - shouldn't die - eat 10 times

	./philo 4 410 200 200 10 - shouldn't die

	./philo 5 600 150 150 - shouldn't die

	./philo 105 800 200 200 - shouldn't die

	./philo 4 310 200 200 10 - shouldn't die

	./philo 5 800 200 200 7 | grep eating | wc -l

	//to count number of eatings use setbuf(stdout, NULL) in your main function
	./philo_bonus 5 800 200 200 7 | grep eating | wc -l