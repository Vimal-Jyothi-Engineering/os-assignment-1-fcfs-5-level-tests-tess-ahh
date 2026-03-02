#include <stdio.h>
#include <string.h>

struct Process {
    char pid[10];  // Changed to string to handle "P1", "P2", etc.
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }

    /* Sort by Arrival Time (FCFS) */
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

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival;

        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        current_time += p[i].burst;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    /* Output in EXACT required format */
    printf("Waiting Time: ");
    for (int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].waiting);
    }

    printf("Turnaround Time: ");  // Removed the \n here
    for (int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].turnaround);
    }

    printf("Average Waiting Time: %.2f ", total_wt / n);  // Added space at the end
    printf("Average Turnaround Time: %.2f", total_tat / n);

    return 0;
}
