#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX 100

struct task{
    int id;
    int wcet;
    int execution;
    int deadline;
    struct task *next;
};

struct taskset{
    struct task *tasks;
    int taskSize;
};

struct task task_init(int id, int wcet, int deadline);

struct taskset taskset_create();

void taskset_init(struct taskset *ts, struct task tasks[], int n, void *func());

void taskset_insert(struct taskset *ts, struct task task, void *func());

void taskset_remove(struct taskset *ts);

void run(struct taskset *ts);

int edf(struct task a, struct task b);

#endif