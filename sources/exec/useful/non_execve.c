/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:02:23 by houazzan          #+#    #+#             */
/*   Updated: 2023/12/13 20:48:38 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	run_builtins(void)
{
	
	if (g_msh.cmd->cmd_type == CD)
		cd();
	else if (g_msh.cmd->cmd_type == ECHO)
		g_msh.exit_status = echo();
	else if (g_msh.cmd->cmd_type == PWD)
		g_msh.exit_status = pwd();
	else if (g_msh.cmd->cmd_type == ENV)
		g_msh.exit_status = env(0);
	else if (g_msh.cmd->cmd_type == EXPORT)
		export();
	else if (g_msh.cmd->cmd_type == UNSET)
		unset();
	else if (g_msh.cmd->cmd_type == EXIT)
		exiting();
}
