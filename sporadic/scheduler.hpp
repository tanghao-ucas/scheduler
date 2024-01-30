#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>

struct task{
    int id;

    int enter;
    int exit;
    int need;
    int period_max;
    int period_min;

    int wcet;
    int period;
    int deadline;

    int complete;
    int next;

    task(int id, int enter, int exit, int need, int period_max, int period_min, int wcet, int deadline);

    bool operator == (const int id);

    void modify(int period);
    void nextjob(int time);
};

struct job{
    int job_id;
    int task_id;
    int execution;
    int deadline;

    job(int time, struct task tsk);
};

void schedule(std::vector<struct job>& job_queue);

int edf(struct job a, struct job b);

#endif