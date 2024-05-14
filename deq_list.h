#ifndef DEQ_LIST_H
#define DEQ_LIST_H

#include "patient_list.h"

typedef struct Deq {
    Item *head;
    Item *tail;
} Deq;

Deq *createDeq(int capacity);

int insertTail(Deq *deq, Patient *newPatient);

int insertHead(Deq *deq, Patient *newPatient);

int remove_from_head(Deq *deq, Patient **removed_patient);

int insertByIndex(Deq *deq, Patient *patients, int i);

void deq_print(const Deq *deq);

int DeqIsEmpty(Deq *deq);

void freeDeq(Deq *deq);

#endif /* DEQ_LIST_H */