/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:03:25 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 00:08:57 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* init_window calculate the width and heigth of the map 
base on the map and the x and y of the imgs */

static void	init_window(t_game *game)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	y = 0;
	while (game->map->map_arr[i])
	{
		y += game->img_space->height;
		i++;
	}
	game->wdw_y = y;
	i = 0;
	while (game->map->map_arr[0][i])
	{
		x += game->img_space->width;
		i++;
	}
	game->wdw_x = x;
	game->wdw = mlx_new_window(game->mlx, x, y, "so_long");
	display_map(game, x, y);
}

static void	populate_game(t_game *game)
{
	t_pl_coord		*coord;

	init_window(game);
	coord = (t_pl_coord *)malloc(sizeof(t_pl_coord));
	if (!coord)
	{
		destroy_imgs(game);
		free_images(game, 5);
		free_split(game->map->map_arr);
		free(game->map);
		free(game);
		display_error_message("Malloc error (allocation of t_player_coord)\n");
		exit(EXIT_FAILURE);
	}
	init_coord_struct(game, coord);
	mlx_hook(game->wdw, 17, 0, exit_hook, &game);
	mlx_key_hook(game->wdw, key_hook, &game);
	mlx_loop(game->mlx);
}

void	init_game(t_map_parse *map)
{
	t_game			*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
	{
		free_split(map->map_arr);
		free(map);
		display_error_message("Malloc error (alloc of t_game_struct)\n");
		exit(EXIT_FAILURE);
	}
	init_game_struct(game, map);
	game->mlx = mlx_init();
	init_textures(game);
	populate_game(game);
}
