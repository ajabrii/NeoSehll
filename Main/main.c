/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:10 by kali              #+#    #+#             */
/*   Updated: 2024/08/09 16:29:44 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

g_shell neobash;

// Function to print a single node in the AST
void print_ast_node(t_node *node, int indent) {
    if (node == NULL) {
        return;
    }

    // Print node type
    switch (node->type) {
        case CMD_N:
            printf("%*sCommand Node:\n", indent, "");
            break;
        case PIPE_N:
            printf("%*sPipe Node:\n", indent, "");
            break;
        case AND_N:
            printf("%*sAND Node:\n", indent, "");
            break;
        case OR_N:
            printf("%*sOR Node:\n", indent, "");
            break;
        default:
            printf("%*sUnknown Node Type\n", indent, "");
            break;
    }

    // Print arguments if they exist
    if (node->args != NULL) {
        printf("%*sArguments: %s\n", indent + 2, "", node->args);
    }

    // Print IO redirection list if it exists
    if (node->iol != NULL) {
        printf("%*sIO Redirections:\n", indent + 2, "");
        t_io *io_node = node->iol;
        while (io_node != NULL) {
            printf("%*sType: ", indent + 4, "");
            switch (io_node->type) {
                case IN:
                    printf("Input\n");
                    break;
                case OUT:
                    printf("Output\n");
                    break;
                case HERE_DOC:
                    printf("Heredoc\n");
                    break;
                case APP:
                    printf("Append\n");
                    break;
                default:
                    printf("Unknown\n");
                    break;
            }
            printf("%*sValue: %s\n", indent + 4, "", io_node->value);
            io_node = io_node->next;
        }
    }

    // Recursively print left and right children
    if (node->left != NULL) {
        printf("%*sLeft Child:\n", indent + 2, "");
        print_ast_node(node->left, indent + 4);
    }

    if (node->right != NULL) {
        printf("%*sRight Child:\n", indent + 2, "");
        print_ast_node(node->right, indent + 4);
    }
}

// Function to print the entire AST
void print_ast(t_node *root) {
    if (root == NULL) {
        printf("Syntax Tree is empty.\n");
        return;
    }

    printf("Printing Abstract Syntax Tree:\n");
    print_ast_node(root, 0);
}

/*88888888888888*/
void    ft_init_neobash(char **env)
{
    neobash.envp = env;
    get_env_list(env);
    neobash.prs_state = 0;
    neobash.hdoc = 1;
    neobash.flag = 0;
    neobash.in = dup(0);
	neobash.out = dup(1);
    neobash.err = dup(2);
    neobash.paths = grep_paths(env);
    neobash.level = ft_atoi(get_env_val("SHLVL"));
    neobash.exp_here = true;
}
/*lldld*/
void    ft_syntax_after()
{
    int flag;

    flag = 0;
    if (neobash.prs_state == 1)
    {
        if (!neobash.cur_tok)
        {
            ft_error("neobash: syntax error near unexpected token `$'\n", "newline");
            return;
        }
        if (neobash.cur_tok->next)
        {
            ft_error("neobash: syntax error near unexpected token `$'\n", neobash.cur_tok->value);
            neobash.prs_state = 0;
            flag = 1;
        }
        if (!flag)
            ft_error("neobash: syntax error near unexpected token `$'\n", neobash.cur_tok->value);
    }
    return;
}

bool synyax_before()
{
    t_token *tmp;

    tmp = neobash.tokens;

    while (tmp)
    {
        if (tmp->type == SYNTAX)
        {
            ft_error("neobash: syntax error near unexpected token `$'", tmp->value);
            return (false);
        }
        tmp = tmp->next;
    }
    return (true);
}
void neoshell()
{
    while (true)
    {
        ft_init_signals();
        neobash.line = readline(PROMPT);
        if (neobash.line == NULL)
        {
            ft_error("exit\n", NULL);
            break;
        }
        if (neobash.line)
            add_history(neobash.line);
        if (!ft_coutquotes())
        {
            free(neobash.line);
            continue;
        }
        ft_lexer();
        if (!neobash.tokens)
            continue;
        free(neobash.line);
        if (!synyax_before())
            continue;
        // printf("hello\n");
        neobash.tree = ft_parser();
        print_ast(neobash.tree);
        if (neobash.prs_state)
        {
            // printf("prs_state == 1\n");
            ft_syntax_after();
            neobash.prs_state = 0;
            continue;
        }
        execution();
        printf("Execution result: %d\n", neobash.status);
    }
}
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    ft_init_neobash(env);
    neoshell();
    return (0);
}