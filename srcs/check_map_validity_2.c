/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:55:45 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 00:18:11 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* this function use a loop nested inside a loop in order to 
1) count the num of exits, coll, and player starting pos
2) check whether there is invalid characters (AKA not [0 1 E P C]) */

void	count_items(t_map_parse *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->map_arr[j])
	{
		while (map->map_arr[j][i])
		{
			if (map->map_arr[j][i] == 'E')
				map->nb_exit++;
			if (map->map_arr[j][i] == 'P')
				map->nb_psp++;
			if (map->map_arr[j][i] == 'C')
				map->nb_coll++;
			if (map->map_arr[j][i] != '1' && map->map_arr[j][i] != '0'
			&& map->map_arr[j][i] != 'P'
			&& map->map_arr[j][i] != 'E' && map->map_arr[j][i] != 'C')
				map->nb_inv_char++;
			i++;
		}
		i = 0;
		j++;
	}
}

/* check if the 4 last char are .ber
if not the case, free map, close file and return exit(EXIT_FAILURE) */

void	is_format_ber(char **argv, t_map_parse *map, int fd)
{
	char	*title;
	int		length;

	title = argv[1];
	length = ft_strlen(title);
	if (length < 5)
		map->ber_format = 0;
	else if (ft_strncmp(title + (length - 4), ".ber", 4) != 0)
		map->ber_format = 0;
	if (map->ber_format != 1)
	{
		display_error_message("Map is not in ber format\n");
		if (close(fd) == -1)
			perror("Error : ");
		free(map);
		exit(EXIT_FAILURE);
	}
}

/*  check for errors in map struct 
if encounters any error, prevent leaks, then exit(EXIT_FAILURE) */

void	check_errors(t_map_parse *map)
{
	if (map->nb_err_walls != 0)
		map_error_messages(1);
	if (map->nb_psp != 1)
		map_error_messages(2);
	if (map->nb_coll <= 0)
		map_error_messages(3);
	if (map->nb_exit <= 0)
		map_error_messages(4);
	if (map->nb_rect_error != 0)
		map_error_messages(5);
	if (map->nb_inv_char != 0)
		map_error_messages(6);
	if (map)
		map_error_messages(7);
	if (map->nb_err_walls != 0 || map->nb_psp != 1 || map->nb_coll <= 0
		|| map->nb_exit <= 0 || map->nb_rect_error != 0
		|| map->nb_inv_char != 0)
	{
		free_split(map->map_arr);
		free(map);
		exit(EXIT_FAILURE);
	}
}

/* just print error msgs */

void	map_error_messages(int error_type)
{
	if (error_type == 1)
		display_error_message("Map not surrounded by walls\n");
	if (error_type == 2)
		display_error_message("Player starting position unexistant or plural\n");
	if (error_type == 3)
		display_error_message("No collectible present\n");
	if (error_type == 4)
		display_error_message("No exit present\n");
	if (error_type == 5)
		display_error_message("Non rectangular map\n");
	if (error_type == 6)
		display_error_message("Invalid character used in map\n");
}
