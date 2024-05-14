CC = gcc
CFLAGS = -Wall -Wextra -Wall -ftrapv -g

# Файлы для вектора
VEC_FILES = patient_vec.c deq_vec.c main_vec.c queue_status_vec.c

# Файлы для списка
LIST_FILES = patient_list.c deq_list.c main_list.c queue_status_list.c

all: vector list

vector: $(VEC_FILES)
	$(CC) $(CFLAGS) -DUSE_VECTOR $(VEC_FILES) -o program_vector

list: $(LIST_FILES)
	$(CC) $(CFLAGS) -DUSE_LIST $(LIST_FILES) -o program_list

clean:
	rm -f program_vector program_list

.PHONY: all vector list clean


# как запускать пример для вектора
# make vector
# valgrind ./program_vector

