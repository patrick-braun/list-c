#include "linked-list.h"

struct list *list_new() {
    struct list *list = malloc(sizeof(struct list));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

void list_destroy(struct list *list, void (*cleanup)(void *)) {
    struct element *cur = list->head;
    struct element *next = NULL;
    for (size_t i = 0; i < list->len; i++) {
        next = cur->next;
        if (cleanup != NULL) {
            (*cleanup)(cur->data);
        }
        free(cur);
        cur = next;
    }
    free(list);
}

int list_append(struct list *list, void *value) {
    struct element *el = malloc(sizeof(struct element));
    if (el == NULL) {
        return 1;
    }

    el->next = NULL;
    el->data = value;
    if (list->len == 0) {
        list->head = el;
        list->tail = el;
        list->len = 1;
        return 0;
    }
    list->tail->next = el;
    list->tail = el;
    list->len++;
    return 0;
}

int list_insert(struct list *list, void *value, size_t index) {
    if (list->len < index) {
        return 1;
    }

    struct element *new = malloc(sizeof(struct element));
    if (new == NULL) {
        return 1;
    }

    new->next = NULL;
    new->data = value;

    if (list->len == 0) {
        list->head = new;
        list->tail = new;
        list->len = 1;
        return 0;
    }


    struct element *el = list->head;

    for (size_t cur = 0; cur < index - 1; cur++) {
        el = el->next;
    }
    new->next = el->next;
    el->next = new;

    if (index == 0) {
        list->head = new;
    }
    if (index == list->len) {
        list->tail = new;
    }
    list->len++;
    return 0;
}

void *list_get(struct list *list, size_t index) {
    if (list->len <= index) {
        return NULL;
    }

    if (index == list->len - 1) {
        return list->tail->data;
    }


    struct element *el = list->head;

    for (size_t cur = 0; cur < index; cur++) {
        el = el->next;
    }
    return el->data;
}

void *list_take(struct list *list, size_t index) {
    if (list->len <= index) {
        return NULL;
    }

    struct element *el = list->head;
    struct element *prev = list->head;

    for (size_t cur = 0; cur < index; cur++) {
        prev = el;
        el = el->next;
    }

    prev->next = el->next;
    if (index == 0) {
        list->head = el->next;
    }
    if (index == list->len - 1) {
        list->tail = prev;
    }
    list->len--;

    void *tmp = el->data;
    free(el);
    return tmp;
}

void list_remove(struct list *list, size_t index) {
    list_take(list, index);
}

