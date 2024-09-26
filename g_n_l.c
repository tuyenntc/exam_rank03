#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_ptr;

	if (!s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	str_ptr = str;
	if (s1 != NULL)
	{
		while (*s1)
			*str++ = *s1++;
	}
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str_ptr);
}

char *remaining(char *buffer)
{
	int i = 0;
	int j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	char *new = malloc(ft_strlen(buffer) - i);
	if (!new)
		return (NULL);
	i++;
	while (buffer[i])
		new[j++] = buffer[i++];
	new[j] = '\0';
	free(buffer);
	return (new);
}

char *get_line(char *buffer)
{
	int i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	char *line = malloc(i + (buffer[i] == '\n') + 1);
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = buffer[j];
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char *save_line(int fd, char *buffer)
{
	char tmp[BUFFER_SIZE + 1];
	int bytes_read;
	char *old;
	while ((bytes_read = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[bytes_read] = '\0';
		old = buffer;
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (free(old), NULL);
		free(old);
		if (ft_strchr(tmp, '\n'))
			break;
	}
	return (bytes_read == -1 ? (free(buffer), NULL) : buffer);
}

char *get_next_line(int fd)
{
	static char *buffer;
	char *line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = save_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = remaining(buffer);
	return (line);
}

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char	*line;
	int		count;

	if (fd == -1)
	{
		perror("error opening file");
		return (1);
	}
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		printf("line %d >> %s\n", count, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

