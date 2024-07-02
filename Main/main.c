/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:10 by kali              #+#    #+#             */
/*   Updated: 2024/07/02 09:21:31 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

g_shell neobash;

// Function to print a single node in the AST
// void print_ast_node(t_node *node, int indent) {
//     if (node == NULL) {
//         return;
//     }

//     // Print node type
//     switch (node->type) {
//         case CMD_N:
//             printf("%*sCommand Node:\n", indent, "");
//             break;
//         case PIPE_N:
//             printf("%*sPipe Node:\n", indent, "");
//             break;
//         case AND_N:
//             printf("%*sAND Node:\n", indent, "");
//             break;
//         case OR_N:
//             printf("%*sOR Node:\n", indent, "");
//             break;
//         default:
//             printf("%*sUnknown Node Type\n", indent, "");
//             break;
//     }

//     // Print arguments if they exist
//     if (node->args != NULL) {
//         printf("%*sArguments: %s\n", indent + 2, "", node->args);
//     }

//     // Print IO redirection list if it exists
//     if (node->iol != NULL) {
//         printf("%*sIO Redirections:\n", indent + 2, "");
//         t_io *io_node = node->iol;
//         while (io_node != NULL) {
//             printf("%*sType: ", indent + 4, "");
//             switch (io_node->type) {
//                 case IN:
//                     printf("Input\n");
//                     break;
//                 case OUT:
//                     printf("Output\n");
//                     break;
//                 case HERE_DOC:
//                     printf("Heredoc\n");
//                     break;
//                 case APP:
//                     printf("Append\n");
//                     break;
//                 default:
//                     printf("Unknown\n");
//                     break;
//             }
//             printf("%*sValue: %s\n", indent + 4, "", io_node->value);
//             io_node = io_node->next;
//         }
//     }

//     // Recursively print left and right children
//     if (node->left != NULL) {
//         printf("%*sLeft Child:\n", indent + 2, "");
//         print_ast_node(node->left, indent + 4);
//     }

//     if (node->right != NULL) {
//         printf("%*sRight Child:\n", indent + 2, "");
//         print_ast_node(node->right, indent + 4);
//     }
// }

// // Function to print the entire AST
// void print_ast(t_node *root) {
//     if (root == NULL) {
//         printf("Syntax Tree is empty.\n");
//         return;
//     }

//     printf("Printing Abstract Syntax Tree:\n");
//     print_ast_node(root, 0);
// }

/*88888888888888*/

void printast(t_node *root)
{
    t_io *tmp;

    if (!root)
        return;
    if (root->type == CMD_N)
        printf("CMD_N\n");
    else if (root->type == PIPE_N)
        printf("PIPE_N\n");
    else if (root->type == OR_N)
        printf("OR_N\n");
    else if (root->type == AND_N)
        printf("AND_N\n");
    else
        printf("???\n");
    if (root->args)
        printf("\tnode argument %s\n", root->args);
    if (root->iol)
        printf("\tio node\n");
    tmp = root->iol;
    while (root->iol)
    {
        printf("\tio Type\n");
        if (root->iol->type == APP)
            printf("\tAPP >>\n");
        else if (root->iol->type == IN)
            printf("\tIN <\n");
        else if (root->iol->type == OUT)
            printf("\tOUT >\n");
        else if (root->iol->type == HERE_DOC)
            printf("\tHERE_DOC <<\n");
        printf("\t%s\n", root->iol->value);
        root->iol = root->iol->next;
    }
    root->iol = tmp;
    if (root->left)
    {
        printf("Left Child:\n");
        printast(root->left);
    }
    if (root->right)
    {
        printf("Right Child:\n");
        printast(root->left);
    }
}
/*/***************************** */
void    ft_init_neobash(char **env)
{
    (void)env;
    get_env_list(env);
    neobash.prs_state = 0;
    // neobash.prompt = NULL;
}
/*lldld*/
void    ft_syntax_after()
{
    if (neobash.prs_state == 1)
    {
        if (!neobash.cur_tok)
        {
        printf("neobash: syntax error near unexpected token `%s'\n", "newline");
        // free_tree();
        return ;
        }
        printf("neobash: syntax error near unexpected token `%s'\n", neobash.cur_tok->value);
        // free_tree();
    }
    return;
}

/*ldkdd*/

void neoshell()
{
    while (true)
    {
        neobash.line = readline(PROMPT);
        if (neobash.line)
            add_history(neobash.line);
        ft_lexer();
        if (!neobash.tokens)
            continue;
        neobash.tree = ft_parser();
        //print_ast(neobash.tree);
        // printast(neobash.tree);
        if (neobash.prs_state)
        {
            ft_syntax_after();
            neobash.prs_state = 0;
            continue;
        }
        // ft_executer();
    }
    ft_free_all();
}
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    ft_init_neobash(env);
    neoshell();
    return (0);
}
