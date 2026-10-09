#include <stdio.h>
#include <stdlib.h>

int n, fn, pos, pg[50], fr[10], t[10];

int ispresent(int p) {
    int i;
    for (i = 0; i < fn; i++) {
        if (fr[i] == p) {
            pos = i;
            return 1;
        }
    }
    return 0;
}

void show() {
    int i;
    printf("[ ");
    for (i = 0; i < fn; i++) {
        if (fr[i] == -1) printf("- ");
        else printf("%d ", fr[i]);
    }
    printf("]");
}

int findlru() {
    int j, k = 0;
    for (j = 0; j < fn; j++) {
        if (fr[j] == -1) return j;
    }
    for (j = 1; j < fn; j++) {
        if (t[j] < t[k]) k = j;
    }
    return k;
}

int findoptimalpage(int i) {
    int j, l, f, far = -1, k = 0;
    for (j = 0; j < fn; j++) {
        if (fr[j] == -1) return j;
    }
    for (j = 0; j < fn; j++) {
        f = 0;
        for (l = i + 1; l < n; l++) {
            if (pg[l] == fr[j]) {
                f = 1;
                break;
            }
        }
        if (!f) return j;
        if (l > far) {
            far = l;
            k = j;
        }
    }
    return k;
}

void fifo() {
    int i, nx = 0, pf = 0;
    for (i = 0; i < fn; i++) fr[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");
    printf("%-6s %-20s %-5s\n", "Page", "Frames", "Fault");
    for (i = 0; i < n; i++) {
        printf("%-6d ", pg[i]);
        if (!ispresent(pg[i])) {
            fr[nx] = pg[i];
            nx = (nx + 1) % fn;
            pf++;
            show();
            printf("        %-5s\n", "Yes");
        } else {
            show();
            printf("        %-5s\n", "No");
        }
    }
    printf("Total page faults = %d\n", pf);
    printf("Hits = %d, Hit ratio = %.2f\n", n - pf, (float)(n - pf) / n);
}

void lru() {
    int i, k, pf = 0;
    for (i = 0; i < fn; i++) { fr[i] = -1; t[i] = -1; }

    printf("\n--- LRU Page Replacement ---\n");
    printf("%-6s %-20s %-5s\n", "Page", "Frames", "Fault");
    for (i = 0; i < n; i++) {
        printf("%-6d ", pg[i]);
        if (ispresent(pg[i])) {
            t[pos] = i;
            show();
            printf("        %-5s\n", "No");
        } else {
            k = findlru();
            fr[k] = pg[i];
            t[k] = i;
            pf++;
            show();
            printf("        %-5s\n", "Yes");
        }
    }
    printf("Total page faults = %d\n", pf);
    printf("Hits = %d, Hit ratio = %.2f\n", n - pf, (float)(n - pf) / n);
}

void optimal() {
    int i, k, pf = 0;
    for (i = 0; i < fn; i++) fr[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");
    printf("%-6s %-20s %-5s\n", "Page", "Frames", "Fault");
    for (i = 0; i < n; i++) {
        printf("%-6d ", pg[i]);
        if (ispresent(pg[i])) {
            show();
            printf("        %-5s\n", "No");
        } else {
            k = findoptimalpage(i);
            fr[k] = pg[i];
            pf++;
            show();
            printf("        %-5s\n", "Yes");
        }
    }
    printf("Total page faults = %d\n", pf);
    printf("Hits = %d, Hit ratio = %.2f\n", n - pf, (float)(n - pf) / n);
}

int main() {
    int i, choice;

    printf("Enter number of pages in reference string: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter reference string: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &pg[i]) != 1) return 1;
    }

    printf("Enter number of frames: ");
    if (scanf("%d", &fn) != 1) return 1;

    while(1) {
        printf("\nSelect Page Replacement Algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. OPTIMAL\n");
        printf("4. Exit\n");
        printf("Enter choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;

        switch(choice) {
            case 1: fifo(); break;
            case 2: lru(); break;
            case 3: optimal(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
