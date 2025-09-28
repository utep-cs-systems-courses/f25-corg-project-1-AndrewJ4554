#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

/* =====================================================
   Helper functions for working with strings and tokens
   ===================================================== */

/*
 * string_length:
 *   Counts the number of characters in a string until
 *   the null terminator '\0' is found.
 *   Equivalent to strlen(), but written manually since
 *   we are not allowed to use <string.h>.
 */
int string_length(char *s) {
    int len = 0;
    while (s && s[len] != '\0') len++;
    return len;
}

/*
 * is_valid_character:
 *   Checks if a character is part of a token.
 *   Rules:
 *     - Valid characters are anything that is NOT
 *       a space (' '), tab ('\t'), or null terminator.
 */
int is_valid_character(char c) {
    return (c != ' ' && c != '\t' && c != '\0');
}

/*
 * find_word_start:
 *   Given a string pointer, skips over spaces and tabs
 *   until it finds the first valid (non-space) character.
 *   Returns:
 *     - Pointer to the first character of the token
 *     - NULL if no tokens remain
 */
char *find_word_start(char *s) {
    if (!s) return NULL;
    // Skip over all invalid characters (spaces/tabs)
    while (*s != '\0' && !is_valid_character(*s)) s++;
    // If we stopped at '\0', no token remains
    return (*s == '\0') ? NULL : s;
}

/*
 * find_word_terminator:
 *   Given the start of a word, moves forward until it
 *   reaches the end of the word (first space, tab, or '\0').
 *   Returns:
 *     - Pointer to the first character AFTER the token.
 */
char *find_word_terminator(char *s) {
    if (!s) return NULL;
    while (*s != '\0' && is_valid_character(*s)) s++;
    return s;
}

/*
 * count_words:
 *   Counts how many tokens (words) exist in a string.
 *   Algorithm:
 *     - Start scanning at the beginning of the string
 *     - Use find_word_start to locate start of token
 *     - Use find_word_terminator to locate end
 *     - Repeat until no more tokens are found
 */
int count_words(char *s) {
    if (!s) return 0;
    int count = 0;
    char *p = s;

    while (1) {
        char *start = find_word_start(p);
        if (!start) break;             // No more tokens
        char *end = find_word_terminator(start);
        count++;
        p = end;                       // Continue searching after this word
    }
    return count;
}

/*
 * copy_str:
 *   Allocates memory for a substring of given length
 *   and copies it from the source string.
 *   Input:
 *     - inStr: pointer to source string
 *     - len: number of characters to copy
 *   Output:
 *     - malloc’d string with '\0' terminator
 */
char *copy_str(char *inStr, short len) {
    char *out = (char*) malloc(len + 1);  // +1 for '\0'
    if (!out) return NULL;

    // Copy each character
    for (short i = 0; i < len; i++) {
        out[i] = inStr[i];
    }
    out[len] = '\0';  // Null terminate
    return out;
}

/* =====================================================
   Wrappers for functions defined in tokenizer.h
   These map our helper functions to the project spec.
   ===================================================== */

/*
 * space_char:
 *   Returns true if the character is a space or tab.
 */
int space_char(char c) {
    return (c == ' ' || c == '\t');
}

/*
 * non_space_char:
 *   Returns true if the character is NOT a space/tab
 *   and not the null terminator.
 */
int non_space_char(char c) {
    return (c != ' ' && c != '\t' && c != '\0');
}

/*
 * token_start:
 *   Wrapper for find_word_start().
 *   Finds first non-space character of the next token.
 */
char *token_start(char *str) {
    return find_word_start(str);
}

/*
 * token_terminator:
 *   Wrapper for find_word_terminator().
 *   Finds the end (1 char past last) of the current token.
 */
char *token_terminator(char *token) {
    return find_word_terminator(token);
}

/*
 * count_tokens:
 *   Wrapper for count_words().
 *   Returns number of tokens in the input string.
 */
int count_tokens(char *str) {
    return count_words(str);
}

/* =====================================================
   Token array functions (Part C, safe to stub early)
   ===================================================== */

/*
 * tokenize:
 *   Splits an input string into an array of tokens.
 *   Steps:
 *     1. Count how many tokens exist (n).
 *     2. Allocate an array of (n+1) pointers to char.
 *        (+1 for the NULL sentinel at the end)
 *     3. For each token:
 *          - Find the start
 *          - Find the end
 *          - Copy the substring into a new malloc’d string
 *          - Store pointer in array
 *     4. Add NULL at the end of the array.
 */
char **tokenize(char *str) {
    int n = count_words(str);  // Total number of tokens
    char **tokens = (char**) malloc((n + 1) * sizeof(char*));
    if (!tokens) return NULL;

    char *p = str;
    int idx = 0;

    while (idx < n) {
        char *start = find_word_start(p);          // beginning of token
        char *end = find_word_terminator(start);   // end of token
        short len = (short)(end - start);          // token length
        tokens[idx] = copy_str(start, len);        // copy token into new string
        idx++;
        p = end;                                   // move forward for next loop
    }

    tokens[n] = NULL;  // Sentinel value
    return tokens;
}

/*
 * print_tokens:
 *   Prints each token from the array on its own line.
 *   Stops when NULL sentinel is reached.
 */
void print_tokens(char **tokens) {
    if (!tokens) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("%s\n", tokens[i]);
    }
}

/*
 * free_tokens:
 *   Frees all memory allocated for tokens.
 *   Algorithm:
 *     - Free each individual string
 *     - Free the array of pointers itself
 */
void free_tokens(char **tokens) {
    if (!tokens) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
