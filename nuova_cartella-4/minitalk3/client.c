#include "minitalk.h"

static void	last_bit(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_putstr("\nKill failed\n");
		usleep(10);
	}
}

static void send_bits(int pid,int i, char c)
{
    if ((c >> i & 1) != 0)
			{
				if (kill(pid, SIGUSR1) == -1) // Fa la funzione kill ma se il ritorno è == -1 fa anche la funzione error
				{
                    ft_putstr("wrong pid\n");
	                exit(1);
                }
			}
			else
				if (kill(pid, SIGUSR2) == -1)
				{
                    ft_putstr("wrong pid\n");
	                exit(1);
                }
			usleep(50);
}

static void	send_to_server(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str;
		while (i--)
		{
            send_bits(pid, i, c);
		}
		str++;
	}
	last_bit(pid);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr("Wrong input: [pid] [string]\n");
		exit(0);
	}
	send_to_server(ft_atoi(argv[1]), argv[2]);
}