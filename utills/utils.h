/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:11:08 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/09 16:13:49 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef UTILS_H
# define UTILS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BL "\033[1;36m"
#define RED "\033[1;31m"
#define RES "\033[0m"

char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);

#endif