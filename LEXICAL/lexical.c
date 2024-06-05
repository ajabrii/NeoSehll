/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:16:25 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/05 15:49:43 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HEADERS/neoshell.h"
#include "../HEADERS/utils.h"


bool check_spcial(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return (false);
    if (c >= '0' &&  c <= '9')
        return (false);
    if (c == 45 || c == '.' || c == '/' || c == '$')
        return (false);
    return (true);
}
int ft_count(char **str)
{
    int i = 0;
    if(!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

bool check_red_or_and(char *line, int i)
{
    if (line[i] == '>' && line[i + 1] == '>')
        return (true);
    else if (line[i] == '<' && line[i + 1] == '<')
        return (true);
    else if (line[i] == '|' && line[i + 1] == '|')
        return (true);
    else if (line[i] == '&' && line[i + 1] == '&')
        return (true);
    else
        return (false);
}

// if_space() -> append_space()
// ifis -> > < >> << | || && ) ( append_spcials()
// ifis ->word or any thing $" '

int count_whitespaces(char *line, int i)
{
    int count;

    count = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
    {
        i++;
        count += 1;
    }
    return (count);
}

bool is_whitespaces(char line)
{
    if (line == ' ' || line == '\t' || line == '\v')
        return (true);
    return (false);
}

void ft_throwerr(char *err,int flag)
{
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
    if (!flag)
        ft_exit(1);
}
void ft_coutquotes()
{
	int i;

	i = 0;
	int dq = 0;
	int sq = 0;
	while (shell.line[i])
	{
		if (shell.line[i] == 34)
			dq += 1;
		else if(shell.line[i] == 39)
			sq += 1;
		i++;
	}
	if (sq % 2 != 0)
        ft_throwerr("neoshell: the single qoutes are not closed", 1);
    if (dq % 2 != 0)
        ft_throwerr("neoshell: the double qoutes are not closed", 1);

}

bool is_quotition(char i)
{
    if (i == 34)
        return (true);
    if (i == 39)
        return (true);
    else
        return (false);
}


int count_inside_quotes(int i, char q)
{
    i++;
    while (shell.line[i] && shell.line[i] != q)
    {
        i++;
    }
    if (shell.line[i] == q)
        i++;
    return i; // Return the index of the ending quote character
}
void ft_lexical()
{
    int i;

    i = 0;
    int start = 0;
    int ntoken = 0;
    int len;

    ft_coutquotes();
    shell.sub = ft_malloc(sizeof(char *) * (ft_strlen(shell.line) + 1));
    while (shell.line[i])
    {

        if (is_quotition(shell.line[i]))
        {
            start = i;
            len = count_inside_quotes(i, shell.line[i]);
            shell.sub[ntoken] = ft_substr(shell.line, start, len - start);
            ntoken++;
            i = len;
        }
        else if (check_spcial(shell.line[i]))
        {
            if (is_whitespaces(shell.line[i]))
            {
                len = count_whitespaces(shell.line, i);
                shell.sub[ntoken] = ft_substr(shell.line, i, len);
                i += len;
            }
            else if (check_red_or_and(shell.line, i))
            {
                shell.sub[ntoken] = ft_substr(shell.line, i, 2);
                i += 2;
            }
            else
            {
                shell.sub[ntoken] = ft_substr(shell.line, i, 1);
                i++;
            }
            ntoken++;
        }
        else
        {
            start = i;
            while (!check_spcial(shell.line[i]))
                i++;
            shell.sub[ntoken] = ft_substr(shell.line, start, i - start);
            ntoken++;
        }
    }
    shell.sub[ntoken] = NULL;
}

t_token set_token(int i)
{
    if (!ft_strncmp(shell.sub[i], ">", ft_strlen(shell.sub[i])))
        return (REDIRECTION);
    else if (!ft_strncmp(shell.sub[i], "<", ft_strlen(shell.sub[i])))
        return (INPUT);
    else if (!ft_strncmp(shell.sub[i], ">>", ft_strlen(shell.sub[i])))
        return (APPEND);
    else if (!ft_strncmp(shell.sub[i], "<<", ft_strlen(shell.sub[i])))
        return (HERE_DOC);
    else if (!ft_strncmp(shell.sub[i], "*", ft_strlen(shell.sub[i])))
        return (STAR);
    else if (!ft_strncmp(shell.sub[i], "&&", ft_strlen(shell.sub[i])))
        return (AND);
    else if (!ft_strncmp(shell.sub[i], "||", ft_strlen(shell.sub[i])))
        return (OR);
    else if (!ft_strncmp(shell.sub[i], " ", 1)|| !ft_strncmp(shell.sub[i], "  ", 1))
        return (WSP);
    else if (!ft_strncmp(shell.sub[i], "|", ft_strlen(shell.sub[i])))
        return (PIPE);
    else if (!ft_strncmp(shell.sub[i], "(", ft_strlen(shell.sub[i])))
        return (L_PAR);
    else if (!ft_strncmp(shell.sub[i], ")", ft_strlen(shell.sub[i])))
        return (R_PAR);
    else
    {
        if (shell.sub[i][0] == '-')
            return (OPTION);
        return (WR);
    }
}

int ft_countv2(char **str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

t_block	*ft_lstlastv3(t_block *lst)
{
	t_block	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_block	*ft_lstnewv3(char *var, t_token token)
{
	t_block	*lst;
	// int		len;

	lst = (t_block *)ft_malloc(sizeof(t_block));
	if (!lst)
		return (NULL);
    lst->value = ft_strdup(var);
    lst->token = token;
    lst->next = NULL;
    return (lst);
}

void ft_lstadd_backv3(t_block **lst, t_block *newx)
{
	t_block	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlastv3(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

void    give_token()
{
    t_block *head;
    int i;

    // int sub_count = ft_countv2(shell.sub);
    i = 0;
    head = NULL;
    while (shell.sub[i])
    {
        ft_lstadd_backv3(&head, ft_lstnewv3(shell.sub[i], set_token(i)));
        i++;
    }
    while (head)
    {
        printf("node[%s][%d]\n", head->value, head->token);
        head = head->next;
    }
}
