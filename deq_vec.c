#include <stdio.h>
#include <stdlib.h>
#include "deq_vec.h"

Deq* createDeq(int capacity) {
    Deq *deq = (Deq*) calloc(1, sizeof(Deq));
    if (deq == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    deq->capacity = capacity;
    deq->size = deq->head = deq->tail = 0;
    deq->patients = (Patient*) calloc(capacity, sizeof(Patient));

    if (deq->patients == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    return deq;
}

void freeDeq(Deq* deq) {
    free(deq->patients);
    free(deq);
}

int insertTail(Deq *deq, Patient *newPatient) {
    if (deq->size == deq->capacity)
        return 1;

    deq->patients[deq->tail] = *newPatient;
    deq->tail = (deq->tail + 1) % deq->capacity;

    ++deq->size;

    return 0;
}

int insertHead(Deq *deq, Patient *newPatient) {
    if (deq->size == deq->capacity) {
        return 1;
    }

    deq->head = (deq->head - 1 + deq->capacity) % deq->capacity;
    deq->patients[deq->head] = *newPatient;
    ++deq->size;

    return 0;
}

int remove_from_head(Deq *deq, Patient **removedPatient) {
    if (deq->size == 0) {
        return 1;
    }

    *removedPatient = &(deq->patients[deq->head]);

    if (deq->head != deq->tail) {
        if (deq->head == deq->capacity - 1) {
            deq->head = 0;
        }
        else {
            ++deq->head;
        }  
    }

    --deq->size;

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
    if (deq->size == 0) {
        return;
    }

    for (int i = deq->head, j = 0; j < deq->size; i = (i + 1) % deq->capacity, ++j) {
        printf("%s ", deq->patients[i].id);
    }

    printf("\n");
}

int DeqIsEmpty(Deq *deq) {
    return (deq->size == 0);
}
