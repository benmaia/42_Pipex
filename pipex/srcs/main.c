/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiguel- <bmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:45:32 by bmiguel-          #+#    #+#             */
/*   Updated: 2022/03/30 16:01:53 by bmiguel-         ###   ########.fr       */
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


//./pipex infile "ls -l" "wc -l" outfile 

void debug(t_p p)
{
	printf("INFILE = %d\n", p.infile);
	printf("OUTFILE = %d\n", p.outfile);
	int i = -1;
	while (p.arg[++i] != NULL)
		printf("ARG[%d] = %s\n", i, p.arg[i]);
	i = -1;
	while (p.path[++i] != NULL)
		printf("PATH[%d] = %s\n", i, p.path[i]);
	i = -1;
	// while (p.cmd_path[++i])
	// 	printf("CMD_PATH[%d] = %s\n", i, p.cmd_path[i]);
}

void parsing(t_p *p, int argc, char **argv)
{
	int	i;
	int	j;

	p->infile = open(argv[1], O_RDONLY);
	p->outfile = open(argv[argc - 1], O_WRONLY, O_CREAT, O_TRUNC, 0644);
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
		if (!strncmp(envp[i], "PATH", 4))
			s = strdup(envp[i] + 5);
	if (!s)
		e("Error");
	p->path = ft_split(s, ':');
}

void get_cmd_path(t_p *p)
{
	char	*tmp;
	//char	*path;
	int		i;
	int		j;

	j = -1;
	while (p->path[++j])
	{
		tmp = ft_strjoin(p->path[j], p->cmd_path[0]);
		p->cmd_path[0] = ft_strdup(tmp);
		free (tmp);
		tmp = NULL;
		i = access(p->cmd_path[0], F_OK);
		if (i < 0)
			continue ;
		else
			return ;
	}
	e("Error");
}

void get_cmd(t_p *p)
{
	char	*tmp;
	int		i;

	i = 0;
	p->cmd_path = ft_split(p->arg[i], ' ');
	i = -1;
	if (p->arg[++i])
	{
		if (p->arg[i][0] == '/')
			return ;
		else
		{
			tmp = ft_strjoin("/", p->cmd_path[0]);
			free(p->cmd_path[0]);
			p->cmd_path[0] = strdup(tmp);
			free (tmp);
			//get_cmd_path(p);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	t_p	p;

	(void)p;
	(void)argv;
	(void)envp;
	p.cmd_nbr = argc - 3;
	if (argc < 5)
		e("Error");
	parsing(&p, argc, argv);
	find_path(&p, envp);
	get_cmd(&p);
	debug(p);
	int i;
	i = access("/bin/ls", F_OK);
	if (i < 0)
		e("Tentaste");
	p.pid = fork();
	char **s;

	s = ft_split(*p.arg, ' ');
	printf("s = %s\n", s[0]);
	printf("s = %s\n", s[1]);
	if (p.pid == 0)
		execve("/bin/ls", p.arg, envp);
	return (0);
}
