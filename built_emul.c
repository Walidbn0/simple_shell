#include "shell.h"

/**
 * _myext - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myext(info_t *info)
{
        int exitcheck;

        if (info->argv[1])
        {
                exitcheck = _erratoi(info->argv[1]);
                if (exitcheck == -1)
                {
                        info->status = 2;
                        print_error(info, "Illegal number: ");
                        _eputs(info->argv[1]);
                        _eputchar('\n');
                        return (1);
                }
                info->err_num = _erratoi(info->argv[1]);
                return (-2);
        }
        info->err_num = -1;
        return (-2);
}

/**
 * _mychdir - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mychdir(info_t *info)
{
        char *s, *dirt, buffer[1024];
        int chdir_ret;

        s = getcwd(buffer, 1024);
        if (!s)
                _puts("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1])
        {
                dirt = _getenvir(info, "HOME=");
                if (!dirt)
                        chdir_ret =
                                chdir((dirt = _getenvir(info, "PWD=")) ? dirt : "/");
                else
                        chdir_ret = chdir(dirt);
        }
        else if (ft_strcmp(info->argv[1], "-") == 0)
        {
                if (!_getenvir(info, "OLDPWD="))
                {
                        _puts(s);
                        _putchar('\n');
                        return (1);
                }
                _puts(_getenvir(info, "OLDPWD=")), _putchar('\n');
                chdir_ret =
			 chdir((dirt = _getenvir(info, "OLDPWD=")) ? dirt : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenvir(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
