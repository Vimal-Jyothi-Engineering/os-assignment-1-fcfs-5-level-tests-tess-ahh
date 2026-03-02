#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
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
        char pname[10];
        scanf("%s %d %d", pname, &p[i].arrival, &p[i].burst);
        p[i].pid = atoi(pname + 1);   // Convert P1 → 1
    }

    // Sort by arrival time
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
    double total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival;

        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        current_time += p[i].burst;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    // EXACT output format (single line)
    printf("Waiting Time: ");
    for (int i = 0; i < n; i++)
        printf("P%d %d ", p[i].pid, p[i].waiting);

    printf("Turnaround Time: ");
    for (int i = 0; i < n; i++)
        printf("P%d %d ", p[i].pid, p[i].turnaround);

    printf("Average Waiting Time: %.2f ", total_wt / n);
    printf("Average Turnaround Time: %.2f", total_tat / n);

    return 0;
}
