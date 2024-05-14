#ifndef QUEUE_H
#define QUEUE_H

#include "patient_list.h"
#include "deq_list.h"

// #include "patient_vec.h"
// #include "deq_vec.h"

int individual(Deq *deq, Patient *patients, int count);

int isNumeric(const char *str);

char* my_readline(const char *str);

#endif 