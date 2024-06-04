/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leg_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:37:29 by srachidi          #+#    #+#             */
/*   Updated: 2024/06/01 11:07:02 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_exprt_error(t_parms *param, char *s)
{
	write(2, "export: `", 10);
	write(2, s, ft_len(s));
	write(2, "': not a valid identifier\n", 27);
	param->ext_stts = 1;
}

int	ft_insrt_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	int		i;

	i = 0;
	dstlen = ft_len(dst);
	srclen = ft_len(src);
	if (dstlen >= dstsize || dstsize == 0)
		return (srclen + dstsize);
	while (src[i] && (i + dstlen) < (dstsize - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (srclen + dstlen);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tdst;
	unsigned char	*tsrc;

	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	tdst = (unsigned char *) dst;
	tsrc = (unsigned char *) src;
	while (n > 0)
	{
		*(tdst++) = *(tsrc++);
		n--;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_len(src);
	if (dstsize > srclen + 1)
		ft_memcpy(dst, src, srclen + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen);
}
