/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:18:22 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/05 20:20:49 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd_path(t_p *p)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	j = -1;
	while (p->path[++j])
	{
		tmp = ft_strjoin(p->path[j], p->cmd_path);
		tmp2 = ft_strdup(tmp);
		free (tmp);
		tmp = NULL;
		i = access(tmp2, F_OK);
		if (i < 0)
			continue ;
		else
		{
			p->cmd_path = ft_strdup(tmp2);
			free (tmp2);
			return ;
		}
	}
	err(p, "Error");
}

char	*get_path_cmd(char *tmp)
{
	int		i;
	char	*s;

	i = -1;
	while (tmp[++i])
		if (tmp[i] == ' ')
			break ;
	s = ft_substr(tmp, 0, i);
	return (s);
}

void	test(t_p *p)
{
	int	i;

	i = access (p->cmd_path, F_OK);
	if (i < 0)
		err(p, "Error");
}

void	get_cmd(t_p *p, int x)
{
	char	*tmp;
	int		i;

	i = -1;
	if (p->arg[x][0] == '/')
	{
		p->cmd = ft_split(ft_strrchr(p->arg[x], '/') + 1, ' ');
		while (p->arg[x][++i])
			if (p->arg[x][i] == ' ')
				break ;
		p->cmd_path = ft_substr(p->arg[x], 0, i);
		test(p);
	}
	else
	{
		p->cmd = ft_split(p->arg[x], ' ');
		p->cmd_path = get_path_cmd(p->arg[x]);
		tmp = ft_strjoin("/", p->cmd_path);
		free(p->cmd_path);
		p->cmd_path = strdup(tmp);
		free (tmp);
		tmp = NULL;
		get_cmd_path(p);
	}
}
