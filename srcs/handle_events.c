/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 20:09:18 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/10 23:56:31 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	destroy_imgs(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img_space->id);
	mlx_destroy_image(game->mlx, game->img_wall->id);
	mlx_destroy_image(game->mlx, game->img_psp->id);
	mlx_destroy_image(game->mlx, game->img_coll->id);
	mlx_destroy_image(game->mlx, game->img_exit->id);
}

void	quit_game(t_game *game)
{
	destroy_imgs(game);
	free_images(game, 5);
	mlx_destroy_window(game->mlx, game->wdw);
	free_split(game->map->map_arr);
	free(game->map);
	free(game->coord);
	free(game);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game **game)
{
	if (keycode == 53)
		quit_game(*game);
	if (keycode == 13 || keycode == 1 || keycode == 2 || keycode == 0)
		move_player(*game, keycode);
	return (1);
}

int	exit_hook(t_game **game)
{
	quit_game(*game);
	return (1);
}
