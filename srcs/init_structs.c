/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:50:22 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/10 23:15:47 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* this func init the game struct used to store imgs
and various parameters */

void	init_game_struct(t_game *game, t_map_parse *map)
{	
	game->img_space = (t_img *)malloc(sizeof(t_img));
	game->img_wall = (t_img *)malloc(sizeof(t_img));
	game->img_psp = (t_img *)malloc(sizeof(t_img));
	game->img_coll = (t_img *)malloc(sizeof(t_img));
	game->img_exit = (t_img *)malloc(sizeof(t_img));
	if (!game->img_wall)
		free(game->img_space);
	if (!game->img_psp)
		free_images(game, 2);
	if (!game->img_coll)
		free_images(game, 3);
	if (!game->img_exit)
		free_images(game, 4);
	if (!game->img_space || !game->img_wall || !game->img_psp
		|| !game->img_coll || !game->img_exit)
	{
		display_error_message("Malloc failed in game struct\n");
		free_split(map->map_arr);
		free(map);
		free(game);
		exit(EXIT_FAILURE);
	}
	game->total_moves = 0;
	game->nb_coll = map->nb_coll;
	game->map = map;
}

/* init the map structs with all infos about the num of 
coll, player starting position, exit, and will be used
to check to error during map parsing */

void	init_map_struct(t_map_parse *map)
{
	map->nb_coll = 0;
	map->nb_psp = 0;
	map->nb_exit = 0;
	map->nb_inv_char = 0;
	map->len_line = 0;
	map->nb_rect_error = 0;
	map->nb_err_walls = 0;
	map->ber_format = 1;
}

/* are coord of the player within the map */

void	init_coord_struct(t_game *game, t_pl_coord *coord)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->map_arr[j])
	{
		while (game->map->map_arr[j][i])
		{
			if (game->map->map_arr[j][i] == 'P')
			{
				coord->i = i;
				coord->j = j;
			}
			i++;
		}
		i = 0;
		j++;
	}
	game->coord = coord;
}
