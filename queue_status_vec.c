#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "queue_status_vec.h"
#include "patient_vec.h"
#include "deq_vec.h"


int individual(Deq *deq, Patient *patients, int count) { //count - количество успешно считанных пациентов во временный массив
    Patient *currentPatient = NULL;
    int res = 0;
    int index = 1;
    insertByIndex(deq, patients, 0);

    int curr_time = patients[0].ta;
    for (int i = 1; i < count; i++) {
        if (patients[i].ta == curr_time) {
            insertByIndex(deq, patients, i);
            index++;
        }
    }

    res = remove_from_head(deq, &currentPatient);
    if (res == 1) {
        return 1;
    }
    char *id = currentPatient->id;
    int end = currentPatient->ta + currentPatient->ts;

    while (index <= count) { 
        printf("%d\n", curr_time);
        printf("%s   ", id);
        if (!DeqIsEmpty(deq)) {
            deq_print(deq);
        } else {
            printf("\n");
        }

        if ((index <= count - 1) && patients[index].ta < end) {
            curr_time = patients[index].ta;
            insertByIndex(deq, patients, index);
            index++;
            while ((index <= count - 1) && patients[index].ta == curr_time) {
                res = insertByIndex(deq, patients, index);
                index++;
            }
        } else {
            if (!DeqIsEmpty(deq)) {
                while ((index <= count - 1) && patients[index].ta == end) {
                    insertByIndex(deq, patients, index);
                    index++;
                }
                res = remove_from_head(deq, &currentPatient);
                if (res == 1) {
                    return 1;
                }
                id = currentPatient->id;
                curr_time = end;
                end = curr_time + currentPatient->ts;
                for (int i = index; i < count; i++) {
                    if (patients[i].ta == curr_time) { 
                        insertByIndex(deq, patients, index);
                        index++;
                    }
                }
            } else {
                if (index == count) {
                    printf("%d\n", end);
                    printf("empty\n");
                    index++;
                } else {
                    curr_time = patients[index].ta;
                    if (curr_time != end) {
                        printf("%d\n", end);
                        printf("empty\n");
                    }
                    for (int i = index; i < count; i++) {
                        if (patients[i].ta == curr_time) {
                            insertByIndex(deq, patients, i);
                            index++;
                             
                        }
                    }
                    res = remove_from_head(deq, &currentPatient);
                    if (res == 1) {
                        return 1;
                    }
                    id = currentPatient->id;
                    end = curr_time + currentPatient->ts;
                }
            }
        }
    }
    return 0;
}

int isNumeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

char* my_readline(const char *str) {
    printf("%s", str);
    int b_size = 50, f = 0;
    char *res = (char *) calloc (b_size, sizeof(char));
    if (res == NULL) {
        return NULL;
    }
    while ((f = scanf("%49[^\n]", res + b_size - 50)) == 1) { 
        b_size += 49;
        res = realloc(res, b_size * sizeof(char));
    }
    if (f == -1) {
        free(res);
        return NULL;
    }
    int clen = strlen(res);
    res = realloc(res, (clen + 1) * sizeof(char));
    scanf("%*c"); //игнорируем символ новой строки оставшийся в потоке ввода
    return res;
}
