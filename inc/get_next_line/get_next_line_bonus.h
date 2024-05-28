#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
char	*get_next_line(int fd);
char	*get_line(char *buffer, ssize_t size);
char	*fill_buffer(int fd, char *buffer);
char	*realloc_buffer(char *ptr, size_t l1, size_t l2);
#endif