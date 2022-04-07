/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:45:32 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/07 21:37:44 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function will be called in loop   */
/* while exists commands to perform.      */
/* It runs each command one by one, if    */
/* it's the 1st command, it will change   */
/* the STDIN to the infile and the STDOUT */
/* to the pipe, is there's more then 2    */
/* commands, the middle ones will just    */
/* change the STDOUT to the pipe inside   */
/* the child and change the STDIN to the  */
/* pipe in the parrent. If it's the last  */
/* command, it will change the STDOUT to  */
/* the outfile in the child, and again    */
/* changes the STDIN to the pipe in the   */
/* the parent. After the that it will     */
/* get the command, and after execute it  */
/* The wait functions is there so the     */
/* parent executes the rest of the        */
/* commands only after the child process  */
/* is finished and closed.*/

void	child_work(t_p *p, int i, char **envp)
{
	if (pipe(p->pipe) == -1)
		err(p, "Error");
	p->pid = fork();
	if (p->pid < 0)
		err(p, "Error");
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

/* 1st thing it will check if the number */
/* of args is correct, if not it will    */
/* give error and show how to use it.    */
/* Then it will do the parsing of the    */
/* arguments, it will find all the paths */
/* of the pc. */
/* Then it will run the command 1 by 1 . */
/* After that if there is an here_doc    */
/* it will delete it after using it.     */
/* And to finished it free everything to */
/* be free os memory leaks!              */

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
	if (p.here_doc)
		unlink(".heredoc_tmp");
	free_all(&p);
	return (0);
}
