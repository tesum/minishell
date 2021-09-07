#include "../libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	size;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(size);
	if (join == NULL)
		return (NULL);
	join[size - 1] = '\0';
	ft_memcpy(join, s1, ft_strlen(s1));
	ft_memcpy(join + ft_strlen(s1), s2, ft_strlen(s2));
	free (s1);
	s1 = NULL;
	return (join);
}

static int	free_all(char **line, char *buf, char **keepread, int i)
{
	if (*line != NULL && i == -1)
	{
		free(*line);
		*line = NULL;
	}
	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
	if (*keepread != NULL && i < 1)
	{
		free(*keepread);
		*keepread = NULL;
	}
	if (i == 0 && *line == NULL)
		return (free_all(line, buf, keepread, -1));
	return (i);
}

static int	read_n(int fd, char *buffer_read, char **line, char **keepread)
{
	int	read_byte;

	read_byte = read(fd, buffer_read, BUFFER_SIZE);
	buffer_read[read_byte] = '\0';
	if (read_byte == 0)
	{
		*line = ft_strdup(*keepread);
		return (free_all(line, buffer_read, keepread, 0));
	}
	*keepread = ft_strjoin_gnl(*keepread, buffer_read);
	if (*keepread == NULL)
		return (free_all(line, buffer_read, keepread, -1));
	return (free_all(line, NULL, keepread, read_byte));
}

static int	find_n(int fd, char *buffer_read, char **line, char **keepread)
{
	char	*buf;
	int		i;

	i = 1;
	while (i > 0)
	{
		buf = ft_strchr(*keepread, '\n');
		if (buf != NULL)
		{
			*buf = '\0';
			*line = ft_strdup(*keepread);
			buf = ft_strdup(buf + 1);
			if (*line == NULL || buf == NULL)
				return (free_all(line, buf, keepread, -1));
			free(*keepread);
			*keepread = buf;
			return (free_all(line, buffer_read, keepread, 1));
		}
		i = read_n(fd, buffer_read, line, keepread);
	}
	return (i);
}

int	get_next_line(int fd, char **line)
{
	static char	*keepread[FD_SIZE];
	char		*buffer_read;

	if (BUFFER_SIZE < 1 || !line || fd < 0 || read(fd, 0, 0) < 0)
		return (-1);
	buffer_read = malloc(BUFFER_SIZE + 1);
	if (buffer_read == NULL)
		return (-1);
	if (keepread[fd] == NULL)
	{
		keepread[fd] = ft_strdup("");
		if (keepread[fd] == NULL)
		{
			free(buffer_read);
			buffer_read = NULL;
			return (-1);
		}
	}
	return (find_n(fd, buffer_read, line, &keepread[fd]));
}
