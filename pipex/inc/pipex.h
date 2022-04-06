/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:37:23 by paijavai          #+#    #+#             */
/*   Updated: 2022/04/06 03:26:13 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

typedef struct s_p {
	int		infile;
	int		outfile;
	int		pipe[2];
	int		id;
	int		pipe_nbr;
	int		cmd_nbr;
	pid_t	pid;
	char	**cmd;
	char	**path;
	char	*cmd_path;
	char	**arg;
	char	*env;
	int		in;
	int		out;
	int		here_doc;
	char	*limiter;
}	t_p;

void	err(t_p *p, char *s);

void	err_all(t_p *p, char *s);

void	special_err(t_p *p, char *s);

void	free_all(t_p *p);

void	free_here(t_p *p);

void	parsing(t_p *p, int argc, char **argv);

void	find_path(t_p *p, char **envp);

void	get_cmd_path(t_p *p);

char	*get_path_cmd(char *tmp);

void	test(t_p *p);

void	get_cmd(t_p *p, int x);

void	child_work(t_p *p, int i, char **envp);

#endif