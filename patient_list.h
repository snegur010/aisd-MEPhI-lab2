#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

typedef struct Patient {
    char *id;
    int ts;
    int ta;
} Patient;

typedef struct Item {
    Patient *patient;
    struct Item *next;
    struct Item *prev;
} Item;

int comparePatientsByTA(const void *a, const void *b);

void sortPatientsByTA(Patient *patients, int count);

Item* createItem(Patient *patient);

void freeItem(Item *item);

Patient* addPatientsToArray(char *input, int *parametr, int capacity);

void free_pat_auxiliary(Patient *patients, int count);

#endif /* PATIENT_LIST_H */