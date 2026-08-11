# mystring

A from-scratch reimplementation of `<string.h>` in raw C — no standard library
includes, not even for `NULL` (it's defined by hand at the top of the file).
The goal is to rebuild the mental model behind each function, not just match
its behavior.

## Progress

**11 of 22** functions from the ISO C `<string.h>` header are implemented.
Excluding the three functions that are locale/errno-dependent and don't
really fit this kind of exercise (`strcoll`, `strxfrm`, `strerror`), that's
**11 of 19 (~58%)**.

Implemented: `strlen`, `strcpy`, `strncpy`, `strcat`, `strncat`, `strcmp`,
`strncmp`, `strchr`, `strrchr`, `strstr`, `memcpy`

Remaining: `memmove`, `memcmp`, `memchr`, `memset`, `strspn`, `strcspn`,
`strpbrk`, `strtok`

## Setup

```c
#define NULL 0
```

Since no headers are included, `NULL` isn't available from `<stddef.h>` —
it's defined manually as a plain `0`, which is a valid null pointer constant
in C.

## Functions

### `int my_strlen(char *str)`

Returns the number of characters in `str` before the terminating `'\0'`.
Walks the string one index at a time until it hits the terminator, and
returns how far it got.

```c
int my_strlen(char *str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == '\0') {
      break;
    }
  }
  return i;
}
```

### `void my_strcpy(char *dest, char *src)`

Copies `src` into `dest`, character by character, until it hits `src`'s
terminator — then writes a `'\0'` into `dest` at that same position.
Assumes `dest` has enough room for all of `src` plus the terminator; unlike
`strncpy`, there's no length limit here.

### `void my_strncat(char *dest, char *src, int n)`

Appends up to `n` characters from `src` onto the end of `dest`. Two indices
are used for a reason: `i` starts at `my_strlen(dest)` (where writing should
begin) and tracks the absolute position in `dest`; `j` starts at `0` and
counts how many characters have been copied *from `src`* — the loop bound
(`j != n`) has to be checked against the count copied, not against `i`,
otherwise `dest`'s existing length would eat into the budget meant for
`src`. Unlike `strncpy`, `strncat` **always** null-terminates the result
unconditionally after the loop, regardless of whether the `n` limit was hit.

```c
void my_strncat(char *dest, char *src, int n) {
  int i = my_strlen(dest);
  int j = 0;
  while (src[j] != '\0' && j != n) {
    dest[i] = src[j];
    i++;
    j++;
  }
  dest[i] = '\0';
}
```

### `int my_strcmp(char *a, char *b)`

Compares two strings character by character. Returns `0` if equal, a
negative value if `a` sorts before `b`, positive if `a` sorts after `b`
(mirroring the real `strcmp` contract — the exact magnitude isn't
meaningful, just the sign). Walks both strings in lockstep until either a
mismatch is found or one of them terminates, then compares whatever
characters (including a possible `'\0'`) are sitting at the final index.

### `int my_strncmp(char *a, char *b, int n)`

Same idea as `my_strcmp`, but stops comparing after at most `n` characters
— if the first `n` characters are identical (or `n` is reached before a
terminator), the strings are considered equal regardless of what comes
after.

### `char *my_strchr(char *str, char c)`

Returns a pointer to the **first** occurrence of `c` in `str`, or `NULL` if
it isn't found. The loop condition checks `str[i] != '\0'` as well as
`str[i] != c` so the search stops at the end of the string instead of
reading past it — and because the terminator itself is included in the
scan, searching for `c == '\0'` correctly returns a pointer to it (matching
real `strchr` semantics).

```c
char *my_strchr(char *str, char c) {
  int i = 0;
  while (str[i] != c && str[i] != '\0') {
    i++;
  }
  if (str[i] == c) {
    return &str[i];
  }
  return NULL;
}
```

### `char *my_strrchr(char *str, char c)`

Same as `my_strchr` but returns the **last** occurrence instead of the
first. Rather than scanning forward and returning as soon as a match is
found, it starts at the terminator (`my_strlen(str)`) and walks *backward*,
so the first match it hits scanning in that direction is actually the last
one in the string. The loop's stopping condition is index-based (`i >= 0`),
not based on comparing character values — an earlier version of this
function mistakenly stopped when it saw a character equal to `str[0]`'s
*value*, which could halt the scan early if that character happened to
reappear elsewhere in the string, before ever reaching index `0`.

```c
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
```

### `char *my_strstr(char *str, char *c)`

Returns a pointer to the first occurrence of the substring `c` inside
`str`, or `NULL` if `c` never appears. Naive `O(n*m)` approach: for every
starting index `i` in `str`, try to match all of `c` starting there. `n` is
reset to `0` at the top of *every* outer-loop iteration — each candidate
start position gets a fresh comparison against `c` from its beginning. A
match is only reported once the inner `while` walks all the way to `c`'s
terminator (`c[n] == '\0'`); reaching the end of `str` instead just means
that candidate failed, and the search moves on to the next `i`. If `c` is
an empty string, the inner loop never runs, `n` stays `0`, and
`c[0] == '\0'` is immediately true — so it correctly returns `str` itself
on the very first try, matching real `strstr` behavior for an empty needle.

```c
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
```

### `void my_strncpy(char *dest, char *src, int n)`

Copies at most `n` characters from `src` into `dest`. If `src` is shorter
than `n`, the copy stops early (`i < strlen(src)`) and a terminator is
written right after the copied characters. If `src` is `n` characters or
longer, the loop stops with `i == n`, and — matching real `strncpy`'s
(in)famous behavior — **no terminator is written** in that case, since
`dest[n]` may be one byte past the end of a buffer sized to hold exactly
`n` bytes. The `if (i < n)` guard around the terminator write is what
prevents that out-of-bounds write.

```c
void my_strncpy(char *dest, char *src, int n) {
  int i = 0;
  while (src[i] != '\0' && i != n) {
    dest[i] = src[i];
    i++;
  }
  if (i < n) {
    dest[i] = '\0';
  }
}
```

### `void *my_memcpy(void *dest, void *src, int n)`

Copies exactly `n` **bytes** from `src` to `dest`, with no awareness of
`'\0'` at all — this is the first function here that isn't operating on
C-strings. The parameters are `void *` because `memcpy` doesn't assume
anything about the type of data being copied (could be an array, a
`struct`, raw binary data). Since `void *` can't be indexed directly, the
parameters are immediately assigned to local `char *` variables (`x`, `y`)
so the copy can happen one byte at a time. Doesn't handle overlapping
`src`/`dest` regions safely — that's what `memmove` is for.

```c
void *my_memcpy(void *dest, void *src, int n) {
  int i = 0;
  char *x = dest;
  char *y = src;

  while (i < n) {
    x[i] = y[i];
    i++;
  }
  return x;
}
```
