#include "test.h"

int main(int argc, char **argv, char *envp[])
{
	if (argc != 1)
		return (0);
	argv[1] = 0;
	g_env = get_env_llist(envp);
	// test_get_command_line(env);
	// test_cd(env);
	//  test_command_lines(env);
	// test_redirection(env);
	test_validate_line();
	test_export();
	test_env();
	test_unset();
	// char *str;
	// str = "n\  d\n\0";
	// write(1, str, 5);
	// char *line;
	// line = 0;
	// get_next_line(0, &line);
	// write(1, line, ft_strlen(line));
	// free(line);
	ft_lstclear(&g_env, free);

	return (0);
}

/*
echo
echo (space)
echo 123
echo 123 > 123
echo 123 > 123 444
echo 123 > 123 > 456
echo 123 > 123 456 > 456
echo '123 > 123 456'
> 002 echo 123
echo 123 > ../123
echo 123 > ~/123
echo 123 > ./001
echo 123 >> 123
echo 123 < 123
echo -n 123
en ; echo 123; en; echo 45
echo 123 | echo 456
echo 123 ; echo 456
echo 123 > 789 | echo 456
echo 123 >> 789 | echo 456
echo ~
echo ~/do
echo ~-/k	(oldpwd가 있을때 / 없을때)
echo ~+/k	(pwd가 있을때 / 없을때)
echo '$a "$a" $a'
echo "$a '$a' $a"
echo $a
echo '$a'
echo "$a"
*/


/*
cd
cd (space)
cd ~
cd ~/cwork
cd -
cd --
cd ~+/command
cd ~-/mini 
cd - > 123
cd ..
cd ../..
*/


/*		
/*

123 파일에 123\n1333\1344

grep 13 < 123 | grep 4
grep 13 < 123 > 003 | grep 4
*/

/*
./minishell
~/cwork/mini/minishell
./			$?
../			$?
./command
../mini
/usr/bin/ls
ls

ctrl c
ctrl d
ctrl \
$?
*/