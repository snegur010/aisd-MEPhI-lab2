#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patient_list.h"
#include "queue_status_list.h"


int comparePatientsByTA(const void *a, const void *b) {
    const Patient *pa = (const Patient *)a;
    const Patient *pb = (const Patient *)b;
    return pa->ta - pb->ta;
}

void sortPatientsByTA(Patient *patients, int count) {
    qsort(patients, count, sizeof(Patient), comparePatientsByTA);
}

Item* createItem(Patient *patient) {
    Item *newItem = (Item*) calloc(1, sizeof(Item));
    if (newItem == NULL) {
        return NULL;
    }
    newItem->patient = patient;
    newItem->next = NULL;
    newItem->prev = NULL;
    return newItem;
}

void freeItem(Item *item) {
    free(item->patient->id);
    free(item->patient);
    free(item);
}

Patient* addPatientsToArray(char *input, int *parametr, int capacity) {
    capacity = capacity - 1 + 1;
    Patient *patients = (Patient*) calloc(1, sizeof(Patient)); 
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
        Patient *newPatient = (Patient*) calloc(1, sizeof(Patient));
        if (newPatient == NULL) {
            printf("Memory allocation failed.\n");
            free_pat_auxiliary(patients, count);
            return NULL;
        }

        newPatient->id = strdup(token); ////////

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

        if (token != NULL) {
            patients = realloc(patients, (count + 1) * sizeof(Patient));
        }
    }
    *parametr = count;
    return patients;
}


void free_pat_auxiliary(Patient *patients, int count) {
    for (int i = 0; i < count; i++) {
        free(patients[i].id);
    }
    free(patients);
}