# Philosophers

**Philosophers** is a multithreading simulation of the classic **Dining Philosophers problem**, written in C using **POSIX threads** and **mutexes**.

The goal of the project is to simulate philosophers who alternately think, eat, and sleep — while competing for limited shared resources (forks). The challenge lies in managing **concurrency**, **race conditions**, and **deadlock prevention**.

## Features
- Accurate simulation of philosopher behavior with configurable parameters
- Thread-safe logging system to track each philosopher’s actions
- Precision timing to control sleep/eat/think durations
- Optional input handling for number of meals per philosopher
- Deadlock-free design using mutex locking and careful resource management

## What I Learned
- POSIX threads and synchronization primitives (`pthread_create`, `pthread_mutex`)
- Deadlock avoidance strategies
- Time-sensitive thread scheduling and event simulation
- Writing efficient and readable multithreaded code in C

## Technologies
- Language: **C**
- Concurrency: **pthreads**, **mutexes**
- Build system: `Makefile`
- Platform: Linux / macOS

## Status
Complete. Fully tested and compliant with project constraints (e.g., no deadlocks, consistent timing).
