#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct taskset taskset_create()
{
    struct taskset ts;
    ts.taskSize = 0;
    return ts;
}

void taskset_init(struct taskset *ts, struct task tasks[], int n, void *cmp())
{
    for(int i = 0; i < n; i++){
        taskset_insert(ts, tasks[i], cmp);
    }
}

void taskset_insert(struct taskset *ts, struct task task, void *cmp())
{
    if(ts->taskSize == 0){
        ts->tasks[0] = task;
        return;
    }
    for(int i = 0; i < ts->taskSize; i++){
        if(func(ts->tasks[i], task)){
            for(int j = ts->taskSize; j > i; j--){
                ts->tasks[j] = ts->tasks[j-1];
            }
            ts->tasks[i] = task;
            ts->taskSize++;
        }
    }
}

void taskset_remove(struct taskset *ts, int id)
{
    for(int i = 0; i < ts->taskSize; i++){
        if(ts->tasks[i].id == id){
            for(int j = i; j < ts->taskSize - 1; j++){
                ts->tasks[j] = ts->tasks[j+1];
            }
            ts->taskSize--;
        }
    }
}


void job_init_by_task(struct job *new, struct task *task)
{
    new->taskid = task->id;
    new->jobid = 0;
    new->period = task->period;
    new->wcet = task->wcet;
    new->execution = rand()%(task->wcet) + 1;
    new->deadline = task->deadline;
    new->next = NULL;
}

void job_init(struct job *new, struct job *last)
{
    new->taskid = last->taskid;
    new->jobid = last->jobid + 1;
    new->period = last->period;
    new->wcet = last->wcet;
    new->execution = rand()%(last->wcet) + 1;
    new->deadline = last->deadline + last->period;
    new->next = NULL;
}

struct jobset jobset_init(struct taskset *ts)
{
    struct jobset js;
    js.jobs = (struct job*)malloc(sizeof(struct job));
    struct job *job;
    for(int i = ts->taskSize - 1; i >= 0; i--){
        job = (struct job*)malloc(sizeof(struct job));
        job_init_by_task(job, &(ts->tasks[i]));
        job->next = js.jobs->next;
        js.jobs->next = job;
    }
    return js;
}

void jobset_fresh(struct jobset *js, void *cmp())
{
    if(js->jobs->next->execution == 0){
        struct job *new = (struct job*)malloc(sizeof(struct job));
        job_init(new, js->jobs->next);

        struct job *p = js->jobs;
        while(cmp(p->next, new)) p = p->next;
        new->next = p->next;
        p->next = new;
        printf("---------New--------Task(%d)Job(%d)\n", new->taskid, new->jobid);
    }
}

void run(struct jobset *js, void *cmp())
{
    printf("Task %d : Job %d is running...\n", js->jobs->next->taskid, js->jobs->next->jobid);
    js->jobs->next->execution--;
    jobset_fresh(js, cmp);
}

void run_time(struct jobset *js, int timezone, void *cmp())
{
    for(int i = 0; i < timezone; i++){
        printf("Time(%d):  ", i);
        run(js, cmp);
    }
}

int edf(struct job *a, struct job *b)
{
    if(a->deadline < b->deadline)
        return 0;
    return 1;
}