
#include <stdarg.h>
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

string_builder sb_new() {
    string_builder sb = {0};
    sb_init(&sb, INITIAL_CAPACITY);
    return sb;
}

char output_buffer[MAX_BUILD_LENGTH];
const char *sb_build(string_builder *sb) {
    if(sb->length > MAX_BUILD_LENGTH) {
        fprintf(stderr, "Failed to build string, consider increasing MAX_BUILD_LENGTH");
        exit(-1);
    }

    strcpy(output_buffer, sb->str);

    sb_free(sb);

    return output_buffer;
}

void sb_append_single(string_builder *sb, const char *new_str) {
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

void sb_append_many_null(string_builder *sb, ...) {
    va_list args;
    va_start(args, sb);

    const char *str = va_arg(args, const char *);
    while( str != NULL) {
        sb_append_single(sb, str);
        str = va_arg(args, const char *);
    }
    va_end(args);
}

void sb_sep_by_many_null(string_builder *sb, const char *separator, ...) {
    va_list args;
    va_start(args, separator);

    const char *str = va_arg(args, const char *);
    while( str != NULL) {
        sb_append_single(sb, str);
        str = va_arg(args, const char *);
        if(str != NULL) {
            sb_append_single(sb, separator);
        }
    }
    va_end(args);
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
