#ifndef DEQ_VEC_H
#define DEQ_VEC_H

#include "patient_vec.h"

typedef struct Deq {
    Patient *patients;
    int capacity, size;
    int head;
    int tail;
} Deq;

Deq* createDeq(int capacity);

void freeDeq(Deq* deq);

int insertTail(Deq *deq, Patient *newPatient);

int insertHead(Deq *deq, Patient *newPatient);

int remove_from_head(Deq *deq, Patient **removedPatient);

int insertByIndex(Deq *deq, Patient *patients, int i);

void deq_print(const Deq *deque);

int DeqIsEmpty(Deq *deq);

#endif /* DEQ_VEC_H */
