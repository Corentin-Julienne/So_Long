/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:28:33 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/10 23:59:10 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* check if every line is the same length
compared to the previous one */

static void	is_map_rectangular(t_map_parse *map)
{
	int		j;
	int		len;
	int		previous_len;

	j = 1;
	previous_len = ft_strlen(map->map_arr[0]);
	while (map->map_arr[j])
	{
		len = ft_strlen(map->map_arr[j]);
		if (len != previous_len)
			map->nb_rect_error++;
		previous_len = len;
		j++;
	}
}

/* check if map sourrounded by walls
this func check only for right and left side of the map */

static void	is_intermediate_walls(t_map_parse *map)
{
	int		len;
	int		j;

	j = 1;
	len = ft_strlen(map->map_arr[0]);
	while (map->map_arr[j])
	{
		if (map->map_arr[j][0] != '1')
			map->nb_err_walls++;
		if (map->map_arr[j][len - 1] != '1')
			map->nb_err_walls++;
		j++;
	}
}

/* check if map sourrounded by walls
if map is not rectangular, stop checking
this func check only the walls at the up and down side of the map */

static void	is_walls(t_map_parse *map)
{
	int		i;
	int		num_len;

	if (map->nb_rect_error != 0)
		return ;
	i = 0;
	num_len = 0;
	while (map->map_arr[num_len])
		num_len++;
	while (map->map_arr[0][i])
	{
		if (map->map_arr[0][i] != '1')
			map->nb_err_walls++;
		i++;
	}
	i = 0;
	while (map->map_arr[num_len - 1][i])
	{
		if (map->map_arr[num_len - 1][i] != '1')
			map->nb_err_walls++;
		i++;
	}
	is_intermediate_walls(map);
}

static int	check_map_validity_2(t_map_parse *map, int fd)
{
	if (close(fd) == -1)
	{
		perror("Error : ");
		free(map->lines);
		free(map);
		exit(EXIT_FAILURE);
	}
	map->map_arr = ft_split(map->lines, '\n');
	if (!map->map_arr)
	{
		display_error_message("Split failed\n");
		free(map->lines);
		free(map);
		exit(EXIT_FAILURE);
	}
	free(map->lines);
	is_map_rectangular(map);
	is_walls(map);
	count_items(map);
	check_errors(map);
	return (0);
}

/* open the map, then cehck is formatted in .ber extension
, then parse every line with gnl, then return the results
in an array of str for checking that format constraitns are respected */

int	check_map_validity(char **argv, t_map_parse *map)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error : ");
		free(map);
		exit(EXIT_FAILURE);
	}
	is_format_ber(argv, map, fd);
	map->lines = get_all_lines(fd, map);
	if (!map->lines)
	{
		display_error_message("Allocation failure while parsing map\n");
		if (close(fd) == -1)
			perror("Error : ");
		free(map);
		exit(EXIT_FAILURE);
	}
	return (check_map_validity_2(map, fd));
}
