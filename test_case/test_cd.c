#include "test.h"

void	print_commond_cd(t_list *start, t_list *env)
{
	t_cmd_line *cmd;
	char	*dir;
	char	*oldpwd;
	char	*pwd;
	bool	pi;

	pi = false;
	while (start)
	{
		cmd = start->content;
		dir = getcwd(NULL, 0);
		pwd = get_env_value("PWD", env);
		oldpwd = get_env_value("OLDPWD", env);
		printf("\nbefore cd : %s\n", dir);
		printf("before cd PWD : %s\n", pwd);
		printf("before cd OLDPWD : %s\n", oldpwd);
		free(pwd);
		free(oldpwd);
		free(dir);
		if (are_equal(cmd->command, "cd"))
			if (!ft_cd(cmd, env, &pi))
				if (g_err.err_value)
					print_err_msg();
		dir = getcwd(NULL, 0);
		pwd = get_env_value("PWD", env);
		oldpwd = get_env_value("OLDPWD", env);
		printf("\nafter cd : %s\n", dir);
		printf("after cd PWD : %s\n", pwd);
		printf("after cd OLDPWD : %s\n\n", oldpwd);
		free(pwd);
		free(oldpwd);
		free(dir);
		start = start->next;
	}
	if (chdir("/home/dokang/cwork/team") < 0)
		printf("eeeeeee\n");
	set_env_target(env, "PWD", "/home/dokang/cwork/team");
	set_env_target(env, "OLDPWD", "/home/dokang/cwork");
}

// void	check_cd(t_list *start, t_list *env)
// {
// 	t_cmd_line *cmd;
// 	char	*b_dir;
// 	char	*b_oldpwd;
// 	char	*b_pwd;
// 	char	*a_dir;
// 	char	*a_oldpwd;
// 	char	*a_pwd;
// 	char	*tmp;
// 	bool	pi;

// 	pi = false;
// 	while (start)
// 	{
// 		cmd = start->content;
// 		b_dir = getcwd(NULL, 0);
// 		b_pwd = get_env_value("PWD", env);
// 		b_oldpwd = get_env_value("OLDPWD", env);
// 		if (are_equal(cmd->command, "cd"))
// 		{
// 			if (!ft_cd(cmd, env, &pi))
// 				if (g_err.err_value)
// 					print_err_msg();
// 			else
// 			{
// 				a_dir = getcwd(NULL, 0);
// 				a_pwd = get_env_value("PWD", env);
// 				a_oldpwd = get_env_value("OLDPWD", env);
// 				if (!are_equal(a_oldpwd, b_pwd))
// 					print_point(expect, result);
// 				if (!are_equal(a_pwd, a_dir))
// 					print_point();
// 				free(tmp);
// 				free(a_oldpwd);
// 				free(a_pwd);
// 				free(a_dir);
// 			}
// 		}
// 		free(b_oldpwd);
// 		free(b_pwd);
// 		free(b_dir);
// 		start = start->next;
// 	}
// 	if (chdir("/home/dokang/cwork/team") < 0)
// 		printf("eeeeeee\n");
// 	set_env_target(env, "PWD", "/home/dokang/cwork/team");
// 	set_env_target(env, "OLDPWD", "/home/dokang/cwork");
// }

void	free_list(t_list *list)
{
	t_list	*start;
	t_list	*tmp;

	start = list;
	while(start)
	{
		t_list *start2 = start;
		tmp = start->content;
		free_cmd_struct(start->content);
		start = start->next;
		free(start2);
		free(tmp);
	}
}

void	test_cd(t_list *env)
{
	t_list *cmd_lines;

	char *case1= "echo -n 1234 ; cd .."; 
	cmd_lines = get_command_lines(case1, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  Case 1 OK  ==========================\n");

	char *case2= "cd .. ; cd .."; 
	cmd_lines = get_command_lines(case2, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case2 OK  ==========================\n");

	char *case3= "cd ~/cwork > 123 ; cd .."; 
	cmd_lines = get_command_lines(case3, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case3 OK  ==========================\n");

	char *case4= "cd ~/cwork > 123 456; cd .."; 
	cmd_lines = get_command_lines(case4, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case4 OK  ==========================\n");

	char *case5= "cd - > 123 ; cd .."; 
	cmd_lines = get_command_lines(case5, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case5 OK  ==========================\n");

	char *case6= "cd ~/cwork > 123 456 | cd .."; 
	cmd_lines = get_command_lines(case6, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case6 OK  ==========================\n");

	char *case7= "cd ~/cwork > 123 | cd .."; 
	cmd_lines = get_command_lines(case7, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case7 OK  ==========================\n");

	char *case8= "cd ~/team > 123 ; cd .."; 
	cmd_lines = get_command_lines(case8, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case8 OK  ==========================\n");

	char *case9= "cd . >> 123 ; cd .."; 
	cmd_lines = get_command_lines(case9, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case9 OK  ==========================\n");

	char *case10= "cd ./team > 123 ; cd .."; 
	cmd_lines = get_command_lines(case10, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case10 OK  ==========================\n");

	char *case11= "cd . < 123 ; cd .."; 
	cmd_lines = get_command_lines(case11, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case11 OK  ==========================\n");

	char *case12= "cd . > 123 ; cd .."; 
	cmd_lines = get_command_lines(case12, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case12 OK  ==========================\n");

	char *case13= "cd . < 1234 ; cd .."; 
	cmd_lines = get_command_lines(case13, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case13 OK  ==========================\n");

	char *case14= "cd . hi > 1234 ;"; 
	cmd_lines = get_command_lines(case14, env);
	print_commond_cd(cmd_lines, env);
	free_list(cmd_lines);
	printf("====================  case14 OK  ==========================\n");
}