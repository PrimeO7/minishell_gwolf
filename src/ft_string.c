/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:22:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 19:45:57 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Simple implementation of strcat.
 *
 * Appends the src string to the dst string, overwriting the terminating null
 * byte ('\0') at the end of dest, and then adds a terminating null byte.
 *
 * @param dst Destination where to append to.
 * @param src Source which shall be appended.
 * @return char* dst or NULL if empty.
 */
char	*ft_strcat(char *dst, const char *src)
{
	char	*ptr;

	if (!dst || !src)
		return (NULL);
	ptr = dst;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dst);
}

/**
 * @brief Simple implementation of strncat.
 *
 * Similar to strcat except that it will use at most n bytes from src and
 * src does not need to be null-terminated if it contains n or more bytes.
 *
 * @param dst Destination where to append to.
 * @param src Source from which to copy.
 * @param n Bytes which shall be copied.
 * @return char* dst or NULL if empty.
 */
char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*ptr;

	if (!dst || !src)
		return (NULL);
	ptr = dst;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0' && n > 0)
	{
		*ptr = *src;
		ptr++;
		src++;
		n--;
	}
	*ptr = '\0';
	return (dst);
}

/**
 * @brief Simple implementation of strcmp.
 *
 * Compares the two strings str1 and str2.
 * The comparison is done using unsigned chars.
 *
 * @param str1 String to compare.
 * @param str2 Second string to compare.
 * @return int 0 if equal, negative if str1 is less, positive if greater.
 */
int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return ((int)(unsigned char)(*str1) - (int)(unsigned char)(*str2));
}

