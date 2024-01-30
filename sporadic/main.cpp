#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#include "scheduler.hpp"

using namespace std;

vector<struct task> task_all;
vector<struct task> task_queue;
vector<struct job> job_queue;

void run(vector<struct job>& job_queue)
{
    schedule(job_queue);
    job_queue[0].execution--;
    printf("Task %d Job %d is running...\n", job_queue[0].task_id, job_queue[0].job_id);

    if(!job_queue[0].execution){
        printf("(Finish) Task %d Job %d\n", job_queue[0].task_id, job_queue[0].job_id);
        vector<struct task>::iterator it;
        it = find(task_queue.begin(), task_queue.end(), job_queue[0].task_id);
        it->complete++;
        job_queue.erase(job_queue.begin());
    }
}

int main()
{
    // Task Configuration
    ifstream infile;
    infile.open("input.txt");

    int total = 0;
    infile >> total;
    int enter, exit, need, period_max, period_min, wcet, deadline;

    for(int i = 0; i < total; i++){
        infile >> enter;
        infile >> exit;
        infile >> need;
        infile >> period_max;
        infile >> period_min;
        infile >> wcet;
        infile >> deadline;
        struct task new_task(i + 1, enter, exit, need, period_max, period_min, wcet, deadline);
        task_all.push_back(new_task);
    }

    // System runtime
    int finish = 40;

    for(int time = 0; time <= finish; time++){
        // Task enter or leave
        for(vector<struct task>::iterator it = task_queue.begin(); it != task_queue.end(); it++){
            if(time == it->exit)
                task_queue.erase(it);
        }

        for(vector<struct task>::iterator it = task_all.begin(); it != task_all.end(); it++){
            if(time == it->enter){
                task_queue.push_back(*it);
            }
        }

        for(vector<struct task>::iterator it = task_queue.begin(); it != task_queue.end(); it++){
            if(time == it->next){
                struct job new_job(time, *it);
                job_queue.push_back(new_job);
                printf("(New) Task %d instance %d\n", it->id, new_job.job_id);
                it->nextjob(time);
            }
        }
        run(job_queue);
    }

    return 0;
}