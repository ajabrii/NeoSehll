/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Neotoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/20 19:14:13 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "neoshell.h"

// out ====> arry [CMD,SP,RE,SP, WR]
// CMD WR >> access() > open >> os append PIP
// int ft_strlenv2(char *str, int flag)
// {
// 	int i = -1;
// 	int size;

// 	size = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == '>' || str[i] == '<')
// 		{
// 			if (flag)
// 				size+= 2;
// 		}
// 	}
// 	return (i + size);
// }

void	*ft_malloc(unsigned int size)
{
	void *res;

	res = malloc(size);
	if (!res)
		return (NULL);
	return (res);
}

// //ls>out
// //ls

// // int is_special(char *str)
// // {
// // 	int i;

// // 	i = 0;
// // 	if (!ft_strncmp(str, ">>", 2))
// // 		i = 2;
// // 	else if (!ft_strncmp(str, "<<", 2))
// // 		i = 3;
// // 	else if (!ft_strchr(str, '>') || ft_strchr(str, '<'))
// // 		i = 1;
// // 	return (i);
// // }

// // int find_index(char c)
// // {
// // 	if (c == '>')
// // 		return (1);
// // 	else if (c == '<')
// // 		return (2);
// // 	return (0);
// // }

// // void edit_redi(t_data *data)
// // {
// // 	int i = 0;
// // 	int j = 0;
// // 	data->linev2 = ft_malloc((sizeof(char) * ft_strlenv2(data->line, 1)) + 1);
// // 	while (data->line[i])
// // 	{
// // 		if (find_index(data->line[i]))
// // 		{
// // 			data->linev2[j] = ' ';
// // 			if (is_special(&data->line[i]) == 2)
// // 			{
// // 				data->linev2[++j] = '>';
// // 				data->linev2[++j] = '>';
// // 				i++;
// // 			}
// // 			else if (is_special(&data->line[i]) == 3)
// // 			{
// // 				data->linev2[++j] = '<';
// // 				data->linev2[++j] = '<';
// // 				i++;
// // 			}
// // 			else if (find_index(data->line[i]) == 1)
// // 				data->linev2[++j] = '>';
// // 			else if (find_index(data->line[i]) == 2)
// // 				data->linev2[++j] = '<';
// // 			data->linev2[++j] = ' ';
// // 			j++;
// // 			i++;
// // 		}
// // 		data->linev2[j] = data->line[i];
// // 		i++;
// // 		j++;
// // 	}
// // 	data->linev2[j] = '\0';
// // }


// // ls>out
int ft_search(t_data *data, t_type **tokenslist, t_token type)
{
	if (data->line && !(ft_strncmp(data->line, ">>", 2)))
		return (ft_get(data, &tokenslist, APP));
	else if(data->line && ft_strncmp(data->line, "<<", 1) == 0)
		return (2);
	else if(data->line && ft_strncmp(data->line, "||", 2) == 0)
		return (2);
	else if(data->line && ft_strncmp(data->line, "&&", 2) == 0)
		return (2);
	else if(data->line && ft_strncmp(data->line, ">", 1) == 0)
		return (1);
	else if(data->line && ft_strncmp(data->line, "<", 1) == 0)
		return (1);
	else if(data->line && ft_strncmp(data->line, "|", 1) == 0)
		return (1);
	else if(str && ft_strncmp(data->line, "\"", 1) == 0)
		return (1);
	else if(str && ft_strncmp(data->line, "\'", 1) == 0)
		return (1);
	return (0);
}

void ft_edit(t_data *data)
{
	int i = -1; // i did pre- incrementation
	int start = 0;
	t_type *tokenslist;
	tokenslist = NULL;
	// t_type *head = NULL;

	while (data->line[++i])
	{
		if (!ft_isalpha(data->line[i]))
		{
			// create node to store type and value of token(just WD word);
			// problem here in that case : ls >> ls enter '>' this twice !!!
			ft_get(data, &tokenslist ,start, i - start);
			// printf("here\n");
			start = i;
			while (ft_search(&data->line[i]) == 1)
			{
				i++;
				printf("%i\n", i);
				if ((ft_search(&data->line[i])) == 0 && data->line[i])
				{
					printf("here\n");
					ft_get(data, &tokenslist ,start, i - start);
				}
			}
			while (data->line[i] == ' ' && data->line[i])
				i++;
			if (!data->line[i])
				break;
			// printf("khrjat\n");
			// --i; ===> i commeted this line
			// to save where i will start next time;
			start = i;
		}
	}
	if (i != 0 && ft_isalpha(data->line[i-1]))
		ft_get(data, &tokenslist ,start, i - start);
	// printf("i == {%i}\n", i);

	// printf("\\\\\\\\\\\\\\\\\\\\\n");
	// print linked list;
	// printf("%i\n", ft_lstsize(tokenslist));
    while (tokenslist)
    {
        printf("{%s}\n", tokenslist->value);
        tokenslist = tokenslist->next;
    }
}

int ft_get(t_data *data, t_type **tokenslist, t_token type)
{
	// this is lst_new function :
    t_type *token = malloc(sizeof(t_type));
    if (token == NULL)
        return (0);
	if (type == APP || type == PPA || type == DQ
	 || type == OR || type == AND)
    	ft_strlcpy(token->value, &data->line, 2);
	else if (type == RE || type == ER || type == PIP)
		ft_strlcpy(token->value, &data->line, 1);
	// printf("[\" %s \"]\n", token->value);
    token->type = type;
    token->next = NULL;

	//this is add_back function :
    ft_lstadd_backv2(tokenslist, token);
	return (1);
}

void ft_edit(t_data *data)
{
	int i = 0;
	t_type *tokenslist;
	tokenslist = NULL;

	while (data->line)
	{
		while(ft_isalpha(&data->line))
		{
			data->line[i];
			i++;
			if (!ft_isalpha(data->line))
				ft_word(data, &tokenslist, i);
		}
		if (ft_search(&data->line) == 1)
			ft_get(data, &tokenslist, 1);
		data->line++;
	}
}

// // void	ft_get_prompt(t_data *data)
// // {
// // 	int i;
// // 	while
// // }


void	parseline(t_data *data)
{
	int i;
	i = 0;
	data->arry = ft_malloc(sizeof(int) * ft_strlen(data->line));
	// ft_coutquotes(data);
	ft_edit(data);

	// edit_redi(data);

	// printf(G "%s\n" RES, data->linev2);
}