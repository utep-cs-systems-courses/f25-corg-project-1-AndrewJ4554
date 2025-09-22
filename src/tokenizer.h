#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

/* ========== Helper functions for tester.c ========== */

int string_length(char *s) {
    int len = 0;
    while (s && s[len] != '\0') len++;
    return len;
}

int is_valid_character(char c) {
    return (c != ' ' && c != '\t' && c != '\0');
}

char *find_word_start(char *s) {
    if (!s) return NULL;
    while (*s != '\0' && !is_valid_character(*s)) s++;
    return (*s == '\0') ? NULL : s;
}

char *find_word_terminator(char *s) {
    if (!s) return NULL;
    while (*s != '\0' && is_valid_character(*s)) s++;
    return s;
}

int count_words(char *s) {
    if (!s) return 0;
    int count = 0;
    char *p = s;
    while (1) {
        char *start = find_word_start(p);
        if (!start) break;
        char *end = find_word_terminator(start);
        count++;
        p = end;
    }
    return count;
}

/* make a malloc’d copy of inStr[len] */
char *copy_str(char *inStr, short len) {
    char *out = (char*) malloc(len + 1);
    if (!out) return NULL;
    for (short i = 0; i < len; i++) {
        out[i] = inStr[i];
    }
    out[len] = '\0';
    return out;
}

/* ========== Wrappers to match Tokenizer.h ========== */

int space_char(char c) {
    return (c == ' ' || c == '\t');
}

int non_space_char(char c) {
    return (c != ' ' && c != '\t' && c != '\0');
}

char *token_start(char *str) {
    return find_word_start(str);
}

char *token_terminator(char *token) {
    return find_word_terminator(token);
}

int count_tokens(char *str) {
    return count_words(str);
}

/* ========== Token array functions (Part C, but safe to stub early) ========== */

char **tokenize(char *str) {
    int n = count_words(str);
    char **tokens = (char**) malloc((n + 1) * sizeof(char*));
    if (!tokens) return NULL;

    char *p = str;
    int idx = 0;
    while (idx < n) {
        char *start = find_word_start(p);
        char *end = find_word_terminator(start);
        short len = (short)(end - start);
        tokens[idx] = copy_str(start, len);
        idx++;
        p = end;
    }
    tokens[n] = NULL;
    return tokens;
}

void print_tokens(char **tokens) {
    if (!tokens) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("%s\n", tokens[i]);
    }
}

void free_tokens(char **tokens) {
    if (!tokens) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
