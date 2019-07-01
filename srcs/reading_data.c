typedef struct s_reading_data
{
    int amount_of_ants;
    char *start_room;
    char *end_room;
    char **rooms_connections;

}              t_data;

making_list_of_path(t_data *str, path *arr)
{
    int i;
    int k;
    int j;

    k = 0;
    while (str->rooms_connections[k][j])
    {
        i = 0;
        j = 0;
        while (str->rooms_connections[k][j] != '-')
            arr->y[i++] = str->rooms_connections[k][j++];
        if (str->rooms_connections[k][j] == '-')
            j++;
        while (str->rooms_connections[k][j])
            arr->next = str->rooms_connections[k][j++];
        k++;
    }
}

int		ft_atoi(char *str)
{
	int				i;
	int				j;
	int				sign;
	long long int	nbr;

	i = 0;
	j = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\r'
			|| str[i] == '\n' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		(str[i++] == '-') ? sign = -1 : 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i++] - '0');
		j++;
	}
	// if (j > 11 || nbr > 2147483647 || nbr < -2147483648)
	// {
	// 	write(1, "Error\n", 6);
	// 	exit(1);
	// }
	return (nbr * sign);
}

void reading_data(t_data *str)
{
    char *line;
    int i;

    line = NULL;
    get_next_line(0, &line);
    if (line[0] == "#" && line[1] != '#')
        get_next_line(0, &line);
    str->amount_of_ants = ft_atoi(line);
    while (get_next_line(0, &line))
    {
        if (line[0] == "#" && line[1] != '#')
            get_next_line(0, &line);
        if (ft_strequ(line, "##start"))
        {
            get_next_line(0, &line);
            i = -1;
            while(line[++i])
                str->start_room[i] = line[i];
        }
        if (ft_strequ(line, "##end"))
        {
            get_next_line(0, &line);
            i = -1;
            while(line[++i])
                str->end_room[i] = line[i];
        }
        if (line[0] != "#")
            reading_data_for_room_connections(str);
    }
}

void reading_data_for_room_connections(t_data *str)
{
    char *line;
    int i;
    int k;
    int j;

    k = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t')
            i++;
        else
            break ;
    }
    j = 0;
    if (line[i] == '\0')
    {
        i = 0;
        while (line[i])
            str->rooms_connections[k][j++] = line[i++];
        k++;
    }
}

