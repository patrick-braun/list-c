#include <stdlib.h>

struct element
{
    void *data;
    struct element *next;
};

struct list
{
    struct element *head;
    struct element *tail;
    size_t len;
};

struct list *list_new();
void list_destroy(struct list *, void (*)(void *));
int list_append(struct list *, void *);
int list_insert(struct list *, void *, size_t);
void *list_get(struct list *, size_t);
void *list_take(struct list*, size_t);
void list_remove(struct list*, size_t);
