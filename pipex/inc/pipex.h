/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:37:23 by paijavai          #+#    #+#             */
/*   Updated: 2022/03/28 17:19:11 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_p{
	int		infile;
	int		outfile;
	int		*pipe;
	int		id;
	int		nbr;
	int		cmd_nbr;
	pid_t	pid;
	char	*cmd;
	char	**cmd_path; //path
	char	**arg; //comandos
	char	*env;
}	t_p;

#endif