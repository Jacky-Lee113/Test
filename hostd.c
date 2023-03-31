#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PROCESSES 100

struct Process {
    char name[256];
	int priority;
    int memory;
    int runtime;
};

// comparator function for the priority queue
int cmp(const void *a, const void *b) {
    const struct Process *p1 = *(const struct Process **) a;
    const struct Process *p2 = *(const struct Process **) b;
    return p1->priority - p2->priority;
}

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    FILE *fp;
    char line[256];
    struct Process *processes[MAX_PROCESSES]; // array of pointers to processes
    int num_processes = 0;
    int i;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: unable to open file '%s'\n", filename);
        return 1;
    }

    // read input file and add each process to the priority queue
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *name = strtok(line, ",");
        int priority = atoi(strtok(NULL, ","));
        int memory = atoi(strtok(NULL, ","));
        int runtime = atoi(strtok(NULL, ","));
        struct Process *p = malloc(sizeof(struct Process));
        strcpy(p->name, name);
		p->priority = priority;
        p->runtime = runtime;
        p->memory = memory;
        processes[num_processes] = p;
        num_processes++;
    }

    fclose(fp);

    // create a priority queue to hold the processes
    qsort(processes, num_processes, sizeof(struct Process *), cmp);

    // output processes
    printf("Name\tPriority\tMemory\tRuntime\n");
    for (i = 0; i < num_processes; i++) {
        printf("%s\t%d\t        %d\t%d\n", processes[i]->name, processes[i]->priority, processes[i]->memory, processes[i]->runtime);
    }

  // execute the processes and keep track of their total runtime
int total_runtime = 0;
for (i = 0; i < num_processes; i++) {
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        sleep(processes[i]->runtime);
        execl("./process", processes[i]->name, NULL);
        perror("exec failed");
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    // add runtime to total
    total_runtime += processes[i]->runtime;
}

// wait for total runtime before terminating the program
sleep(total_runtime);

// program has finished executing, terminate
kill(getpid(), SIGINT);
exit(0);
}