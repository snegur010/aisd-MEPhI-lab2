#include <stdio.h>
#include <stdlib.h>
#include "deq_list.h"


void freeDeq(Deq *deq) {
    if (deq == NULL) {
        return;
    }

    Item *current = deq->head;
    while (current != NULL) {
        Item *next = current->next;
        freeItem(current);
        current = next;
    }
    free(deq);
}


Deq *createDeq(int capacity) {
    capacity = capacity + 1 - 1;
    Deq *deq = (Deq*) calloc(1, sizeof(Deq));
    if (deq == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    deq->head = NULL;
    deq->tail = NULL;
    return deq;
}

int insertTail(Deq *deq, Patient *newPatient) {
    Item *new = createItem(newPatient);
    if (new == NULL) {
        return 1;
    }

    if (deq->head == NULL) {
        deq->head = deq->tail = new;
    } else {
        new->prev = deq->tail;
        deq->tail->next = new;
        deq->tail = new;
    }

    return 0;
}

int insertHead(Deq *deq, Patient *newPatient) {
    Item *new = createItem(newPatient);
    if (new == NULL) {
        return 1;
    }

    if (deq->head == NULL) {
        deq->head = deq->tail = new;
    } else {
        new->next = deq->head;
        deq->head->prev = new;
        deq->head = new;
    }
    return 0;
}

int remove_from_head(Deq *deq, Patient **removed_patient) {
    if (deq->head == NULL) {
        return 1;
    }

    *removed_patient = deq->head->patient;

    Item *head = deq->head;
    deq->head = head->next;
    free(head);

    if (deq->head == NULL) {
        deq->tail = NULL;
    } else {
        deq->head->prev = NULL;
    }
    return 0;
}


int insertByIndex(Deq *deq, Patient *patients, int i) {
    int res = 0;
    if (patients[i].id[0] == '*') {
        res = insertHead(deq, patients + i);
        if (res == 1) {
           printf("Deq is full. Cannot insert from front.\n\n");
           return 1; 
        }
    } else {
        res = insertTail(deq, patients + i);
        if (res == 1) {
            printf("Deq is full. Cannot insert from tail.\n\n");
            return 1;
        }
    }
    return 0;
}

void deq_print(const Deq *deq) {
    if (deq->head == NULL) {
        return;
    }

    Item *curr = deq->head;
    while (curr != NULL) {
        printf("%s ", curr->patient->id);
        curr = curr->next;
    }

    printf("\n");
}

int DeqIsEmpty(Deq *deq) {
    return (deq->head == NULL);
}

