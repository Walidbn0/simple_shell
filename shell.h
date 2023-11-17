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


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


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
 *					allowing uniform prototype for function pointer struct
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
	list_t *hist;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **commd_buf; 
	int commd_buf_type;
	int readfd;
	int histcount;
} info_t;

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
	int (*func)(info_t *);
} builtin_table;


/* shlo.c */
int shlo(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_commd(info_t *info);
void fork_commd(info_t *info);

/* path.c */
int is_commd(info_t *info, char *path);
char *dup_chars(char *strpath, int start, int stop);
char *find_path(info_t *inf, char *strpath, char *commd);

/* loophsh.c */
int loophsh(char **);

/* error_str_functions.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fdesc);
int _putsfd(char *str, int fdesc);

/* str_functions.c */
int	ft_strlen(char *str)
int	ft_strcmp(char *s1, char *s2)
char *starts_with(const char *haystack, const char *needle);
char *ft_strcat(char *dest, char *src)

/* str_functions2.c */
char *ft_strcpy(char *dest, char *src)
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* str_functions3.c */
char *ft_strncpy(char *dest, char *src, unsigned int n)
char *ft_strncat(char *dest, char *src, unsigned int nb)
char *_strchr(char *s, char c);

/* str_functions4.c */
char **strtow(char *str, char *deli);
char **strtow2(char *str, char deli);

/* mem_functions */
char *_memset(char *s, char bit, unsigned int n);
void ffree(char **pep);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* mem_functions2.c */
int bfree(void **ptr);

/* more_functions.c */
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *str);

/* more_functions2.c */
int _erratoi(char *s);
void print_error(info_t *info, char *erstr);
int print_de(int input, int fdes);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buff);

/* built_emul.c */
int _myext(info_t *info);
int _mychdir(info_t *info);
int _myhelp(info_t *info);

/* built_emul2.c */
int _myhist(info_t *info);
int unst_alias(info_t *info, char *str);
int st_alias(info_t *info, char *str);
int prnt_alias(list_t *node);
int _myalias(info_t *info);

/* gline.c */
ssize_t input_buff(info_t *info, char **buff, size_t *lengh);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* info.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **argv);
void free_info(info_t *info, int all);

/* envir.c */
char *_getenv(info_t *info, const char *name);
int _myenvir(info_t *info);
int _mysetenvir(info_t *info);
int _myunsetenvir(info_t *info);
int populate_envir_list(info_t *info);

/* envir2.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *val);

/* file_io_funct.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buff, int linecount);
int renumber_history(info_t *info);

/* liststr.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* liststr2.c module */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain.c */
int is_chaiin(info_t *, char *, size_t *);
void check_chaiin(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_string(char **, char *);

#endif
