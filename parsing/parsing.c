/*
** parsing.c for sudoki in /home/brout_m/RENDU/CPE/sudoki-bi/parsing
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Fri Feb 26 21:10:58 2016 marc brout
** Last update Sun Feb 28 12:13:54 2016 benjamin duhieu
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sudoki.h"

int		check_str(const char *str)
{
  int		i;

  i = -1;
  while (str && str[++i])
    if (str[i] != ' ' && str[i] < '0' && str[i] > '9')
      return (1);
  return (0);
}

int		parse_tab(t_sudoku *sudo)
{
  char		*str;
  int		y;

  y = -1;
  while (++y < 9)
    {
      if (!(str = get_next_line(0)))
	return (my_puterror(MALLOC_ERROR));
      if (strlen(str) != 20)
	return (my_puterror(MAP_ERROR));
      fill_line(sudo->tab[y], str);
      if (check_str(sudo->tab[y]))
	return (my_puterror(MAP_ERROR));
      freestr(str);
    }
  return (0);
}

t_sudoku	*parse_one_input()
{
  t_sudoku	*sudo;

  if (!(sudo = malloc(sizeof(t_sudoku))))
    return (my_puterrornull(MALLOC_ERROR));
  sudo->valid = 1;
  if (!(sudo->tab = set_tab()))
    return (NULL);
  sudo->next = NULL;
  if (parse_tab(sudo))
    return (NULL);
  return (sudo);
}

t_sudoku	*parse_input()
{
  char		*str;
  t_sudoku	*sudo;
  t_sudoku	*tmp;

  if (!(sudo = malloc(sizeof(t_sudoku))))
    return (my_puterrornull(MAP_ERROR));
  sudo->valid = 2;
  sudo->next = NULL;
  while ((str = get_next_line(0)))
    {
      if (strlen(str) != 20)
	return (my_puterrornull(MAP_ERROR));
      if (!(tmp = parse_one_input()))
	return (NULL);
      freestr(str);
      is_it_valid(tmp);
      check_integrity(tmp);
      add_to_end_list(sudo, tmp);
      if (!(str = get_next_line(0)) || strlen(str) != 20)
	return (my_puterrornull(MAP_ERROR));
      freestr(str);
    }
  freestr(str);
  return (sudo);
}
