/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:48:29 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:29 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# define ORANGE "\001\033[38;5;208m\002"
# define DEFAULT "\001\033[0m\002"
# define HEREDOC 42

extern int				g_sigflag;

typedef struct s_garbage
{
	void				*line;
	struct s_garbage	*next;
}			t_garbage;

typedef struct s_simplecmd
{
	char	*path;
	char	**args;
}			t_simplecmd;

typedef struct s_cmd
{
	t_simplecmd		*scmd;
	char			**in;
	char			**out;
	int				fd[255];
	int				here_doc;
	int				pos;
}					t_cmd;

typedef struct s_shell
{
	t_garbage	*garbage;
	t_cmd		*cmd;
	char		*line;
	char		**path;
	char		**env;
	char		**cmdtab;
	int			flag;
	int			exit_status;
	int			here_flag;
}				t_shell;

typedef struct s_lexer
{
	int		flag;
	int		cmd_count;
}			t_lexer;

typedef struct s_index
{
	int		i;
	int		j;
	int		k;
	int		x;
	int		flag;
	char	*var;
	pid_t	*pid;
	int		**fd;
}			t_index;

typedef struct s_echo
{
	int		i;
	int		j;
	int		k;
	int		flag;
	char	apex;
	char	*res;
}			t_echo;

typedef struct s_filefd
{
	int	in;
	int	out;
}		t_filefd;

typedef struct s_str
{
	char	*str1;
	char	*str2;
	int		i;
}			t_str;

size_t				ft_name(char *str);
t_list				**garbage_collector(void);
t_list				*ft_lstnew(void *line);
int					pwd(void);
int					*n_doc(void);
int					*exit_status(void);
int					matlen(char **mat);
int					my_isalnum(char *c);
int					init_len(char *str);
int					check_char(char *str);
int					ft_apexlen(char *str);
int					check_apex(char args);
int					is_digit_2(char *str);
int					ft_tablen(char **tab);
int					print_exit_error(int f);
int					get_len(char *str, int i);
int					my_getenv(t_shell *shell);
int					minusn_finder(char *args);
int					ft_strcmp(char *s1, char *s2);
int					ft_idchar(char *args, char c);
int					exit_handler(char *str, int f);
int					print_env(char **envp, int fd);
int					is_digit_3(char *str, int flag);
int					update_flag_pipex(t_shell *shell);
int					is_a_really_valid_line(char *line);
int					is_valid_line(char *line, int flag);
int					check_infile_outfile(t_shell *shell);
int					check_fd(t_shell *shell, int i, int fd);
int					check_path(t_shell *shell, int i, int j);
int					copy_append(t_shell *shell, int i, int *j);
int					copy_infile(t_shell *shell, int i, int *j);
int					copy_outfile(t_shell *shell, int i, int *j);
int					copy_heredoc(t_shell *shell, int i, int *j);
int					command_not_found(t_shell *shell, char *str);
int					check_builtin2(t_shell *shell, int i, int j);
int					ft_print(t_shell *shell, char *str, int quit);
int					unset(t_shell *shell, char *args, char **envp);
int					check_builtin1(t_shell *shell, int i, int j, int fd);
int					create_heredoc(char *limiter, int *n_doc,
						t_shell *shell, int i);
int					create_heredoc_parent(int pid, int *status, int fd);
char				*apex_trim(char *str);
char				**get_env(char **env);
char				**copy_pwd(char **env);
char				**env_copy(char **envp);
char				*my_strdup(const char *s);
char				*ft_var_update(char *args, int *j);
char				**alt_split(char const *s, char c);
char				**ft_tabdup(char **tab, char **new);
char				*ft_substitute(char *str1, char *str2);
char				*ft_readline(char *str, t_shell *shell);
char				*valid_command(char **command, char **env);
char				*expand_varline(char *line, t_shell *shell);
char				*ft_substitute_error(char *str1, char *str2);
char				*copy_redirect(t_shell *shell, int i, int j);
char				*ft_check_var(char *str, int i, t_shell *shell);
char				*ft_strncpy(char *dest, const char *src, int n);
char				**export(t_shell *shell, char *str, char **envp);
char				*readline_heredoc(char *str, t_shell *shell, int fd);
void				ctrl_c(int sig);
void				ctrl_d(int sig);
void				ft_exit(int id);
void				free_heredoc(void);
void				ctrl_bslash(int sig);
void				ft_putstr(char *str);
void				lexer(t_shell *shell);
void				ctrl_heredoc(int sig);
void				ctrl_executor(int sig);
void				check_exit(t_shell *shell);
void				env_null(int i, char **envp);
void				close_fd(int **fd, int n_cmd);
void				sighandle_command(int signal);
void				apex_reset(char *apex, int *i);
void				executor(t_shell *shell, int i);
void				garbage_collector_free(int flag);
void				ft_cd(t_shell *shell, char *args);
void				minusn_check(char **args, int *j);
void				heredoc_signal_exit(int fd, int id);
void				check_here_flag(t_shell *shell, int i);
void				expand_var(char **cmd, t_shell *shell);
void				check_num(t_shell *shell, int i, int j);
void				check_space(t_shell *shell, int *j, int i);
void				ft_error(t_shell *shell, int id, int flag);
void				add_env(char *str, char **envp, int i, int *j);
void				get_doc(char *limiter, int fd, t_shell *shell);
void				*update_var(char *str, char **tmp, char **envp);
void				*upgrade_var(char *str, char **tmp, char **envp);
void				ft_quit(t_shell *shell, int exit_status, int flag);
void				ft_echo(char **args, t_shell *shell, int flag, int fd);
void				get_builtin(t_shell *shell, int i, int fd_out, int **fd);
void				redirect_fd(t_shell *shell, int *fd_in, int *fd_out, int i);
long long			ft_atol(char *str);
unsigned char		wait_and_free(pid_t *pid, int i);

#endif