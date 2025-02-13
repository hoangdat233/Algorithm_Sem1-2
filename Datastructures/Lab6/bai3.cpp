#include <iostream>
#include <vector>

struct Worker {
    int salary;    
    int id;        
};

struct TaskedWorker {
    long long finishTime; 
    int salary;          
    int id;               
};

struct Job {
    long long startTime; 
    int duration;        
};

void heapifyUpFreeWorkers(std::vector<Worker>& heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].salary < heap[parent].salary) {
            std::swap(heap[i], heap[parent]);
            i = parent;
        } else break;
    }
}

void heapifyDownFreeWorkers(std::vector<Worker>& heap, int i) {
    int n = heap.size();
    while (true) {
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < n && heap[left].salary < heap[smallest].salary)
            smallest = left;
        if (right < n && heap[right].salary < heap[smallest].salary)
            smallest = right;

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            i = smallest;
        } else break;
    }
}

void pushFreeWorker(std::vector<Worker>& heap, const Worker& worker) {
    heap.push_back(worker);
    heapifyUpFreeWorkers(heap, heap.size() - 1);
}

Worker popFreeWorker(std::vector<Worker>& heap) {
    Worker topWorker = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDownFreeWorkers(heap, 0);
    return topWorker;
}

void heapifyUpBusyWorkers(std::vector<TaskedWorker>& heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].finishTime < heap[parent].finishTime) {
            std::swap(heap[i], heap[parent]);
            i = parent;
        } else break;
    }
}

void heapifyDownBusyWorkers(std::vector<TaskedWorker>& heap, int i) {
    int n = heap.size();
    while (true) {
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < n && heap[left].finishTime < heap[smallest].finishTime)
            smallest = left;
        if (right < n && heap[right].finishTime < heap[smallest].finishTime)
            smallest = right;

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            i = smallest;
        } else break;
    }
}

void pushBusyWorker(std::vector<TaskedWorker>& heap, const TaskedWorker& worker) {
    heap.push_back(worker);
    heapifyUpBusyWorkers(heap, heap.size() - 1);
}

TaskedWorker popBusyWorker(std::vector<TaskedWorker>& heap) {
    TaskedWorker topWorker = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDownBusyWorkers(heap, 0);
    return topWorker;
}

int main() {
    int numWorkers, numJobs;
    std::cin >> numWorkers >> numJobs;

    std::vector<Worker> workers(numWorkers);
    for (int i = 0; i < numWorkers; ++i) {
        std::cin >> workers[i].salary;
        workers[i].id = i;
    }

    std::vector<Worker> freeWorkers;
    for (const auto& worker : workers) {
        pushFreeWorker(freeWorkers, worker);
    }

    std::vector<TaskedWorker> busyWorkers;

    long long totalCost = 0;

    std::vector<Job> jobs(numJobs);
    for (int i = 0; i < numJobs; ++i) {
        std::cin >> jobs[i].startTime >> jobs[i].duration;
    }

    for (const auto& job : jobs) {
        long long currentTime = job.startTime;
        while (!busyWorkers.empty() && busyWorkers[0].finishTime <= currentTime) {
            TaskedWorker finishedWorker = popBusyWorker(busyWorkers);
            pushFreeWorker(freeWorkers, {finishedWorker.salary, finishedWorker.id});
        }
        if (!freeWorkers.empty()) {
            Worker assignedWorker = popFreeWorker(freeWorkers);
            long long finishTime = currentTime + job.duration;

            TaskedWorker taskedWorker = {finishTime, assignedWorker.salary, assignedWorker.id};
            pushBusyWorker(busyWorkers, taskedWorker);

            totalCost += (long long)assignedWorker.salary * job.duration;
        }
    }

    std::cout << totalCost << std::endl;
    return 0;
}
