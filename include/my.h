/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** Contains the prototypes of all the functions exposed by libmy.a.
*/

#ifndef MY_H
#define MY_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define READ_SIZE 5

#define ALLOW "abcdefghijklmnopqrstuvwxyz"
#define ALUP "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUM "0123456789"

#define IS_ALLOW 1
#define IS_ALUP 2
#define IS_NUM 4
#define IS_ALNUM 8

#define ABS(value) (((value > 0) ? (value) : (-value)))

typedef struct format_id {
	int legit;
	int length;
	char flags[6];
	int nb_flag;
	int min_width;
	int precision;
	char type;
}format_id_t;

typedef enum {
	FALSE,
	TRUE
}bool_t;

//write
void my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);

//printf
int my_printf(char *str, ...);
int my_sprintf(char **str, const char *format, ...);
int my_fprintf(int fd, const char *format, ...);
char *put_var_showstr(char *str, va_list ap);
char *put_var(char *str, format_id_t *fid, va_list ap);
char *put_spaces(char *str, format_id_t *fid, int min_width);
char *put_precision(char *cat, format_id_t const *fid, va_list ap);
char *put_var_nbr(char *str, format_id_t const *fid, va_list ap);
int display_fid(format_id_t *fid, va_list ap, int *bytes);
format_id_t *get_format_id(char const *str, int pos);
format_id_t *init_format_id(void);
char *my_push_back(char *str, char const cat);
char *my_pushstr_back(char *str, char const *cat);
char *my_insert_char(char *str, char const cat, int const pos);
char *my_insert_str(char *str, char const *cat, int const pos);
char *str_fid(format_id_t *fid, va_list ap, int *bytes);

//conversion
int my_getnbr(char const *str);
char *int_str(long nb);
char int_char(int const n);
char *put_nbr_to_base(long nbr, char const *base);
void incr10_str(char *str);
int find_power_10(long n);

//math
int my_pow(int nb, int power);
int my_sqrt(int nb);
int my_gcd(int a, int b);

//files
char *my_read_all(int fd);
char *my_fread_all(FILE *file);
int my_fgetnbr(FILE *file);
char *get_next_line(int fd);

//alloc
void *my_malloc(int size);
void *my_realloc(void *ptr, int const size);
void *my_memset(void *s, char c, size_t n);

//my_str
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char const *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strlowcase(char *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
char *my_revstr(char *str);
char *my_strdup(char const *str);
int in_str(char const c, char const *str);
bool_t my_str_is(const char *str, const int option);
char **my_str_split(const char *str, const char sep);
void my_strcut(char *str, const char end);
int my_str_seek(const char *str, const char *seek);

//other
void my_swap(int *a, int *b);

#endif
