/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:17:25 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/06 03:14:46 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc(char **argv, char *buf, int file)
{
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		read(0, buf, 10000);
		if (!ft_strncmp(argv[2], buf, ft_strlen(argv[2])))
			break ;
		write(file, buf, ft_strlen(buf));
	}
}

void	append(t_p *p, int argc, char **argv)
{
	int		file;
	char	buf[10000];

	p->here_doc = 1;
	file = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	heredoc(argv, buf, file);
	close(file);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(1);
	}
}

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
	i = 1 + p->here_doc;
	j = -1;
	while (++i < argc)
		p->arg[++j] = ft_strdup(argv[i]);
}

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
