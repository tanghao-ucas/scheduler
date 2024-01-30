#include "scheduler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

struct task task_init(int id, int wcet, int deadline)
{
    struct task task;
    task.id = id;
    task.wcet = wcet;
    task.execution = rand()%wcet + 1;
    task.deadline = deadline;
    task.next = NULL;
    return task;
}

struct taskset taskset_create()
{
    struct taskset ts;
    ts.tasks = (struct task*)malloc(sizeof(struct task));
    ts.taskSize = 0;
    return ts;
}

void taskset_init(struct taskset *ts, struct task tasks[], int n, void *func())
{
    for(int i = 0; i < n; i++){
        taskset_insert(ts, tasks[i], func);
    }
}

void taskset_insert(struct taskset *ts, struct task task, void *func())
{
    struct task *p = (struct task*)malloc(sizeof(struct task));
    *p = task;
    struct task *s = ts->tasks;

    while(s->next != NULL && func(*p, *(s->next))){
        s = s->next;
    }
    if(s->next != NULL)
        p->next = s->next; 
    s->next = p;
    ts->taskSize++;
}

void taskset_remove(struct taskset *ts)
{
    struct task *p = ts->tasks->next;
    ts->tasks->next = p->next;
    printf("------------Task %d is removed!\n", p->id);
    free(p);
    ts->taskSize--;
}

void run(struct taskset *ts)
{
    struct task *p = ts->tasks->next;
    p->execution--;
    int id = p->id;
    printf("Task %d is running... \n", id);
    if(!(p->execution > 0)){
        taskset_remove(ts);
    }
}

int edf(struct task a, struct task b)
{
    if(a.deadline > b.deadline)
        return 1;
    return 0;
}