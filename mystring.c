#define NULL 0

// length
int my_strlen(char *str);

// copy
void my_strcpy(char *dest, char *src);
void my_strncpy(char *dest, char *src, int n);
void *my_memcpy(void *dest, void *src, int n);
void *my_memmove(void *dest, void *src, int n);
int my_memset(void *dest, int value, int n);

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

int main() {

	return 0;
}

// length

int my_strlen(char *str) {
  int i;

  for ( i = 0; str[i] != '\0' ; i++) {
    if (str[i] == '\0') {
      break;
    }
  }

  return i;
}

// copy

void my_strcpy(char *dest, char *src) {
  int i = 0;
  while(src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';

}

void my_strncpy(char *dest, char *src, int n) {
  int i = 0;
  while(src[i] != '\0' && i != n) {
    dest[i] = src[i];
    i++;
  }
  if (i < n) {
    dest[i] = '\0';
  }
}

void *my_memcpy(void *dest, void *src, int n) {
  int i = 0;
  char *x = dest;
  char *y = src;

  while( i < n ) {
    x[i] = y[i];
    i++;
  }
  return x;
}

void *my_memmove(void *dest, void *src, int n) {
  char *x = dest;
  char *y = src;

  if ( x < y ) {
    int i = 0;
    while( i < n ) {
      x[i] = y[i];
      i++;
    }
  }
  if ( x > y ) {
    int i = n - 1;
    while( i >= 0 ) {
      x[i] = y[i];
      i--;
    }
  }
  return x;
}

int my_memset(void *dest, int value, int n) {

}

// concatenate

void my_strcat(char *dest, char *src) {
  int i = my_strlen(dest);
  int j = 0;
  while( src[j] != '\0') {
    dest[i] = src[j];
    i++;
    j++;
  }
  dest[i] = '\0';
}

void my_strncat(char *dest, char *src, int n) {
  int i = my_strlen(dest);
  int j = 0;
  while( src[j] != '\0' && j != n) {
    dest[i] = src[j];
    i++;
    j++;
  }
  dest[i] = '\0';
}

// compare

int my_strcmp(char *a, char *b) {
  int i = 0;
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

int my_strncmp(char *a, char *b, int n) {
  int i = 0;
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

int my_memcmp(void *a, void *b, int n) {
  int i = 0;
  char *x = a;
  char *y = b;
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

char* my_strchr(char *str, char c) {
  int i = 0;
  while (str[i] != c && str[i] != '\0') {
    i++;
  }
  if (str[i] == c) {
    return &str[i];
  }
  return NULL;
}

char* my_strrchr(char *str, char c) {
  int i = my_strlen(str);
  while (i >= 0 && str[i] != c) {
    i--;
  }
  if (i >= 0) {
    return &str[i];
  }
  return NULL;
}

char* my_strstr(char *str, char *c) {
  int size = my_strlen(str);

  for (int i = 0; i < size; i++) {
    int n = 0;
    while (str[i + n] == c[n] && str[i + n] != '\0' && c[n] != '\0') {
      n++;
    }
    if (c[n] == '\0') {
      return &str[i];
    }
  }
  return NULL;
}
