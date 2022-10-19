#include "minitalk.h"

static void	response(unsigned int *c_pid)
{
	kill(*c_pid, SIGUSR1);
	*c_pid = 0;
}

static void	handler_s(int sig, siginfo_t *siginfo, void *optional)
{
	static unsigned char	c;
	static int				i;
	static unsigned int		c_pid;

	(void)optional;
	c_pid = siginfo->si_pid; //pid del client
	c = c | (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (!c)
			return (response(&c_pid)); //manda il segnale al pid del client
		ft_putchar(c);
		c = 0;
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Mandatory!\n");
	ft_putstr("PID : ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	sa.sa_sigaction = handler_s;  // handler definisce il comportamento del segnale modificato in sigaction().
	sa.sa_flags = SA_SIGINFO;	  // sa_flags ottiene tutte le proprietà del segnale ottenute da sig_info che da un "int" che fa da collegamento agli argomenti di sig_info.
	if (sigaction(SIGUSR1, &sa, 0) == -1) // sigaction cambia l'azione di un proccesso di uno specifico segnale modificato nell'handler. 
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}