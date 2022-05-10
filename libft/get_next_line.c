/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:08:16 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/10 19:22:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_protec_strchr(const char *s, int c)
{
	char	*new_ptr;
	char	d;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	d = (char)c;
	new_ptr = (char *)s;
	while (s[i])
	{
		if (s[i] != d)
			new_ptr++;
		else
			return (new_ptr);
		i++;
	}
	if (s[i] == d)
		return (new_ptr);
	else
		return (NULL);
}

static char	*obtain_line(char *relic)
{
	int		i;
	int		j;
	char	*line;

	if (!ft_protec_strchr(relic, '\n'))
		return (ft_strdup(relic));
	i = 0;
	while (relic[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = relic[j];
		j++;
	}
	line[j] = '\n';
	line[j + 1] = '\0';
	return (line);
}

static char	*obtain_relic(char *relic)
{
	char		*new_relic;
	char		*cutted_relic;

	new_relic = ft_strdup(ft_protec_strchr(relic, '\n'));
	if (relic)
		free(relic);
	if (!new_relic)
		return (NULL);
	if (ft_strlen(new_relic) > 1)
	{
		cutted_relic = ft_strdup(new_relic + 1);
		free(new_relic);
		return (cutted_relic);
	}
	free(new_relic);
	return (NULL);
}

static char	*handle_output(ssize_t reader, char *relic, char *line)
{
	if (reader == -1)
	{
		if (relic)
			free(relic);
		return (NULL);
	}
	if (!relic && !line)
		return (NULL);
	if (reader == 0 && !relic && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*relic = NULL;
	char			*line;
	char			*tmp;
	ssize_t			reader;

	reader = 1;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (ft_protec_strchr(relic, '\n') == NULL && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
			return (handle_output(reader, relic, NULL));
		buffer[reader] = '\0';
		if (!relic)
			relic = ft_strdup("");
		tmp = ft_strjoin(relic, buffer);
		if (relic)
			free(relic);
		relic = tmp;
	}
	line = obtain_line(relic);
	relic = obtain_relic(relic);
	return (handle_output(reader, relic, line));
}
