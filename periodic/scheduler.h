#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX 100

struct task
{
    int id;
    int period;
    int wcet;
    int deadline;
};

struct taskset
{
    struct task tasks[MAX];
    int taskSize;
};

struct job
{
    int taskid;
    int jobid;

    int wcet;
    int execution;
    
    int period;
    int deadline;
    struct job *next;
};

struct jobset
{
    struct job *jobs;
    int jobSize;
};

/*
 * Task Operation
*/

struct task task_init(int id, int wcet, int deadline);

struct taskset taskset_create();

void taskset_init(struct taskset *ts, struct task tasks[], int n, void *cmp());

void taskset_insert(struct taskset *ts, struct task task, void *cmp());

void taskset_remove(struct taskset *ts, int id);


/*
 * Job Operation
*/

void job_init_by_task(struct job *new, struct task *task);

void job_init(struct job *new, struct job *last);

struct jobset jobset_init(struct taskset *ts);

void jobset_fresh(struct jobset *js, void *cmp());


/*
 * System 
*/

void run(struct jobset *js, void *cmp());

void run_time(struct jobset *js, int timezone, void *cmp());

int edf(struct job *a, struct job *b);

#endif