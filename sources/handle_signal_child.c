#include "minishell.h"

static void	handle_sigint(void);
static void	child_cancel(int signal);
static void	handle_sigquit(void);



void	handle_signal_child(void)
{
	handle_sigint();
	handle_sigquit();
}

static void	handle_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = &child_cancel;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void	child_cancel(int signal)
{
	global_exit = (128 + signal);
}

static void	handle_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}
