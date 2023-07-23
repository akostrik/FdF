/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:06:29 by akostrik          #+#    #+#             */
/*   Updated: 2023/07/23 16:14:09 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	exit_esc_key(int keysym, t_data **d)
{
	if (keysym == XK_Escape)
		exit_(d);
	return (0);
}

int	exit_(t_data **d)
{
	int	y;

	if (d == NULL || *d == NULL)
		exit(EXIT_FAILURE);
	if ((*d)->mlx != NULL && (*d)->win != NULL)
		mlx_destroy_window((*d)->mlx, (*d)->win);
	if ((*d)->mlx != NULL && (*d)->img_mlx != NULL)
		mlx_destroy_image((*d)->mlx, (*d)->img_mlx);
	if ((*d)->mlx != NULL)
		mlx_destroy_display((*d)->mlx);
	if ((*d)->mlx != NULL)
		free((*d)->mlx);
	if (*d != NULL && (*d)->n != NULL)
	{
		y = -1;
		while (++y < (*d)->y_max && (*d)->n[y] != NULL)
			if ((*d)->n[y] != NULL)
				free((*d)->n[y]);
		free((*d)->n);
	}
	if ((*d)->fd != -1)
		close((*d)->fd);
	free(*d);
	exit(EXIT_SUCCESS);
	return (0);
}
