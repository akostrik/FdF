/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:05:03 by akostrik          #+#    #+#             */
/*   Updated: 2023/07/20 21:09:46 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# define W_X_MAX 810
# define W_Y_MAX 540

typedef struct s_node
{
	int	x;
	int	y;
	int	z;
	int	xp;
	int	yp;
	int	col;
}	t_node;

typedef struct s_lst
{
	char			*line;
	struct s_lst	*nxt;
}	t_lst;

typedef struct s_data
{
	t_node		**n;
	void		*mlx;
	void		*win;
	void		*img_mlx;
	char		*img;
	int			x_max;
	int			y_max;
	int			z_min;
	int			z_max;
	int			z_dif;
	float		ax;
	float		ay;
	float		az;
	int			grid_xy;
	int			grid_z;
	int			bpp;
	int			size_line;
	int			endian;
	int			fd;
	char		*filename;
	int			line_is_finished;
	int			file_is_finished;
}	t_data;

void	set_x_max(t_data **d);
void	set_y_max(t_data **d);
int		get_next_val(t_data **d);
void	calc_image(t_data *d);
int		exit_(t_data **d);

#endif