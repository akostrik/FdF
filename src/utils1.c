/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:04:33 by akostrik          #+#    #+#             */
/*   Updated: 2023/07/23 16:06:25 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	len_next_line(t_data **d)
{
	ssize_t	nb_bts;
	char	c;
	int		len_line;

	len_line = 0;
	c = ' ';
	nb_bts = read((*d)->fd, &c, 1);
	if (nb_bts <= 0 || c == '\n')
		return (0);
	while (1)
	{
		while (nb_bts > 0 && c != '\n' && c != ' ')
			nb_bts = read((*d)->fd, &c, 1);
		len_line++;
		if (nb_bts <= 0 || c == '\n')
			break ;
		while (nb_bts > 0 && c == ' ')
			nb_bts = read((*d)->fd, &c, 1);
		if (nb_bts <= 0 || c == '\n')
			break ;
	}
	return (len_line);
}

int	get_next_val(t_data **d)
{
	ssize_t	nb_bts;
	char	s[10];
	int		i;
	char	c;

	i = -1;
	while (++i < 10)
		s[i] = '\0';
	nb_bts = read((*d)->fd, &s[0], 1);
	i = 0;
	while (1)
	{
		nb_bts = read((*d)->fd, &c, 1);
		if (nb_bts <= 0 || c == '\n' || c == ' ' || c == ',')
			break ;
		s[++i] = c;
	}
	if (c == ',')
		while (nb_bts > 0 && c != '\n' && c != ' ')
			nb_bts = read((*d)->fd, &c, 1);
	(*d)->line_is_finished = (c == '\n');
	(*d)->file_is_finished = (nb_bts <= 0);
	return (ft_atoi(s));
}

void	set_x_max(t_data **d)
{
	int	len_line;

	(*d)->fd = -1;
	(*d)->fd = open((*d)->filename, O_RDONLY);
	if ((*d)->fd == -1)
		exit_(d);
	(*d)->x_max = 0;
	while (1)
	{
		len_line = len_next_line(d);
		if (len_line == 0)
			break ;
		if ((*d)->x_max < len_line)
			(*d)->x_max = len_line;
	}
	close((*d)->fd);
}

void	set_y_max(t_data **d)
{
	ssize_t	nb_bts;
	char	c;

	(*d)->fd = -1;
	(*d)->fd = open((*d)->filename, O_RDONLY);
	if ((*d)->fd == -1)
		exit_(d);
	(*d)->y_max = 1;
	while (1)
	{
		while (1)
		{
			nb_bts = read((*d)->fd, &c, 1);
			if (nb_bts <= 0 || c == '\n')
				break ;
		}
		if (nb_bts <= 0)
			break ;
		nb_bts = read((*d)->fd, &c, 1);
		if (nb_bts <= 0)
			break ;
		((*d)->y_max)++;
	}
	close((*d)->fd);
}
