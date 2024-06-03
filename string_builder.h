#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t length;
    size_t capacity;
} string_builder;

// initialize the string_builder
void sb_init(string_builder *sb, size_t initial_capacity);

// appends a string to the string_builder
void sb_append(string_builder *sb, const char *new_str);

// Empties the string_builder without freeing the memory
void sb_empty(string_builder *sb);

// free the string_builder resources
void sb_free(string_builder *sb);
