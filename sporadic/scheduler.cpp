#include "scheduler.hpp"
#include <algorithm>

task::task(int id, int enter, int exit, int need, int period_max, int period_min, int wcet, int deadline){
    this->id = id;

    this->enter = enter;
    this->exit = exit;
    this->need = need;
    this->period_max = period_max;
    this->period_min = period_min;

    this->wcet = wcet;
    this->period = period_min;
    this->deadline = deadline;

    this->complete = 0;
    this->next = enter;
}

bool task::operator == (const int id)
{
    return (this->id == id);
}

job::job(int time, struct task tsk){
    task_id = tsk.id;
    job_id = tsk.complete + 1;
    execution = tsk.wcet;
    deadline = tsk.deadline == 0 ? time + tsk.period : time + tsk.deadline;
}

void task::nextjob(int time)
{
    if(time < this->exit)
        next = time + period;
}

void task::modify(int period)
{
    this->period = period;
}

void schedule(std::vector<struct job>& job_queue)
{
    sort(job_queue.begin(), job_queue.end(), edf);
}

int edf(struct job a, struct job b)
{
    return a.deadline < b.deadline;
}
