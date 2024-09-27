#include "get_next_line.h"

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i = 0;
	char	*dest = (char *)s1;
	char	*src = (char *)s2;
	while (i < n)
    {
		dest[i] = src[i];
        i++;
    }
	return (dest);
}

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *new_ptr;
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL)
        return (malloc(new_size));
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    free(ptr);
    return (new_ptr);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int	bytes_read = 0;
	static int	pos = 0;
	char *line = NULL;
	int len = 0;
    int old_size = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (pos >= bytes_read)
		{
			pos = 0;
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break;
		}
		for (; pos < bytes_read; pos++)
		{
			if (buffer[pos] == '\n')
			{
				line = ft_realloc(line, old_size, len + 2);
				if (!line)
					return (NULL);
				line[len++] = '\n';
				line[len] = '\0';
				pos++;
				return (line);
			}
			line = ft_realloc(line, old_size, len + 2);
			if (!line)
				return (NULL);
			line[len++] = buffer[pos];
            old_size = len + 1;
		}
	}
	if (len > 0)
	{
		line[len] = '\0';
		return (line);
	}
	free(line);
	return (NULL);
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
