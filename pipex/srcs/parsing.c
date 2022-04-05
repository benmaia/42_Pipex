/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:17:25 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/05 20:21:24 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parsing(t_p *p, int argc, char **argv)
{
	int	i;
	int	j;

	p->infile = open(argv[1], O_RDONLY);
	p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->infile < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	p->arg = malloc(sizeof(char *) * argc);
	if (!p->arg)
		err(p, "Error");
	i = 1;
	j = -1;
	while (++i < argc)
		p->arg[++j] = ft_strdup(argv[i]);
	p->arg[j] = NULL;
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
