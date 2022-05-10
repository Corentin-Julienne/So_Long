/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:29:26 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 00:15:12 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	destroy_img_case_pb(t_game *game, int iter)
{
	mlx_destroy_image(game->mlx, game->img_space->id);
	mlx_destroy_image(game->mlx, game->img_wall->id);
	if (iter == 3)
		mlx_destroy_image(game->mlx, game->img_psp->id);
	if (iter == 4)
	{
		mlx_destroy_image(game->mlx, game->img_psp->id);
		mlx_destroy_image(game->mlx, game->img_coll->id);
	}
	if (iter == 5)
	{
		mlx_destroy_image(game->mlx, game->img_psp->id);
		mlx_destroy_image(game->mlx, game->img_coll->id);
		mlx_destroy_image(game->mlx, game->img_exit->id);
	}
}

static void	load_textures(t_game *game, t_img **image, char *path, int iter)
{
	int		width;
	int		height;

	(*image)->id = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!((*image)->id))
	{
		display_error_message("Failed to import img from xpm file\n");
		if (iter == 1)
		{
			mlx_destroy_image(game->mlx, game->img_space->id);
			free(game->img_space);
		}		
		else
		{
			destroy_img_case_pb(game, iter);
			free_images(game, iter);
		}
		free_split(game->map->map_arr);
		free(game->map);
		free(game);
		exit(EXIT_FAILURE);
	}
	(*image)->width = width;
	(*image)->height = height;
}

void	init_textures(t_game *game)
{	
	load_textures(game, &game->img_space, "./textures/free_space.xpm", 1);
	load_textures(game, &game->img_wall, "./textures/wall.xpm", 2);
	load_textures(game, &game->img_psp, "./textures/player.xpm", 3);
	load_textures(game, &game->img_coll, "./textures/coll.xpm", 4);
	load_textures(game, &game->img_exit, "./textures/exit.xpm", 5);
}
