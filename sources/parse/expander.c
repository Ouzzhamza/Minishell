/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:01 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/01 20:54:53 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fast_strncat(char *dest, const char *src, size_t *size)
{
	size_t	src_len;

	if (dest && src)
	{
		src_len = ft_strlen(src);
		ft_memcpy(dest + *size, src, src_len + 1u);
		*size += src_len;
	}
}

void	ft_find_sub(const char *old, const char *new_, t_info *info)
{
	if (ft_strstr(info->temp, old) == info->temp)
	{
		info->x = 0;
		fast_strncat(&info->buff[info->i], new_, &info->x);
		info->i += ft_strlen(new_);
		info->temp += ft_strlen(old);
	}
	else
		info->buff[info->i++] = *info->temp++;
}

void	ft_count_old(const char *old, t_info *info)
{
	const char	*str;

	str = ft_strstr((const char *)&info->temp[info->i], old);
	if (str == &info->temp[info->i])
	{
		info->c_d++;
		info->i += ft_strlen(old) - 1;
	}
}

void	replace_sub(char **str, const char *old, const char *new_)
{
	t_info	info;

	info.temp = (const char *)(*str);
	info.c_d = 0;
	info.i = -1;
	info.t = ft_strlen(new_) - ft_strlen(old);
	while (info.temp[++(info.i)] != '\0')
		ft_count_old(old, &info);
	info.buff = ft_calloc((info.i + info.c_d * info.t + 1), sizeof(char));
	if (!info.buff)
		return ;
	info.i = 0;
	while (*info.temp)
		ft_find_sub(old, new_, &info);
	free(*str);
	*str = ft_calloc(info.i + 1, sizeof(char));
	if (!(*str))
		return ;
	info.i = 0;
	fast_strncat(*str, (const char *)info.buff, &info.i);
	free(info.buff);
}

char	*get_env1(char *env)
{
	t_env*ptr;
	ptr = g_msh.dup_envp;
	while (ptr)
	{
		if (!ft_strcmp1(env, ft_strndup(ptr->key, ft_strlen(ptr->key) - 1)))
			return(ft_strdup(ptr->value));
		ptr = ptr->next;
	}
	return (NULL);
}

void	expand_dollar(t_command *node)
{
	int		i;
	char	*sub;
	char	*env;
	int		flag;

	while (node)
	{
		flag = 0;
		i = 0;
		while (node->cmd[i])
		{
			if (is_dollar(node->cmd[i]) >= 0 && node->cmd[i][0] != '\'')
			{
				flag = 1;
				sub = dollar_substr(node->cmd[i]);
				env = dollar_substr1(node->cmd[i]);
				if (get_env1(env))
					replace_sub(&node->cmd[i], sub, get_env1(env));
				else if (!get_env1(env))
					replace_sub(&node->cmd[i], sub, "");
			}
			i++;
		}
		if (flag == 1)
		{
			free(sub);
			free(env);
		}
		node = node->next;
	}
}
