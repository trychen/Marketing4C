#include "core.h"

void fixReturnNewline(char c[], int len) {
    if (len == 0) return;
    len--;
    while (c[len] == '\r' || c[len] == '\n') {
        c[--len] = '\0';
    }
}

void list_add(LIST head, void* entry) {
    if (head->entry == NULL) {
        head->entry = entry;
    } else {
        LIST end;

        while (head != NULL) {
            end = head;
            head = head->next;
        }

        LIST next = malloc(sizeof(Linker));
        next->entry = entry;
        next->next = NULL;

        end->next = next;
    }
}

bool list_delete(LIST head, void *entry) {
    LIST previous = head;
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

int list_size(LIST head) {
    if (head == NULL) return 0;
    int size = 0;
    FOREACH(head, Linker*, h, size++)
    return size;
}

void list_free(LIST head) {
    while(head != NULL) {
        free(head);
        head = head->next;
    }
}

LIST list_create() {
    LIST list = malloc(sizeof(Linker));
    list->next = list->entry = NULL;
    return list;
}

LIST list_folkInOrder(LIST head, bool (*order)(void*, void*)) {
    LIST sorted = list_create();

    FOREACH(head, void*, current, {
        Linker* add = list_create();
        add->entry = current;

        if (sorted->next == NULL) {
            sorted->next = add;
            continue;
        }

        Linker *aim = sorted->next;
        if (order(aim->entry, add->entry)) {
            add->next = aim;
            sorted->next = add;
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
    })

    return sorted;
}