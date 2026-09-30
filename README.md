<div align="center">

# OS-Fall-26

---

### Operating Systems concepts, in runnable C++.

A collection of **small, self-contained Linux programs** written while working through an Operating Systems course — processes, threads, and IPC. Every file does one thing, prints what happened, and can be compiled and run on its own.

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)](https://isocpp.org/)[![Linux](https://img.shields.io/badge/Linux-POSIX-FCC624?style=flat-square&logo=linux&logoColor=black)](https://www.gnu.org/software/libc/)[![CMake](https://img.shields.io/badge/CMake-4.x-064F8C?style=flat-square&logo=cmake&logoColor=white)](https://cmake.org/)

</div>

---

## Why this repo?

Textbook explanations of `fork()`, mutexes, and shared memory are easy to skim and easy to forget. Each example here is a few dozen lines you can compile, run, and watch — zombie processes you can actually see, race conditions that actually lose updates.

---

## Features

### Process Operations

`fork()`, `exec()` family, `wait()`. Includes a real **zombie process** and a real **orphan process**, plus a three-level process tree built with nested forks.

### Threads

From raw `pthreads` up to `std::thread`, then synchronization: a race condition with no lock, the same race fixed with a mutex, `std::lock_guard`, thread-local storage, and a **bounded producer/consumer** using condition variables.

### Thread Pool

A compact `ThreadPool` with a shared task queue, worker threads, and graceful shutdown — the classic pattern, in ~60 lines.

### IPC

Four mechanisms side by side: anonymous **pipes**, named **FIFOs**, **System V message queues**, **shared memory** (both `shmget/shmat` and POSIX `shm_open/mmap`), each with a producer/consumer pair where applicable.

### And more

- **Runnable per file** — no target wiring, just `g++ file.cpp`
- **Commented where it matters** — the "why" sits next to the line it explains
- **Standard C++17 + POSIX** — no third-party dependencies at all

---

## Quick Start

### Prerequisites

- Linux (or WSL/macOS for most examples)
- `g++` with C++17
- `cmake` 4.x (optional — only if you want the project file)

### Run it

```bash
git clone https://github.com/uxlabspk/OS-Fall-26.git
cd OS-Fall-26
```

Compile any single example:

```bash
g++ -std=c++17 Threads/race_condition.cpp -o race_condition -pthread
./race_condition
```

The IPC examples that come in pairs must be started in order:

```bash
g++ -std=c++17 IPC/shared_producer.cpp -o shared_producer -lrt
g++ -std=c++17 IPC/shared_consumer.cpp -o shared_consumer -lrt
./shared_producer & ./shared_consumer
```

> **Tip:** run the zombie example in one terminal and `ps -ef | grep defunct` in another while it sleeps — you'll catch the zombie in the wild.

---

## How it works

```
Concept from class
    ↓
One .cpp file, one main()
    ↓
g++ -std=c++17 → runnable binary
    ↓
stdout shows the kernel's behavior directly
```

**Race condition demo:** 4 threads × 100,000 increments. Unlocked, the counter comes out low and non-deterministic. Add a mutex (or `lock_guard`) and it lands exactly on 400,000.

**Zombie demo:** child `exit(0)`s immediately, parent `sleep(3)`s without `wait()` — the dead child stays in the process table until the parent reaps it.

---

## Tech Stack

| Layer | Tech |
|-------|------|
| Language | **C++17** — `std::thread`, `std::mutex`, `std::condition_variable` |
| System API | **POSIX** — `fork`, `exec`, `pipe`, `shm_open`, `pthreads` |
| IPC | **System V** (`shmget`, `msgget`) + **POSIX** (`shm_open`, `mmap`, FIFO) |
| Build | **g++** directly, or **CMake** for the project skeleton |

---

## Project Structure

```
OS-Fall-26/
├── CMakeLists.txt         Project skeleton (C++17)
├── Process_Operations/
│   ├── fork_example.cpp   fork() + parent/child PIDs
│   ├── exec_example.cpp   execl / execlp / execv / execvp
│   ├── zombies_example.cpp  Unreaped child → zombie
│   ├── orphan_example.cpp   Parent exits → orphan reparented to init
│   └── process_tree.cpp   Nested forks build a 3-level tree
├── Threads/
│   ├── pthread.cpp              Raw pthread_create/pthread_join
│   ├── std_thread.cpp           std::thread basics
│   ├── race_condition.cpp       Unsynchronized counter (wrong answer)
│   ├── race_condition_mutex.cpp Same race, fixed with std::mutex
│   ├── lock_guard.cpp           RAII locking with std::lock_guard
│   ├── thread_local_storage.cpp thread_local, one copy per thread
│   ├── producer_consumer.cpp    Bounded buffer + condition_variable
│   └── thread_pool.cpp          Worker pool with task queue
├── IPC/
│   ├── anon_pipes.cpp       Anonymous pipe across fork()
│   ├── named_pipe.cpp       FIFO writer  (/tmp/FIFO)
│   ├── named_pipe_reader.cpp FIFO reader
│   ├── message_queue.cpp    System V message queue
│   ├── shared_data.cpp      shmget/shmat producer-consumer
│   ├── shared_producer.cpp  POSIX shm_open/mmap writer
│   └── shared_consumer.cpp  POSIX shm_open/mmap reader
└── Compiler_Working/
    └── hello.cpp            Sanity-check build
```

---

## Contributing

Course notes grow over the semester. Contributions welcome.

1. Fork it
2. Create a branch (`git checkout -b feat/my-example`)
3. Commit (`git commit -m 'Add semaphore example'`)
4. Push (`git push origin feat/my-example`)
5. Open a PR