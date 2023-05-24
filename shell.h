#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} data;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data *);
} builtin_table;


/* shell_loops.c */
int hsh(info_t *, char **);
int find_builtin(data *);
void find_cmd(data *);
void fork_cmd(data *);

/* pointer.c */
int is_cmd(data *, char *);
char *dup_chars(char *, int, int);
char *find_path(data *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* 1-error.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* 1-string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* 2-string.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exit_shell.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tow.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* free.c */
int befree(void **);

/* atoi.c */
int interactive(data *);
int is_delimeter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* 2-error.c */
int _erratoi(char *);
void print_error(data *, char *);
int print_base(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* 1-builtin.c */
int _exit(data *);
int _cd(data *);
int _help(data *);

/* 2-builtin.c */
int _history(data *);
int _alias(data *);

/* get_line.c */
ssize_t get_input(data *);
int _getline(data *, char **, size_t *);
void sigintHandler(int);

/* get_shellinfo.c */
void clear_info(data *);
void set_info(data *, char **);
void free_info(data *, int);

/* env.c */
char *_getenv(data *, const char *);
int _env(data *);
int _setenv(data *);
int _unsetenv(data *);
int populate_env_list(data *);

/* get_environ.c */
char **get_environ(data *);
int _unsetenv(data *, char *);
int _setenv(data *, char *, char *);

/* get_hist.c */
char *get_history_file(data *intel);
int write_history(data *intel);
int read_history(data *intel);
int build_history_list(data *intel, char *buf, int linecount);
int renumber_history(data *intel);

/* 1-list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* 2-list.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


/* chain.c */
int is_chain(data *, char *, size_t *);
void check_chain(data *, char *, size_t *, size_t, size_t);
int replace_alias(data *);
int replace_vars(data *);
int replace_string(char **, char *);


#endif
