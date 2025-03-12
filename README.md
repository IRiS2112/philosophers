  # 📜 Philosophers

## 📝 Description
This project implements the **Dining Philosophers problem**, a well-known synchronization challenge in computer science.
The goal is to manage multiple philosophers who alternate between **thinking**, **eating**, and **sleeping** while ensuring that no **deadlocks** or **race conditions** occur.

## 🚀 Features
- **Proper handling of threads and mutexes** to manage concurrency.
- **Prevention of deadlocks and race conditions**, ensuring smooth execution.
- **Efficient synchronization using mutexes** to avoid conflicts between philosophers.
- **Argument validation** to ensure correct usage of the program.

## 🔧 Implementation Details
- Each philosopher is represented by a **thread** that performs actions such as eating, thinking, and sleeping.
- **Forks are protected by mutexes** to ensure that no two philosophers can pick up the same fork simultaneously.
- The program includes mechanisms to ensure that philosophers **never enter a deadlock**, meaning they always eventually get to eat.
- **Printing output is synchronized** to avoid jumbled or mixed messages when multiple philosophers are printing at the same time.

## 📜 Rules
- A philosopher **must take two forks** (one in each hand) before they can eat.
- Philosophers **must alternate** between eating, sleeping, and thinking in a specific order.
- A philosopher **dies if they do not eat before `time_to_die`**.
- If the `number_of_times_each_philosopher_must_eat` argument is provided, the simulation will **end when all philosophers have eaten at least that many times**.

## 🎯 Goals of the Project
✅ To **understand** the implementation of threads and mutexes in a multi-threaded environment.
✅ To **handle synchronization and concurrency** in a way that avoids deadlocks and race conditions.
✅ To **prevent deadlocks** and ensure fair distribution of resources among philosophers.
