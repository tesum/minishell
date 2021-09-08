#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
# ifndef FD_SIZE
#  define FD_SIZE 10000
# endif
# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif
# ifndef MIN_INT
#  define MIN_INT -2147483648
# endif

int			get_next_line(int fd, char **line);
char		*ft_strjoin_gnl(char *s1, char *s2);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

long long	ft_atoi(const char *str);
double		ft_atof(char **line);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_memcmp(const void *str1, const void *str2, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);

char		*ft_strchr(const char *str, int ch);
char		*ft_strdup(const char *src);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *str, int ch);
char		*ft_itoa(int n);
char		*ft_substr(char const *s, size_t start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);

void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *str, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *dst, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		*ft_bzero(void *dst, size_t len);
void		*ft_calloc(size_t count, size_t size);

size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef struct s_option
{
	int			error;
	int			flag_minus;
	int			flag_zero;
	int			width;
	int			dot;
	int			precision;
	int			count;
	char		type;
	int			skip;
	int			star_width;
	int			star_precision;
}				t_option;

int			ft_printf(const char *format, ...);
void		init_struct(t_option *options, int len);
void		if_just_dot(t_option *options);
char		*ft_utoa(unsigned int n);
char		*ft_hex(unsigned int num, char x);
char		*ft_ultimate_hex(unsigned long long num, char x);

void		print_num(t_option *options, char *number);
void		print_num2(t_option *options, char *number);
void		print_num3(t_option *options, char *number);

void		pars_flags(char *parsing, t_option *options, va_list ap);
void		pars_width(char *parsing, t_option *options, va_list ap);
void		pars_dot_precision(char *parsing, t_option *options, va_list ap);
void		pars_type(char *parsing, t_option *options, va_list ap);
void		parse_input(char *parsing, t_option *options, va_list ap);

void		reverse(char *s);
void		proc_char(t_option *options, va_list ap);
void		proc_int(t_option *options, va_list ap);
void		proc_percent(t_option *options);
void		proc_pointer(t_option *options, va_list ap);
void		proc_string(t_option *options, va_list ap);
void		proc_uint(t_option *options, va_list ap);
void		proc_hex(t_option *options, va_list ap, char x);
void		proc_notype(t_option *options);
void		proc_n(t_option *options, va_list ap);

#endif
