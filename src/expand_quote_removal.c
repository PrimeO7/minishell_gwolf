/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:49:12 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 19:15:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

t_err	ft_quote_removal(char *str)
{
	t_track	input;
	bool	in_double_quotes;
	t_err	err;

	ft_init_tracker(&input, str);
	in_double_quotes = false;
	while (input.str[input.pos])
	{
		if (input.str[input.pos] == '\'' && !in_double_quotes)
			err = ft_rm_single_quote(&input);
		else if (input.str[input.pos] == '"')
			err = ft_rm_double_quote(&input, &in_double_quotes);
		else
			err = ft_move_tracker(&input);
		if (err != SUCCESS)
			return (err);
	}
	return (SUCCESS);
}

/**
 * @brief Remove single quotes.
 *
 * Remove found single quote with ft_eat_char().
 * Jump over quoted part, searching for the second single.
 * Remove the second single quote.
 *
 * @param expr String
 * @param pos Current position
 * @return t_err SUCCESS
 */
t_err	ft_rm_single_quote(t_track *input)
{
	ft_eat_char(input);
	while (input->str[input->pos] != '\'')
		input->pos++;
	ft_eat_char(input);
	return (SUCCESS);
}

/**
 * @brief Remove double quotes.
 *
 * Remove found double quote with ft_eat_char().
 * Switch bool in_quotes on/off.
 * This way we know if we are in double quotes or not.
 * The next time we see a double quote the switch gets flipped again.
 *
 * @param expr String.
 * @param pos Current position.
 * @param in_double_quotes Pointer to change switch.
 * @return t_err SUCCESS.
 */
t_err	ft_rm_double_quote(t_track *input, bool *in_double_quotes)
{
	ft_eat_char(input);
	*in_double_quotes = !(*in_double_quotes);
	return (SUCCESS);
}
