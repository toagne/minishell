/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:53:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 13:33:51 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr_and_null(char ***arr)
{
	size_t	i;

	if (arr == NULL || *arr == NULL)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_arr(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
