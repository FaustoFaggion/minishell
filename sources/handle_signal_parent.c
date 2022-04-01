#include "minishell.h"

static void	handle_sigint(void);
static void	handle_sigquit(void);
void	update_global_exit(int signal);

void	handle_signal_parent(void)
{
	handle_sigint();
	handle_sigquit();
}

static void	handle_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = &update_global_exit;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = &update_global_exit;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	update_global_exit(int signal)
{
	global_exit = (128 + signal);
	if (signal == SIGQUIT)
		write(1, "Quit", 5);
	write(1, "\n", 1);
}