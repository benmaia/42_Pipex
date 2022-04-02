/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:28:52 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/02 16:58:54 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void e(char * s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// STDERR_FILENO = 2


//./pipex infile "ls" "cat" outfile 

void	parsing(t_p *p, int argc, char **argv)
{
	int i;
	int j;

	p->infile = open(argv[1], O_RDONLY);
	p->outfile = open(argv[argc - 1], O_RDWR);
	if (p->infile < 0 || p->outfile < 0)
	{
		printf("Ficaste aqui 2\n");
		return ;
	}
	i = 1;
	j = -1;
	p->arg = malloc(sizeof(char *) * argc);
	if (!p->arg)
	{
		printf("Ficaste aqui 3\n");
		return ;
	}	

	i = 1;
	j = -1;
	while (++i < argc)
		p->arg[++j] = ft_strdup(argv[i]);
	p->arg[j] = NULL;	
}

void	find_path(t_p *p, char **envp)
{
	int		i;
	char	*s;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH", 4))
			s = strdup(envp[i] + 5);
	if (!s)
		return ;
	
	p->cmd_path = ft_split(s, ':');
	i = -1;
}

void	cmd_path(t_p *p, int x)
{
	int		i;
	int		j;
	char	*tmp;
	char	*paths;
	
	j = -1;
	paths = p->arg[x];
	while (p->cmd_path[++j])
	{
		tmp = ft_strjoin(p->cmd_path[j], paths);
		p->arg[x] = ft_strdup(tmp);
		free (tmp);
		tmp = NULL;
		i = access(p->arg[x], F_OK);
		if (i < 0)
			continue ;
		else
			return ;
	}
	e("Error");
}

void	check_cmd(t_p *p)
{
	int		i;
	char	*tmp;

	i = -1;
	while (p->arg[++i])
	{
		if (p->arg[i][0] == '/' )
			continue ;
		else
		{
			tmp = ft_strjoin("/", p->arg[i]);
			free(p->arg[i]);
			p->arg[i] = ft_strdup(tmp);
			free (tmp);
			cmd_path(p, i);
		}
	}
}

void	debug(t_p p)
{
	printf("INFILE = %d\n", p.infile);
	printf("OUTFILE = %d\n", p.outfile);
	
	int i = 0;
	while (p.cmd_path[i] != NULL)
	{
		printf("CMD_PATH[%d] = %s\n", i, p.cmd_path[i]);
		i++;
	}

	i = 0;
	while (p.arg[i] != NULL)
	{
		printf("ARG[%d] = %s\n", i, p.arg[i]);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_p	p;

	if (argc < 5)
	{
		printf("Ficaste aqui 1\n");
		return (1);
	}
	parsing(&p, argc, argv);
	find_path(&p, envp);
	check_cmd(&p);
	debug(p);
	return (0);
}

p.pid = fork();
	if (!p.pid)
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		p.cmd_args = ft_split(argv[2 + p.here_doc + p.idx], ' ');
		p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			msg_pipe(p.cmd_args[0]);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
