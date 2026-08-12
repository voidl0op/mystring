#include "mystring.h"

// length

size_t my_strlen(const char *str) {
  size_t i;

  for ( i = 0; str[i] != '\0' ; i++) {
    if (str[i] == '\0') {
      break;
    }
  }

  return i;
}

// copy

void my_strcpy(char *dest, const char *src) {
  size_t i = 0;
  while(src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';

}

void my_strncpy(char *dest, const char *src, size_t n) {
  size_t i = 0;
  while(src[i] != '\0' && i != n) {
    dest[i] = src[i];
    i++;
  }
  if (i < n) {
    dest[i] = '\0';
  }
}

void *my_memcpy(void *dest, const void *src, size_t n) {
  size_t i = 0;
  char *x = dest;
  const char *y = src;

  while( i < n ) {
    x[i] = y[i];
    i++;
  }
  return x;
}

void *my_memmove(void *dest, const void *src, size_t n) {
  char *x = dest;
  const char *y = src;

  if ( x < y ) {
    size_t i = 0;
    while( i < n ) {
      x[i] = y[i];
      i++;
    }
  }
  if ( x > y ) {
    size_t i = n;
    while( i > 0 ) {
      i--;
      x[i] = y[i];
    }
  }
  return x;
}

void *my_memset(void *dest, int value, size_t n) {
  char *x = dest;
  for ( size_t i = 0; i < n; i++) {
    x[i] = value;
  }
  return x;
}

// concatenate

void my_strcat(char *dest, const char *src) {
  size_t i = my_strlen(dest);
  size_t j = 0;
  while( src[j] != '\0') {
    dest[i] = src[j];
    i++;
    j++;
  }
  dest[i] = '\0';
}

void my_strncat(char *dest, const char *src, size_t n) {
  size_t i = my_strlen(dest);
  size_t j = 0;
  while( src[j] != '\0' && j < n) {
    dest[i] = src[j];
    i++;
    j++;
  }
  dest[i] = '\0';
}

// compare

int my_strcmp(const char *a, const char *b) {
  size_t i = 0;
  while( b[i] != '\0' && a[i] != '\0') {
    if ( a[i] != b[i] ) {
      int x = a[i]-b[i];
      if (x == 0) return 0;
      if (x < 0 ) return -1;
      if (x > 0 ) return 1;
    }
    i++;
  }
  int x = a[i] - b[i];
  if (x == 0) return 0;
  if (x < 0 ) return -1;
  return 1;
}

int my_strncmp(const char *a, const char *b, size_t n) {
  size_t i = 0;
  while( b[i] != '\0' && a[i] != '\0' && i != n ) {
    if ( a[i] != b[i] ) {
      int x = a[i]-b[i];
      if (x == 0) return 0;
      if (x < 0 ) return -1;
      if (x > 0 ) return 1;
    }
    i++;
  }
  if ( i == n ) return 0;
  int x = a[i] - b[i];
  if (x == 0) return 0;
  if (x < 0 ) return -1;
  return 1;
}

int my_memcmp(const void *a, const void *b, size_t n) {
  size_t i = 0;
  const char *x = a;
  const char *y = b;
  while(  i != n ) {
    if ( x[i] != y[i] ) {
      int z = x[i]-y[i];
      if (z == 0) return 0;
      if (z < 0 ) return -1;
      if (z > 0 ) return 1;
    }
    i++;
  }
  if ( i == n ) return 0;
  int z = x[i] - y[i];
  if (z == 0) return 0;
  if (z < 0 ) return -1;
  return 1;
}

// search

char* my_strchr(const char *str, char c) {
  size_t i = 0;
  while (str[i] != c && str[i] != '\0') {
    i++;
  }
  if (str[i] == c) {
    return (char *)&str[i];
  }
  return NULL;
}

char* my_strrchr(const char *str, char c) {
  size_t i = my_strlen(str);
  do {
    if (str[i] == c) {
      return (char *)&str[i];
    }
  } while (i-- != 0);
  return NULL;
}

char* my_strstr(const char *str, const char *c) {
  size_t size = my_strlen(str);

  for (size_t i = 0; i < size; i++) {
    size_t n = 0;
    while (str[i + n] == c[n] && str[i + n] != '\0' && c[n] != '\0') {
      n++;
    }
    if (c[n] == '\0') {
      return (char *)&str[i];
    }
  }
  return NULL;
}

char* my_memchr(const void *str, int value, size_t n) {
  const char *x = str;
  size_t i = 0;
  for ( ; i < n; i++) {
    if( x[i] == value) {
      return (char *)&x[i];
    }
  }
  return NULL;
}

size_t my_strcspn(const char *a, const char *b) {
  size_t i = 0;
  size_t j = 0;
  for ( ; i < my_strlen(a); i++) {
    for (j = 0; j < my_strlen(b); j++) {
      if ( a[i] == b[j]) {
        return i;
      }
    }
  }
  return my_strlen(a);
}

size_t my_strspn(const char *a, const char *b) {
  size_t i = 0;
  size_t j = 0;
  for ( ; i < my_strlen(a); i++) {
    int found = 0;
    for (j = 0; j < my_strlen(b); j++) {
      if ( a[i] == b[j]) {
        found = 1;
        break;
      }
    }
    if ( found == 0) return i;
  }
  return my_strlen(a);
}

char *my_strpbrk(const char *a, const char *b) {
  size_t i = 0;
  size_t j = 0;
  for ( ; i < my_strlen(a); i++) {
    for (j = 0; j < my_strlen(b); j++) {
      if ( a[i] == b[j]) {
        return (char *)&a[i];
      }
    }
  }
  return NULL;
}

// tokenize

char *my_strtok(char *str, const char *delim) {
  static char *pos = NULL;
  size_t i = 0;
  size_t j = 0;

  if ( str == NULL ) {
    str = pos;
  }

  if ( str == NULL || str[0] == '\0' ) {
    return NULL;
  }

  for ( ; i < my_strlen(str) ; i++) {
    for ( j  = 0; j < my_strlen(delim) ; j++) {
      if ( str[i] == delim[j] ) {
        str[i] = '\0';
        pos = &str[i + 1];
        return str;
      }
    }
  }
  pos = NULL;
  return str;
}
