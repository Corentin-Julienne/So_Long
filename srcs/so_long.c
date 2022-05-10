/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:28:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 00:17:25 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_map_parse	*map;

	if (argc != 2)
	{
		display_error_message("Wrong number of arguments !\n");
		exit(EXIT_FAILURE);
	}
	map = (t_map_parse *)malloc(sizeof(t_map_parse));
	if (!map)
	{
		display_error_message("Struct failed to be created\n");
		exit(EXIT_FAILURE);
	}
	init_map_struct(map);
	check_map_validity(argv, map);
	init_game(map);
	return (0);
}
