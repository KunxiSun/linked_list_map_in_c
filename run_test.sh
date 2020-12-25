#!/bin/bash

gcc src/test/tests.c src/linked_list_map.c -o run -O0 -Wall -Werror -Werror=vla -g -std=gnu11 -lm -lpthread -fsanitize=address

./run

rm run