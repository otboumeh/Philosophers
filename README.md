# Philosophers Project 🧘‍♂️🍴

The **Philosophers** project is a classic concurrency problem that explores the challenges of synchronization and thread management. Inspired by Edsger Dijkstra's famous *Dining Philosophers Problem*, this project simulates a group of philosophers sitting around a table, alternating between thinking, eating, and sleeping. The goal is to manage shared resources (forks) in a way that avoids deadlocks and ensures fairness.

## Features ✨

- **Multithreading**: Each philosopher is represented as a thread, running independently.
- **Resource Sharing**: Forks (shared resources) are managed to prevent conflicts using mutexes.
- **Deadlock Prevention**: Implements techniques to ensure the simulation runs smoothly without getting stuck.
- **Customizable Parameters**: Adjust the number of philosophers, time limits, and more via program input.

## How It Works 🔧

1. Philosophers sit in a circle, with one fork placed between each pair.
2. Each philosopher alternates between three states:
   - **Thinking**: Pondering life's great mysteries.
   - **Eating**: Picking up the two forks (left and right) to eat.
   - **Sleeping**: Resting after a meal.
3. Philosophers can only eat if they have access to both forks. Mutex locks ensure that forks are properly shared between philosophers.

## Project Constraints 🛠️

- No global variables are allowed, ensuring all data is passed explicitly.
- Efficient and minimal use of system resources.
- Handles edge cases like starvation and improper timing.

## Usage 🚀

1. Clone the repository:
   ```bash
   git@github.com:otboumeh/Philosophers.git
   cd philosophers
2.  Compile the project:
    ```bash
    Make
3. Run the program with the following arguments:
   ```bash
   ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals (optional)]
  Example:
  ```bash
    ./philo 5 800 200 200
```
### Arguments Explanation

- **number_of_philosophers**: Total number of philosophers (and forks).
- **time_to_die**: Time (in milliseconds) a philosopher can survive without eating.
- **time_to_eat**: Time (in milliseconds) a philosopher takes to eat.
- **time_to_sleep**: Time (in milliseconds) a philosopher takes to sleep.
- **number_of_meals (optional)**: If specified, the simulation ends once each philosopher eats this many times.

---

### Learning Outcomes 📚

- Mastery of multithreading concepts using **pthread**.
- Advanced synchronization techniques like mutexes.
- Understanding and handling race conditions, deadlocks, and starvation.
- Practical application of algorithmic thinking in systems programming.

 ---
 ## Contributing 🤝

Feel free to open issues or submit pull requests. Contributions and feedback are always welcome!

