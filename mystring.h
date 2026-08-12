#ifndef MYSTRING_H
#define MYSTRING_H

#ifndef NULL
#define NULL 0
#endif

// length
int my_strlen(char *str);

// copy
void my_strcpy(char *dest, char *src);
void my_strncpy(char *dest, char *src, int n);
void *my_memcpy(void *dest, void *src, int n);
void *my_memmove(void *dest, void *src, int n);
void *my_memset(void *dest, int value, int n);

// concatenate
void my_strcat(char *dest, char *src);
void my_strncat(char *dest, char *src, int n);

// compare
int my_strcmp(char *a, char *b);
int my_strncmp(char *a, char *b, int n);
int my_memcmp(void *a, void *b, int n);

// search
char* my_strchr(char *str, char c);
char* my_strrchr(char *str, char c);
char* my_strstr(char *str, char *c);
char* my_memchr(void *str, int value, int n);
int my_strcspn( char *a, char *b);
int my_strspn( char *a, char *b);
char* my_strpbrk(char *a, char *b);

// tokenize
char *my_strtok(char *str, char *delim);

#endif
