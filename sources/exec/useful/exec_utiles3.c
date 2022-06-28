/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utiles3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:51:18 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/25 18:52:50 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

int ft_env_size(t_env *env)
{
    int i;
    i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return (i);
}