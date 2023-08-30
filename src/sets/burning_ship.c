/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:17:14 by jschwabe          #+#    #+#             */
/*   Updated: 2023/08/30 13:40:14 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static uint32_t	bs_calculate_color(t_args *args, double cx, double cy);

void	burning_ship(t_args *args)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		mlx_put_pixel(args->img, x, y, bs_calculate_color(args, x, y));
		x++;
		if (x == WIDTH)
		{
			x = 0;
			y++;
		}
	}
}

static uint32_t	bs_calculate_color(t_args *args, double cx, double cy)
{
	t_burning_ship	b;

	b.iterations = -1;
	b.zx = 0.0;
	b.zy = 0.0;
	cx = args->xmin + (cx * ((args->xmax - args->xmin) / WIDTH));
	cy = args->ymin + (cy * ((args->ymax - args->ymin) / HEIGHT));
	while (++b.iterations < args->max_iterations)
	{
		b.zx = fabs(b.zx);
		b.zy = fabs(b.zy);
		b.tmp = b.zx * b.zx - b.zy * b.zy + cx;
		b.zy = 2.0 * b.zx * b.zy + cy;
		b.zx = b.tmp;
		if (sqrt(b.zx * b.zx + b.zy * b.zy) > 2.0)
			break ;
	}
	return (args->color_function(b.iterations, args->max_iterations));
}
