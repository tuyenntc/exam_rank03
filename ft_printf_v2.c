#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	put_str(char *s)
{
	int i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}


int	put_nb(long nb, int base)
{
	char *s = "0123456789abcdef";
	int i = nb % base;
	int count;
	if (nb / base > 0)
		count += put_nb(nb / base, base);
	count += ft_putchar(s[i]);
	return (count);
}

int	handle_format(char *s, va_list args)
{
	int i = 0;
	int n = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			n += put_str(va_arg(args, char *));
			i += 2;
		}
		else if (s[i] == '%' && s[i + 1] == 'd')
		{
			n += put_nb(va_arg(args, int), 10);
			i += 2;
		}
		else if (s[i] == '%' && s[i + 1] == 'x')
		{
			n += put_nb(va_arg(args, int), 16);
			i += 2;
		}
		else
		{
			write(1, &s[i], 1);
			n++;
			i++;
		}
	}
	return (n);
}

int	ft_printf(char *s, ...)
{
	va_list	args;
	va_start(args, s);
	int n = handle_format(s, args);
	va_end(args);
	return (n);
}

int	main(void)
{
	ft_printf("Magic %s is %d", "number", 42);
}
