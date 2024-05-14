#include <stdio.h>
#include <stdlib.h>
#include "deq_vec.h"
#include "patient_vec.h"
#include "queue_status_vec.h"

#define DEQ_CAPACITY 5
#define PROMT "Запишись к врачу>>>  "

int main() {
    Deq *deq = createDeq(DEQ_CAPACITY);

    if (deq == NULL) {
        printf("Failed to create deque.\n");
        return 1;
    }                                                    

    int parametr;
    printf("Enter patients in the format: id/ta/ts ('*' indicates 'only ask'):\n");
    char *input = my_readline(PROMT);

    if (input == NULL) {
        freeDeq(deq);
        printf("Failed to read input.\n");
        return 1;
    }

    Patient *patients = addPatientsToArray(input, &parametr, DEQ_CAPACITY);
    if (patients == NULL) {
        printf("Вводите пациентов корректно!\n");
        freeDeq(deq);
        free(input);
        return 1;
    }

    sortPatientsByTA(patients, parametr);

    int res = individual(deq, patients, parametr);

    if (res == 1) {
        printf("Память не была выделена\n");
        free_pat_auxiliary(patients, parametr);
        freeDeq(deq);
        free(input);
        return 1;
    }

    free_pat_auxiliary(patients, parametr);
    freeDeq(deq);
    free(input);
    return 0;
}