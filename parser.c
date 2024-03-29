/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 20:12:37 by kcedra            #+#    #+#             */
/*   Updated: 2020/10/04 17:12:43 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pars		parser(char *filename, t_vars *vars)
{
	int		fd;
	int		gnl;
	char	*line;
	char	*text;
	t_pars	pars;

	pars_init(&pars);
	fd = open(filename, O_RDONLY);
	gnl = get_next_line(fd, &line);
	pars.flag = file_error_management(gnl, filename);
	if (pars.flag == 1)
		return (pars);
	text = ft_strdup(line);
	free(line);
	line = ft_strjoin(text, "\n");
	free(text);
	text = ft_strdup(line);
	free(line);
	while ((gnl = get_next_line(fd, &line)) != 0)
		text_join_n(&text, &line, gnl);
	text_join_n(&text, &line, gnl);
	pars.flag = args_error_management(text, &pars, 0, vars);
	free(text);
	close(fd);
	return (pars);
}
