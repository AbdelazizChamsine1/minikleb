// #include "minishell.h"

// void process_string_with_expansions(t_mini *mini, char *input)
// {
//     char *expanded_string;
//     int ret = 0; // Set this to the appropriate return code if needed

//     // Perform expansions
//     expanded_string = expansions(input, mini->env, ret);
//     if (expanded_string == NULL)
//     {
//         perror("Failed to expand variables");
//         return;
//     }

//     // Use the expanded string
//     printf("Expanded string: %s\n", expanded_string);

//     // Free the allocated memory
//     free(expanded_string);
// }

