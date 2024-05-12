/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:10:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/12 20:34:32 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RED "\033[30;31m"
# define G "\033[1;32m"
# define ORG "\033[1;33m"
# define PER "\033[97m"
# define CY "\033[96m"
# define RES "\033[0m"

size_t	ft_strlen(char *str);
void	ft_error(char *err);
long	ft_atol(char *str, int flag);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s1);
void	*ft_memmove(void *dst, void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_isalpha(int c);

#endif
