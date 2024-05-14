#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq_vec.h"
#include "patient_vec.h"
#include "queue_status_vec.h"

void freePatient(Patient *patient) {
    free(patient->id);
}

void free_pat_auxiliary(Patient *patients, int count) {
    for (int i = 0; i < count; i++) {
        free(patients[i].id);
    }
    free(patients);
}

Patient* createPatient(char *id, int ta, int ts) {
    Patient *newPatient = (Patient *) calloc(1, sizeof(Patient));
    if (newPatient == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newPatient->id = strdup(id);
    newPatient->ta = ta;
    newPatient->ts = ts;
    return newPatient;
}

Patient* addPatientsToArray(char *input, int *parametr, int capacity) {
    Patient *patients = (Patient*) calloc(capacity, sizeof(Patient));
    if (patients == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int count = 0;
    char *token = strtok(input, "/");

    if (token == NULL) {
        printf("Wrong parameters\n");
        free(patients);
        return NULL;
    }

    while (token != NULL) {
        if (count >= capacity) {
            printf("Exceeded maximum capacity. Ignoring additional patients.\n");
            break;
        }

        Patient *newPatient = (Patient *) calloc(1, sizeof(Patient));

        if (newPatient == NULL) {
            printf("Memory allocation failed.\n");
            free_pat_auxiliary(patients, count);
            return NULL;
        }

        newPatient->id = strdup(token);    //////////
        if (newPatient->id[0] == '*') {
            *parametr = 0;
        } else {
            *parametr = 1;
        }

        token = strtok(NULL, "/");

        if (token == NULL) {
            printf("Wrong parameters\n");
            free(newPatient->id);
            free(newPatient);
            free_pat_auxiliary(patients, count);
            return NULL;
        }

        if (!isNumeric(token)) {
            printf("Error: Second token of patient #%d should be a number.\n", count + 1);
            free(newPatient->id);
            free(newPatient);
            continue;
        }
        newPatient->ta = atoi(token);

        token = strtok(NULL, " ");

        if (token == NULL) {
            printf("Wrong parameters\n");
            free(newPatient->id);
            free(newPatient);
            free_pat_auxiliary(patients, count);
            return NULL;
        }

        if (!isNumeric(token)) {
            printf("Error: Third token of patient #%d should be a number.\n", count + 1);
            free(newPatient->id);
            free(newPatient);
            continue;
        }
        newPatient->ts = atoi(token);
        patients[count] = *newPatient;
        count++;
        free(newPatient);
        token = strtok(NULL, "/");
    }
    *parametr = count;
    return patients;
}

int comparePatientsByTA(const void *a, const void *b) {
    const Patient *pa = (const Patient *)a;
    const Patient *pb = (const Patient *)b;
    return pa->ta - pb->ta;
}

// Функция для сортировки массива пациентов по полю "ta"
void sortPatientsByTA(Patient *patients, int count) {
    qsort(patients, count, sizeof(Patient), comparePatientsByTA);
}