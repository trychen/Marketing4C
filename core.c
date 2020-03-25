#include "core.h"

void fixReturnNewline(char c[], int len) {
    if (len == 0) return;
    len--;
    while (c[len] == '\r' || c[len] == '\n') {
        c[--len] = '\0';
    }
}

Linker * linkedlist_endpoint(Linker *head) {
    while(head != NULL) {
        if (head->next == NULL)
            return head;
        head = head->next;
    }
    return head;
}

void linkedlist_add(Linker *head, void* add) {
    if (head->entry == NULL) {
        head->entry = add;
    } else {
        Linker *end;

        while (head != NULL) {
            end = head;
            head = head->next;
        }

        Linker *next = malloc(sizeof(Linker));
        next->entry = add;
        next->next = NULL;

        end->next = next;
    }
}

void linkedlist_foreach(Linker *head, void (*func_each)(void *entry)) {
    while(head != NULL) {
        func_each(head->entry);
        head = head->next;
    }
}

void * linkedlist_search(Linker *head, bool (*func_filter)(void *entry)) {
    while(head != NULL) {
        if (func_filter(head->entry)) return head->entry;
        head = head->next;
    }
    return NULL;
}

bool linkedlist_delete(Linker *head, void *entry) {
    Linker* previous = head;
    while(head != NULL) {
        if (head->entry == entry) {
            previous->next = head->next;
            free(head);
            return true;
        }
        previous = head;
        head = head->next;
    }
    return false;
}

int linkedlist_size(Linker *head) {
    if (head == NULL) return 0;
    int size = 0;
    while(head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

void * linkedlist_get(Linker *head, int index) {
    int current = 0;
    while(head != NULL) {
        if (index == current) {
            return head->entry;
        }
        current++;
        head = head->next;
    }
    return NULL;
}

Linker * linkedlist_folkInOrder(Linker *head, bool (*order)(void*, void*)) {
    Linker *sorted = malloc(sizeof(Linker));
    memset(sorted, 0, sizeof(Linker));

    Linker *current = head;

    while (current != NULL) {
        if (sorted->entry == NULL) {
            sorted->entry = current->entry;
            current = current->next;
            continue;
        }

        Linker *add = malloc(sizeof(Linker));
        add->entry = current->entry;
        add->next = NULL;

        Linker *aim = sorted;

        if (order(aim->entry, add->entry)) {
            add->next = aim;
            sorted = add;
        } else {
            while (aim->next != NULL && !order(aim->next->entry, add->entry)) {
                aim = aim->next;
            }

            if (aim->next == NULL)
                aim->next = add;
            else {
                Linker *next = aim->next;
                aim->next = add;
                add->next = next;
            }
        }

        current = current->next;
    }
    return sorted;
}