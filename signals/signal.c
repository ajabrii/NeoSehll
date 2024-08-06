
#include "../Header/headers.h"

void	sigint_handler(int num)
{
	(void)num;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
}

void	ft_init_signals(void)
{
	signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
}
