#include <stdio.h>
#include <stdlib.h>

void range(int M, int N, int S) {
    for (int i = M; i < N; i += S) {
        printf("%d\n", i);
    }
}

int main(int argc, char *argv[]) {
    char *help = "Program printing sequence of numbers like range(M, N, S)\n"
                 "Use arguments M, N, S\n";
    switch (argc) {
        case 1: {
            printf("%s", help);
            break;
        }
        case 2: {
            range(0, atoi(argv[1]), 1);
            break;
        }
        case 3: {
            range(atoi(argv[1]), atoi(argv[2]), 1);
            break;
        }
        case 4: {
            range(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
            break;
        }
        default: printf("%s", help);
    }
}
