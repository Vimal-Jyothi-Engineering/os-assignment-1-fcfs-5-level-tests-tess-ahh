#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Process {
    char pid_str[10];
    int pid_num;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    scanf("%d", &n);
    
    struct Process p[n];
    char pname[20];
    
    // Read process details
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", pname, &p[i].arrival, &p[i].burst);
        strcpy(p[i].pid_str, pname);
        p[i].pid_num = atoi(pname + 1);
    }
    
    // Sort by Arrival Time (FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            // If arrival times are equal, maintain original order (stable sort)
            else if (p[i].arrival == p[j].arrival && p[i].pid_num > p[j].pid_num) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    
    // Calculate waiting and turnaround times
    for (int i = 0; i < n; i++) {
        // If current time is less than arrival time, CPU was idle
        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        
        // Waiting time = current time - arrival time
        p[i].waiting = current_time - p[i].arrival;
        
        // Turnaround time = waiting time + burst time
        p[i].turnaround = p[i].waiting + p[i].burst;
        
        // Update current time
        current_time += p[i].burst;
        
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }
    
    // Output in the exact format
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d %d\n", p[i].pid_num, p[i].waiting);
    }
    
    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d %d\n", p[i].pid_num, p[i].turnaround);
    }
    
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    
    return 0;
}
