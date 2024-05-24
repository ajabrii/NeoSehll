/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:51:36 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/24 20:58:41 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef TOKENS_H
# define TOKENS_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
# include <stdbool.h>
#include <sys/wait.h>
# include "../utils/utils.h"
# include "../neoshell.h"

/* <tokenization_tools.c> */
bool	is_whitespace(char line);
bool	check_spcial(char c);
int		count_whitespaces(char *line, int i);
int		check_first(char *line, int i);

/* <tokenization.c> */
int ft_get(t_data *data, t_type **tokenslist, int i, int len ,t_token type);
void	parseline(t_data *data);
void ft_lexical(t_data *data);
int check_red(t_data *data, t_type *tokenslist, int i);
#endif