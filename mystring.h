#ifndef MYSTRING_H
#define MYSTRING_H

#ifndef NULL
#define NULL 0
#endif

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

// length
size_t my_strlen(const char *str);

// copy
void my_strcpy(char *dest, const char *src);
void my_strncpy(char *dest, const char *src, size_t n);
void *my_memcpy(void *dest, const void *src, size_t n);
void *my_memmove(void *dest, const void *src, size_t n);
void *my_memset(void *dest, int value, size_t n);

// concatenate
void my_strcat(char *dest, const char *src);
void my_strncat(char *dest, const char *src, size_t n);

// compare
int my_strcmp(const char *a, const char *b);
int my_strncmp(const char *a, const char *b, size_t n);
int my_memcmp(const void *a, const void *b, size_t n);

// search
char* my_strchr(const char *str, char c);
char* my_strrchr(const char *str, char c);
char* my_strstr(const char *str, const char *c);
char* my_memchr(const void *str, int value, size_t n);
size_t my_strcspn(const char *a, const char *b);
size_t my_strspn(const char *a, const char *b);
char* my_strpbrk(const char *a, const char *b);

// tokenize
char *my_strtok(char *str, const char *delim);

#endif
