/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 16:53:58 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/14 16:53:59 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int main()
{
	char *s;
	char **tok;

	int i =0;
	get_next_line(0, &s);
	tok = ft_strtok(s, " ,.:;");
	while (tok[i])
	{
		printf("%s\n", tok[i++]);
	}
	//printf("%s\n", s);
}

// int main()
// {
// char test[80], blah[80];
//      char *sep = "\\/:;=-";
//      char *word, *phrase, *brkt, *brkb;

//      strcpy(test, "This;is.a:test:of=the/string\\tokenizer-function.");

//      for (word = strtok_r(test, sep, &brkt);
//           word;
//           word = strtok_r(NULL, sep, &brkt))
//      {
//          strcpy(blah, "blah:blat:blab:blag");

//          for (phrase = strtok_r(blah, sep, &brkb);
//               phrase;
//               phrase = strtok_r(NULL, sep, &brkb))
//          {
//              printf("So far we're at %s:%s\n", word, phrase);
//          }
//      }
// }
