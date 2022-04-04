/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:45:32 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/04/05 00:09:55 by bmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int e(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
	return (1);
}

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// STDERR_FILENO = 2
// test.txt = 3
// test2.txt = 4





//./pipex infile "ls -l" "wc -l" outfile 

void debug(t_p p)
{
	//int i;
	
	printf("INFILE = %d\n", p.infile);
	printf("OUTFILE = %d\n", p.outfile);
	//printf("PIPE = %d\n", p.pipe);
	// printf("ID = %d\n", p.id);
	// printf("PIPE_NBR = %d\n", p.pipe_nbr);
	// printf("CMD_NBR = %d\n", p.cmd_nbr);
	// printf("PID = %d\n", p.pid);
	// i = -1;
	// while (p.cmd[++i])
	// 	printf("CMD[%d] = %s\n", i, p.cmd[i]);
	// i = -1;
	// while (p.path[++i] != NULL)
	// 	printf("PATH[%d] = %s\n", i, p.path[i]);
	// printf("CMD_PATH = %s\n", p.cmd_path);
	// i = -1;
	// while (p.arg[++i] != NULL)
	// 	printf("ARG[%d] = %s\n", i, p.arg[i]);
}

void parsing(t_p *p, int argc, char **argv)
{
	int	i;
	int	j;

	p->infile = open(argv[1], O_RDONLY);
	p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->infile < 0 || p->outfile < 0)
		e("Error");
	p->arg = malloc(sizeof(char *) * argc);
	if (!p->arg)
		e("Error");
	i = 1;
	j = -1;
	while (++i < argc)
		p->arg[++j] = ft_strdup(argv[i]);
	p->arg[j] = NULL;
}

void find_path(t_p *p, char **envp)
{
	char	*s;
	int		i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH", 4))
			s = ft_strdup(envp[i] + 5);
	if (!s)
		e("Error");
	p->path = ft_split(s, ':');
	free (s);
}

void get_cmd_path(t_p *p)
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
	e("Error");
}

static char	*get_path_cmd(char *tmp)
{
	int		i;
	char	*s;

	i = -1;
	while (tmp[++i])
		if (tmp[i] == ' ')
			break;
	s = ft_substr(tmp, 0, i);
	return (s);
}

void get_cmd(t_p *p, int x)
{
	char	*tmp;
	int		i;

	i = 0;
	p->cmd = ft_split(p->arg[x], ' ');
	p->cmd_path = get_path_cmd(p->arg[x]);
	i = -1;
	if (p->arg[++i])
	{
		if (p->arg[i][0] == '/')
		{
			free (p->cmd_path);
			p->cmd_path = ft_strdup(p->arg[i]);
		}
		else
		{
			tmp = ft_strjoin("/", p->cmd_path);
			free(p->cmd_path);
			p->cmd_path = strdup(tmp);
			free (tmp);
			tmp = NULL;
			get_cmd_path(p);
		}
	}
}

void	child_work(t_p *p, int i, char **envp)
{
	if (pipe(p->pipe) == -1)
		e("Error");
	p->pid = fork();
	if (!p->pid)
	{
		close (p->pipe[0]);
		if (p->id == 0)
		{
			dup2 (p->infile, STDIN_FILENO);
			dup2 (p->pipe[1], STDOUT_FILENO);
		}
		else if (p->id == p->cmd_nbr - 1)
		{
			dup2 (p->outfile, STDOUT_FILENO);
		}
		else
			dup2 (p->pipe[1], STDOUT_FILENO);
		get_cmd(p, i);
		execve(p->cmd_path, p->cmd, envp);
	}
	close (p->pipe[1]);
	wait(NULL);
	dup2 (p->pipe[0], STDIN_FILENO);
}

int main(int argc, char **argv, char **envp)
{
	t_p	p;

	if (argc < 5)
		e("Error");
	p.cmd_nbr = argc - 3;
	parsing(&p, argc, argv);
	find_path(&p, envp);
	p.id = -1;
	while (++p.id < p.cmd_nbr)
			child_work(&p, p.id, envp);
	//debug(p);
	return (0);
}
