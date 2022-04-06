/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:25:46 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/06 03:29:04 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_here(t_p *p)
{
	int	i;

	i = -1;
	while (p->path[++i])
		free (p->path[i]);
	free (p->path);
}

void	free_all(t_p *p)
{
	int	i;

	i = -1;
	while (p->path[++i])
		free (p->path[i]);
	free (p->path);
	i = -1;
	while (p->arg[++i])
		free (p->arg[i]);
	free (p->arg);
}

void	err(t_p *p, char *s)
{
	perror(s);
	if (p->here_doc)
		free_here(p);
	else
		free_all(p);
	exit(EXIT_FAILURE);
}

void	special_err(t_p *p, char *s)
{
	perror(s);
	free_here(p);
	exit(EXIT_FAILURE);
}

void	err_all(t_p *p, char *s)
{
	perror(s);
	free_all(p);
	exit(EXIT_FAILURE);
}
