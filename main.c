#include <stdio.h>
#include <memory.h>
#include <time.h>

#include "linked-list.h"

#define ARRLEN 10

typedef struct list *List;

void print_and_free(void *data) {
    printf("%d\n", *(int *)data);
    free(data);
}

int main(void) {
    List list = list_new();
    int arr[ARRLEN];
    int arrcpy[ARRLEN];
    srand(time(NULL));
    rand();
    for (size_t i = 0; i < ARRLEN; i++) {
        int *tmp = malloc(sizeof(int));
        *tmp = rand();
        arr[i] = *tmp;
        list_append(list, tmp);
    }

    for (size_t i = 0; i < ARRLEN; i++) {
        arrcpy[i] = *(int *) list_get(list, i);
    }

    printf("Mem diff: %d\n", memcmp(arr, arrcpy, ARRLEN * sizeof(int)));
    list_destroy(list, print_and_free);
}
