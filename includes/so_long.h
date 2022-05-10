/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:28:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 00:05:10 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_img
{
	void			*id;
	int				width;
	int				height;
}					t_img;

typedef struct s_pl_coord
{
	int				i;
	int				j;
}					t_pl_coord;

typedef struct s_map_parse
{
	int				nb_coll;
	int				nb_psp;
	int				nb_exit;
	int				nb_inv_char;
	int				len_line;
	int				nb_rect_error;
	int				nb_err_walls;
	int				ber_format;
	char			*lines;
	char			**map_arr;
}					t_map_parse;

typedef struct s_game
{
	void			*mlx;
	void			*wdw;
	int				wdw_x;
	int				wdw_y;
	t_img			*img_space;
	t_img			*img_wall;
	t_img			*img_coll;
	t_img			*img_exit;
	t_img			*img_psp;
	t_pl_coord		*coord;
	t_map_parse		*map;
	int				total_moves;
	int				nb_coll;
}					t_game;

/* check map_validity 1 and 2 */

int		check_map_validity(char **argv, t_map_parse *map);
void	count_items(t_map_parse *map);
void	is_format_ber(char **argv, t_map_parse *map, int fd);
void	check_errors(t_map_parse *map);
void	map_error_messages(int error_type);

/* display map */

void	display_map(t_game *game, int wdw_x, int wdw_y);

/* handle events */

void	destroy_imgs(t_game *game);
int		key_hook(int keycode, t_game **game);
void	quit_game(t_game *game);
int		exit_hook(t_game **game);

/* init game 1 and 2 */

void	init_textures(t_game *game);
void	init_game(t_map_parse *map);

/* init_structs */

void	init_map_struct(t_map_parse *map);
void	init_game_struct(t_game *game, t_map_parse *map);
void	init_coord_struct(t_game *game, t_pl_coord *coord);

/* player moves 1 and 2 */

void	move_player(t_game *game, int keycode);
int		is_obstacle(t_game *game, int keycode);
void	handle_exit_pos(t_game *game);

/* utils */

char	*get_all_lines(int fd, t_map_parse *map);
void	display_error_message(char *error_message);
void	free_images(t_game *game, int num_img);
void	free_split(char **split);

#endif
