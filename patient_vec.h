#ifndef PATIENT_VEC_H
#define PATIENT_VEC_H

// Структура пациента
typedef struct Patient {
    char *id;
    int ta;
    int ts;
} Patient;

// Освобождение памяти, выделенной для пациента
void freePatient(Patient *patient);

// Создание пациента
Patient* createPatient(char *id, int ta, int ts);

Patient* addPatientsToArray(char *input, int *parametr, int capacity);

int comparePatientsByTA(const void *a, const void *b);

void sortPatientsByTA(Patient *patients, int count);

void free_pat_auxiliary(Patient *patients, int count);

#endif /* PATIENT_H */

