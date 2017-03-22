#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int				hash(char *input)
{
	unsigned int		result;

	result = 0;
	while (*input)
	{
		result = *input + 31 * result;
		input++;
	}
	return (result % 101);
}

int		dictInsert(struct s_dict *dict, char *key, struct s_art *value)
{
	unsigned int i;
	struct s_item *item;

	i = hash(key);
	if (dict->items[i]->value == NULL)
	{
		dict->items[i]->key = key;
		dict->items[i]->value = value;
		dict->items[i]->next = NULL;
	}
	else
	{
		item = dict->items[i];
		while (item->next)
			item = item->next;
		item->next = (struct s_item *)malloc(sizeof(struct s_item));
		item->next->key = key;
		item->next->value = value;
		item->next->next = NULL;
	}
	return (1);
}

struct s_dict 	*dictInit(int capacity)
{
	struct s_dict *result;

	result = (struct s_dict *)malloc(sizeof(struct s_dict));
	result->items = (struct s_item **)malloc(sizeof(struct s_item *) * capacity);
	int i;

	i = 0;
	while (i < 101)
	{
		result->items[i] = (struct s_item *)malloc(sizeof(struct s_item));
		result->items[i]->key = NULL;
		result->items[i]->value = NULL;
		result->items[i]->next = NULL;
		i++;
	}
	if (!result->items)
		printf("failed\n");
	result->capacity = capacity;
	return (result);
}

struct	s_art	*dictSearch(struct s_dict *dict, char *key)
{
	int i;
	struct s_item *item;

	i = hash(key);
	item = dict->items[i];
	while (item)
	{
		if (strcmp(item->key, key) == 0)
			return (item->value);
		item = item->next;
	}
	return (NULL);
}

int		searchPrice(struct s_dict *dict, char *name)
{
	return (dictSearch(dict, name)->price);
}
