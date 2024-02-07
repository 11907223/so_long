/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:44:03 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/29 11:55:26 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !(*s))
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t bytesize)
{
	void			*array;
	size_t			i;
	unsigned char	*ptr;

	if (nmemb == 0 || bytesize == 0)
	{
		array = malloc(nmemb * bytesize);
		if (!array)
			return (NULL);
		return (array);
	}
	if (nmemb > SIZE_MAX / bytesize || nmemb > INT_MAX / bytesize)
		return (NULL);
	array = malloc(nmemb * bytesize);
	if (!array)
		return (NULL);
	ptr = array;
	i = 0;
	while (i < (nmemb * bytesize))
	{
		ptr[i] = '\0';
		i++;
	}
	return (array);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
		i++;
	substr = (char *)malloc((i + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	newstr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1[++i])
		newstr[i] = s1[i];
	j = -1;
	while (s2[++j])
		newstr[i++] = s2[j];
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*dup;

	size = ft_strlen(s);
	if (size == 0)
		return (NULL);
	dup = (char *)ft_calloc((size + 1), sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
