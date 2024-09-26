#include <unistd.h>
#include <stdarg.h>

int	put_str(char *s)
{
	if (!s)
		s = "(null)";
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	put_nb(long nb, int base)
{
	char	*s = "0123456789abcdef";
	char	buf[50];
	int i = 0;
	int len = 0;
	if (nb < 0 && base == 10)
	{
		write(1, "-", 1);
		nb = -nb;
		len++;
	}
	else if (nb < 0 && base == 16)
		nb = (unsigned int)nb;
	if (nb == 0)
	{
		write(1, "0", 1);
		return (len + 1);
	}
	while (nb)
	{
		buf[i++] = s[nb % base];
		nb /= base;
	}
	len += i;
	while (i--)
		write(1, &buf[i], 1);
	return (len);
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
			n += put_nb(va_arg(args, unsigned int), 16);
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
	va_list args;
	va_start(args, s);
	int n = handle_format(s, args);
	va_end(args);
	return (n);
}

int	main(void)
{
	ft_printf("%s\n", "toto");
//	ft_printf("Magic %s is %d", "number", 42);
//	ft_printf("Hexadecimal for %d is %x\n", 42, 42);

	return (0);
}
