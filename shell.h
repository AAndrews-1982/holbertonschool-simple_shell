#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int prompt(void);
char *_read(void);
char *_fullpathbuffer(char **av, char *PATH, char *copy);
int checkbuiltins(char **av, char *buffer, int exitstatus);
int _forkprocess(char **av, char *buffer, char *fullpathbuffer);

/* String Helper Functions */

char *_strdup(char *str);
int _splitstring(char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
<<<<<<< HEAD

/*Tokenize & PATH Helper Functions*/

char **tokenize(char *buffer);
int _splitPATH(char *str);
int _PATHstrcmp(const char *s1, const char *s2);
char *_concat(char *tmp, char **av, char *tok);


/*Other Helper Funcs*/

char *_getenv(const char *name);
int _env(void);
void _puts(char *str);
int _putchar(char c);
char *_memset(char *s, char b, unsigned int n);
=======
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
>>>>>>> 9b165e6b717a860f06c0286a391b662382b89dac

#endif
