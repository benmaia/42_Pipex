/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:45:32 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/06 18:49:01 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_here(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	child_work(t_p *p, int i, char **envp)
{
	if (pipe(p->pipe) == -1)
		err(p, "Error");
	p->pid = fork();
	if (!p->pid)
	{
		close (p->pipe[0]);
		if (p->id == 0)
		{
			dup2 (p->infile, STDIN_FILENO);
			dup2 (p->pipe[1], STDOUT_FILENO);
		}
		else if (p->id == p->cmd_nbr - 1)
			dup2 (p->outfile, STDOUT_FILENO);
		else
			dup2 (p->pipe[1], STDOUT_FILENO);
		get_cmd(p, i);
		execve(p->cmd_path, p->cmd, envp);
	}
	close (p->pipe[1]);
	wait(NULL);
	dup2 (p->pipe[0], STDIN_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_p	p;

	if (argc < 5)
	{
		ft_putstr_fd("Arg: ./pipex infile command1 command2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
	parsing(&p, argc, argv);
	p.cmd_nbr = argc - 3 - p.here_doc;
	find_path(&p, envp);
	p.id = -1;
	while (++p.id < p.cmd_nbr)
		child_work(&p, p.id + p.here_doc, envp);
	free_all(&p);
	return (0);
}
