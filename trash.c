// bool ft_clean(char *line, int start, int end)
// {
//     while (start <= end)
//     {
//        if (is_whitespace(line[start]))
//             return (false);
//         start++;
//     }
//     return (true);
// }

// in the ft_get();
// if (type == DQ)
//     {
//         qt++;
//         if (qt % 2)
//             token->flag = ft_clean(data->line, start, i);
//         start = i;
//     }
//     else 
//         token->flag = true;

int ft_count(char **str)
{
    int i = 0;
    if(!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}