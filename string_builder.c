
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_builder.h"

void sb_init(string_builder *sb, size_t initial_capacity) {
    sb->str = (char *)malloc(initial_capacity);
    if (sb->str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    sb->str[0] = '\0'; // Initialize with empty string
    sb->length = 0;
    sb->capacity = initial_capacity;
}

void sb_append(string_builder *sb, const char *new_str) {
    size_t new_len = strlen(new_str);
    if (sb->length + new_len + 1 > sb->capacity) {
        // Need to reallocate
        size_t new_capacity = (sb->capacity + new_len) * 2;
        sb->str = (char *)realloc(sb->str, new_capacity);
        if (sb->str == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(-1);
        }
        sb->capacity = new_capacity;
    }

    strcat(sb->str, new_str);

    sb->length += new_len;
}

void sb_empty(string_builder *sb) {
    sb->str[0] = '\0';
    sb->length = 0;
}

void sb_free(string_builder *sb) {
    free(sb->str);
    sb->str = NULL;
    sb->length = 0;
    sb->capacity = 0;
}
