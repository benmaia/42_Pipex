/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:17:25 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/08 00:34:50 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Recreates the here_doc in shell so it  */
/* writes the "pipe heredoc> ", after     */
/* that, it reads what the user inputs in */
/* a infinite loop. That loop will only   */
/* stop, when the read function receives  */
/* an input exactly equal to the limiter  */
/* while it doesn't find that it will     */
/* reset the input with ft_bzero          */

void	heredoc(char **argv, int file)
{
	char	buf[10000];
	int		i;

	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		i = read(0, buf, 10000);
		buf[--i] = '\0';
		if (ft_strlen(buf) == ft_strlen(argv[2]))
			if (!ft_strncmp(argv[2], buf, ft_strlen(argv[2])))
				break ;
		write(file, buf, ft_strlen(buf));
		ft_bzero(buf, sizeof(buf));
	}
}

/* If it appends, the here_doc flag gets   */
/* the value 1, it creates a ghost file    */
/* with the O_CREAT, and the outfile can't */
/* delete what was inside of it, that's    */
/* why it uses the O_APPEND, so it can     */
/* concatenate the new output with the old */
/* one. Then calls the heredoc function and*/
/* after that it puts the STDIN as the     */
/* ghost file it created.                  */

void	append(t_p *p, int argc, char **argv)
{
	int		file;

	if (argc < 6)
        {
                ft_putstr_fd("Arg: ./pipex  here_doc LIMITER command1 command2 outfile\n", 2);
                exit(EXIT_FAILURE);
        }
	p->here_doc = 1;
	file = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	heredoc(argv, file);
	close(file);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(1);
	}
}

/* If it redirects, the outfile should   */
/* delete whats there and writes the     */
/* new input, thats why it uses the flag */
/* O_TRUNC, if the outfile doesn't exist */
/* then one is created with the O_CREAT  */
/* and set the flag of here_doc as 0     */

void	redirect(t_p *p, int argc, char **argv)
{
	p->here_doc = 0;
	p->infile = open(argv[1], O_RDONLY);
	p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->infile < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

/* It gets the argv and does the parsing */
/* if it finds and here_doc it parses    */
/* as an append command, otherwise it    */
/* parses as a redirection, after that   */
/* it stores all the argv into arg so it */
/* can use them in other functions.      */

void	parsing(t_p *p, int argc, char **argv)
{
	int	i;
	int	j;

	if (!ft_strncmp(argv[1], "here_doc", 9))
		append(p, argc, argv);
	else
		redirect(p, argc, argv);
	p->arg = malloc(sizeof(char *) * argc);
	if (!p->arg)
		err(p, "Error");
	i = 1;
	j = -1;
	while (++i < argc)
		p->arg[++j] = ft_strdup(argv[i]);
	p->arg[++j] = 0;
}

/* It fins all the paths of the      */
/* computer where the commands could */
/* be stored.                        */

void	find_path(t_p *p, char **envp)
{
	char	*s;
	int		i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH", 4))
			s = ft_strdup(envp[i] + 5);
	if (!s)
		err(p, "Error");
	p->path = ft_split(s, ':');
	free (s);
}
