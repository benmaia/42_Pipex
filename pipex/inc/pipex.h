/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:37:23 by paijavai          #+#    #+#             */
/*   Updated: 2022/04/05 00:10:22 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

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
}	t_p;

#endif