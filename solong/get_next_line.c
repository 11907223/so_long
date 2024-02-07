/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:43:29 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/29 11:55:35 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	find_nchar(const char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*extract_line(char *savedlines)
{
	int		i;
	char	*nextline;

	i = find_nchar(savedlines);
	if (i >= 0)
	{
		nextline = ft_substr(savedlines, 0, i + 1);
		if (!nextline)
			return (NULL);
		return (nextline);
	}
	return (NULL);
}

static char	*update(char *savedlines)
{
	int		i;
	char	*temp;

	i = find_nchar(savedlines);
	if (i >= 0)
	{
		temp = ft_substr(savedlines, i + 1, ft_strlen(savedlines) - i);
		if (!temp)
			return (NULL);
		return (temp);
	}
	temp = ft_strdup(savedlines);
	if (!temp)
		return (NULL);
	return (temp);
}

static char	*read_lines(int fd, char **savedlines)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;
	char	*nextline;

	while (find_nchar(*savedlines) < 0)
	{
		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			break ;
		}
		temp = ft_strjoin(*savedlines, buffer);
		free(*savedlines);
		*savedlines = ft_strdup(temp);
		free(temp);
		free(buffer);
	}
	nextline = extract_line(*savedlines);
	return (nextline);
}

char	*get_next_line(int fd)
{
	static char	*savedlines = NULL;
	char		*temp;
	char		*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(savedlines);
		savedlines = NULL;
		return (NULL);
	}
	nextline = read_lines(fd, &savedlines);
	temp = update(savedlines);
	if (savedlines)
		free(savedlines);
	savedlines = ft_strdup(temp);
	free(temp);
	if (!nextline)
	{
		if (!savedlines)
			return (NULL);
		nextline = ft_strdup(savedlines);
		free(savedlines);
		savedlines = NULL;
	}
	return (nextline);
}
