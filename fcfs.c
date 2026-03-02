#include <stdio.h>
#include <string.h>

struct Process {
    char pid[10];  // Store PID as string (e.g., "P1", "P2")
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    scanf("%d", &n);
    
    struct Process p[n];
    
    // Read process details - PID is a string like "P1", "P2"
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }
    
    // Sort by Arrival Time (FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
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
        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        
        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;
        
        current_time += p[i].burst;
        
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }
    
    // Output in the exact format expected by the tests
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].waiting);
    }
    
    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].turnaround);
    }
    
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f", total_tat / n);
    
    return 0;
}
