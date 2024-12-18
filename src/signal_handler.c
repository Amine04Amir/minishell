#include "minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;

    if (g_mini.sig_flag == 0)
    {    
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        write(1, "\nminishell$ ", 12);
    }
    else
        write(1, "\n", 1);

}

void signal_handler(int sig)
{
    if (sig == IN_CHILD)
    {    
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

    }
    else if (sig == IN_PROMPT)
    {
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, SIG_IGN);
    }
   /* else if (sig == IN_HEREDOC)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
    }*/
}

