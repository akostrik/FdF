/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:56:54 by akalimol          #+#    #+#             */
/*   Updated: 2023/07/20 21:12:05 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//mlx_loop inf loop waits for events
// Vous devez utiliser la MiniLibX. Soit la version disponible sur les machines 
// de l’école, soit en l’installant par les sources

#include "include.h"

static void	init_d1(t_data **d)
{
	(*d)->fd = -1;
	(*d)->ax = 20 * 3.14152 / 180;
	(*d)->ay = 180 * 3.14152 / 180;
	(*d)->az = 85 * 3.14152 / 180;
	(*d)->z_max = -2147483648;
	(*d)->z_min = 2147483647;
	(*d)->file_is_finished = 0;
	(*d)->mlx = NULL;
	(*d)->mlx = mlx_init();
	if ((*d)->mlx == NULL)
		exit_(d);
	(*d)->win = NULL;
	(*d)->win = mlx_new_window((*d)->mlx, W_X_MAX, W_Y_MAX, "fdf");
	if ((*d)->win == NULL)
		exit_(d);
	(*d)->img_mlx = NULL;
	(*d)->img_mlx = mlx_new_image((*d)->mlx, W_X_MAX, W_Y_MAX);
	if ((*d)->img_mlx == NULL)
		exit_(d);
	(*d)->img = NULL;
	(*d)->img = mlx_get_data_addr((*d)->img_mlx, &((*d)->bpp), \
								&((*d)->size_line), &((*d)->endian));
	if ((*d)->img == NULL)
		exit_(d);
}

static void	init_d2(t_data **d)
{
	set_y_max(d);
	set_x_max(d);
	(*d)->fd = -1;
	(*d)->fd = open((*d)->filename, O_RDONLY);
	if ((*d)->fd == -1)
		exit_(d);
	(*d)->n = NULL;
	(*d)->n = (t_node **)malloc(sizeof(t_node *) * (*d)->y_max);
	if ((*d)->n == NULL)
		exit_(d);
}

static void	init_d3(t_data **d)
{
	int		x;
	int		y;

	y = -1;
	while (++y < (*d)->y_max && (*d)->file_is_finished != 1)
	{
		(*d)->n[y] = NULL;
		(*d)->n[y] = (t_node *)malloc(sizeof(t_node) * (*d)->x_max);
		if ((*d)->n[y] == NULL)
			exit_(d);
		(*d)->line_is_finished = 0;
		x = -1;
		while (++x < (*d)->x_max)
		{
			(*d)->n[y][x].x = y - ((*d)->y_max) / 2;
			(*d)->n[y][x].y = x - ((*d)->x_max) / 2;
			(*d)->n[y][x].z = 0;
			if ((*d)->line_is_finished != 1 && (*d)->file_is_finished != 1)
				(*d)->n[y][x].z = get_next_val(d);
			(*d)->z_max = fmax((*d)->z_max, (*d)->n[y][x].z);
			(*d)->z_min = fmin((*d)->z_min, (*d)->n[y][x].z);
		}
	}
}

static void	init_d4(t_data **d)
{
	int		offset;

	close((*d)->fd);
	(*d)->z_dif = (*d)->z_max - (*d)->z_min;
	offset = W_X_MAX / 2;
	(*d)->grid_xy = W_X_MAX / 2 / fmax((*d)->x_max, (*d)->y_max);
	while ((*d)->grid_xy < 2 && offset > 120)
	{
		(*d)->grid_xy = (W_X_MAX - offset) / fmax((*d)->x_max, (*d)->y_max);
		offset = offset / 2;
	}
	offset = W_Y_MAX / 2;
	(*d)->grid_z = W_Y_MAX / 4.;
	if ((*d)->z_dif != 0)
		(*d)->grid_z /= (*d)->z_dif;
	while ((*d)->grid_z < 2 && offset > 70)
	{
		(*d)->grid_z = W_Y_MAX - offset;
		if ((*d)->z_dif != 0)
			(*d)->grid_z /= (*d)->z_dif;
		offset = offset / 2;
	}
	if ((*d)->x_max == 1 && (*d)->y_max == 1)
		(*d)->grid_z = 1;
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2)
		exit_(NULL);
	d = NULL;
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit_(&d);
	d->filename = argv[1];
	init_d1(&d);
	init_d2(&d);
	init_d3(&d);
	init_d4(&d);
	calc_image(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img_mlx, 0, 0);
	mlx_hook(d->win, DestroyNotify, 0, &exit_, &d);
	mlx_loop(d->mlx);
}
