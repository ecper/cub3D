#include <cub3d.h>

void	print_error(char *msg)
{	
	const char	*red = "\033[31m";
	const char	*reset = "\033[0m";

	write(2, red, 5);
	ft_putendl_fd(msg, 1);
	write(2, reset, 4);
	exit(1);
}
