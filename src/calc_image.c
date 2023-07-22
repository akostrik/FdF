/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:04:43 by akostrik          #+#    #+#             */
/*   Updated: 2023/07/20 21:11:00 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	calc_pixel(t_data *d, t_node p, t_node p1, t_node p2)
{
	int	col;

	if (p.xp < 0 || p.xp > W_X_MAX || p.yp < 0 || p.yp > W_Y_MAX)
		return ;
	if (p1.xp == p2.xp && p1.yp == p2.yp)
		col = p1.col;
	else if (p1.xp == p2.xp && p1.yp != p2.yp)
		col = (p2.col - p1.col) * (p.yp - p1.yp) / (p2.yp - p1.yp) + p1.col;
	else
		col = (p2.col - p1.col) * (p.xp - p1.xp) / (p2.xp - p1.xp) + p1.col;
	*((int *)(d->img + p.yp * d->size_line + p.xp * 4)) = \
		((col >> 16) & 0xFF) * 65536 + ((col >> 8) & 0xFF) * 256 + (col & 0xFF);
}

static int	calc_ending_point_color(t_data *d, t_node p)
{
	int	ratio;

	if (d->z_dif == 0)
		return (255 * 256 * 256);
	ratio = 255. * 2 * (p.z - d->z_min) / d->z_dif;
	if (ratio >= 255)
		return (255 * 256 * 256 + 255 * 256 + ratio / 2);
	return (255 * 256 * 256 + ratio * 256 + 0);
}

static void	calc_line_bresenhams(t_data *d, t_node p1, t_node p2)
{
	t_node	p;
	int		err;
	int		e;

	p.xp = p1.xp;
	p.yp = p1.yp;
	p1.col = calc_ending_point_color(d, p1);
	p2.col = calc_ending_point_color(d, p2);
	err = abs(p2.xp - p1.xp) - abs(p2.yp - p1.yp);
	while (p.xp != p2.xp || p.yp != p2.yp)
	{
		calc_pixel(d, p, p1, p2);
		e = 2 * err;
		if (e > -1 * abs(p2.yp - p1.yp))
		{
			err -= abs(p2.yp - p1.yp);
			p.xp += (p1.xp < p2.xp) * 2 - 1;
		}
		if (e < abs(p2.xp - p1.xp))
		{
			err += abs(p2.xp - p1.xp);
			p.yp += (p1.yp < p2.yp) * 2 - 1;
		}
	}
	calc_pixel(d, p, p1, p2);
}

static void	calc_projection(t_data *d)
{
	int	y;
	int	x;
	int	xx;
	int	yy;
	int	zz;

	y = -1;
	while (++y < d->y_max)
	{
		x = -1;
		while (++x < d->x_max)
		{
			xx = d->n[y][x].x * d->grid_xy;
			yy = d->n[y][x].y * d->grid_xy;
			zz = d->n[y][x].z * d->grid_z;
			d->n[y][x].xp = W_X_MAX / 2 + xx * cos(d->az) * cos(d->ay);
			d->n[y][x].xp -= zz * sin(d->ay) + yy * sin(d->az) * cos(d->ay);
			d->n[y][x].yp = W_Y_MAX / 2 + xx * sin(d->az) * cos(d->ax) + \
			yy * cos(d->az) * cos(d->ax) + zz * cos(d->ay) * sin(d->ax) + \
			xx * cos(d->az) * sin(d->ay) * sin(d->ax) - \
			yy * sin(d->az) * sin(d->ay) * sin(d->ax);
		}
	}
}

void	calc_image(t_data *d)
{
	int	y;
	int	x;

	calc_projection(d);
	if (d->x_max == 1 && d->y_max == 1)
	{
		d->n[0][0].col = calc_ending_point_color(d, d->n[0][0]);
		calc_pixel(d, d->n[0][0], d->n[0][0], d->n[0][0]);
		return ;
	}
	y = -1;
	while (++y < d->y_max)
	{
		x = -1;
		while (++x < d->x_max - 1)
			calc_line_bresenhams(d, d->n[y][x], d->n[y][x + 1]);
	}
	y = -1;
	while (++y < d->y_max - 1)
	{
		x = -1;
		while (++x < d->x_max)
			calc_line_bresenhams(d, d->n[y][x], d->n[y + 1][x]);
	}
}
