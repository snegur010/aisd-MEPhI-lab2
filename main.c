#include <stdio.h>
#include <stdlib.h>
// #include "deq_vec.h"
// #include "patient_vec.h"
#include "deq_list.h"
#include "patient_list.h"
#include "queue_status.h"

#define DEQ_CAPACITY 5
#define PROMT "Запишись к врачу>>>  "

int main() {
    Deq *deq = createDeq(DEQ_CAPACITY);
    if (deq == NULL) {
        printf("Failed to create deque.\n");
        return 1;
    }                                                    

    int parametr, count;
    printf("Enter patients in the format: id/ta/ts ('*' indicates 'only ask'):\n");
    char *input = my_readline(PROMT);
    if (input == NULL) {
        free(deq);
        printf("Failed to read input.\n");
        return 1;
    }

    Patient *patients = addPatientsToArray(input, &parametr, &count, DEQ_CAPACITY);
    if (patients == NULL) {
        printf("Failed to add patients to array.\n");
        for (int i = 0; i < count; i++) {
            free(patients[i].id);
        }
        free(patients);
        free(deq);
        free(input);
        return 1;
    }
    sortPatientsByTA(patients, count);
    int res = individual(deq, patients, count);
    if (res == 1) {
        printf("Память не была выделена\n");
    }

    for (int i = 0; i < count; i++) {
        free(patients[i].id);
    }

    free(patients);
    // free(deq->patients); //only for vector
    free(deq);
    free(input);
    return 0;
}