/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:07:51 by elibrahi          #+#    #+#             */
/*   Updated: 2025/04/20 21:03:36 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_make_word(char const *str, char c, int i)
{
	int		len;
	int		j;
	char	*word;

	len = 0;
	j = i;
	while (str[j] && str[j] != c)
	{
		len++;
		j++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
		word[j++] = str[i++];
	word[j] = '\0';
	return (word);
}

static char	**ft_free(char **words, int j)
{
	while (j >= 0)
		free(words[j--]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**words;

	words = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	i = 0;
	j = 0;
	if (!words)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			words[j] = ft_make_word(s, c, i);
			if (!words[j])
				return (ft_free(words, j));
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	words[j] = NULL;
	return (words);
}
