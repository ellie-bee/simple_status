#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUILD_LENGTH 1024
#define INITIAL_CAPACITY 128

typedef struct {
    char *str;
    size_t length;
    size_t capacity;
} string_builder;

void sb_init(string_builder *sb, size_t initial_capacity);

string_builder sb_new();

const char *sb_build(string_builder *sb);

#define sb_append(sb, ...) sb_append_many_null(sb, ##__VA_ARGS__, NULL)
void sb_append_many_null(string_builder *sb, ...);

#define sb_sep_by(sb, sep, ...) sb_sep_by_many_null(sb, sep, ##__VA_ARGS__, NULL)
void sb_sep_by_many_null(string_builder *sb, const char *separator, ...);

void sb_empty(string_builder *sb);

void sb_free(string_builder *sb);
