#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fcfs(int process[], int bursttime[], int arrivaltime[], int n);
void sjf(int process[], int bursttime[], int arrivaltime[], int n);
void srtf(int process[], int bursttime[], int arrivaltime[], int n);
void round_robin(int process[], int bursttime[], int arrivaltime[], int n, int quantum);
void priority_np(int process[], int bursttime[], int arrivaltime[], int priority[], int n, int order);
void priority_p(int process[], int bursttime[], int arrivaltime[], int priority[], int n, int order);
