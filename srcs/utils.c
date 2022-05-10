/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:07:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/10 23:24:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_empty_lines_err(char *next_line, char *all_lines,
	t_map_parse *map, int fd)
{
	if (!next_line)
		return ;
	if (ft_strlen(next_line) == 1 && next_line[0] && next_line[0] == '\n')
	{
		display_error_message("Map has at least one empty line\n");
		free(next_line);
		if (all_lines)
			free(all_lines);
		free(map);
		if (close(fd) == -1)
			perror("Error : ");
		exit(EXIT_FAILURE);
	}
}

char	*get_all_lines(int fd, t_map_parse *map)
{
	char	*next_line;
	char	*all_lines;
	char	*tmp;
	int		iter;

	next_line = NULL;
	all_lines = ft_strdup("");
	if (!all_lines)
		return (NULL);
	iter = 0;
	while (next_line || iter == 0)
	{
		next_line = get_next_line(fd);
		check_empty_lines_err(next_line, all_lines, map, fd);
		if (next_line)
		{
			tmp = ft_strjoin(all_lines, next_line);
			free(all_lines);
			all_lines = tmp;
			free(next_line);
		}
		iter++;
	}
	return (all_lines);
}

/* display an error message while failure of any type (on STDERR)*/

void	display_error_message(char	*error_message)
{
	char	*prefix;

	prefix = "Error : ";
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
}

/* free image previously malloqued in case of malloc error 
or when about to exit the program */

void	free_images(t_game *game, int num_img)
{
	free(game->img_space);
	free(game->img_wall);
	if (num_img == 3)
		free(game->img_psp);
	if (num_img == 4)
	{
		free(game->img_psp);
		free(game->img_coll);
	}
	if (num_img == 5)
	{
		free(game->img_psp);
		free(game->img_coll);
		free(game->img_exit);
	}
}

/* free split is used for freeing an array of str
when every str is also malloqued */

void	free_split(char **split)
{
	int		len;
	int		i;

	len = 0;
	while (split[len])
		len++;
	i = 0;
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
