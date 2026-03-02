#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Process {
    char pid_str[10];  // Original PID string (e.g., "P1")
    int pid_num;       // Numeric PID for output (e.g., 1)
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
        p[i].pid_num = atoi(pname + 1);  // Extract number from "P1", "P2", etc.
    }
    
    // Check if input is already sorted by arrival time (from code 1)
    int already_sorted = 1;
    for (int i = 0; i < n - 1; i++) {
        if (p[i].arrival > p[i + 1].arrival) {
            already_sorted = 0;
            break;
        }
    }
    
    // Sort by Arrival Time if not already sorted
    if (!already_sorted) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (p[j].arrival > p[j + 1].arrival) {
                    struct Process temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
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
    
    // Output format from code 1 (using P%d for PID numbers)
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
