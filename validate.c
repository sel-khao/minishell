int quote(char *str)
{//am i inside or outisde quotes?
    int i = 0;
    int d = 0;//outside it
    int s = 0;

    while (str[i])
    {
        if (str[i] == '\'' && d == 0)//
            s = !s;//alterna s tra 1 e 0, on and off, in and out
        else if (str[i] == '"' && s == 0)
            d = !d;
        i++;
    }
    if (s == 1 || d == 1)
        return (1);//unclosed quotes
    return (0);//success
}

int validate_pipe(char *input)
{
    int i = 0;
    int s = 0;
    int d = 0; // single and double quote flags

    while (input[i] == ' ')
        i++;
    if (input[i] == '|')
        return 1;
    while (input[i])
    {
        if (input[i] == '\'' && d == 0)
            s = !s;
        else if (input[i] == '"' && s == 0)
            d = !d;
        if (input[i] == '|' && s == 0 && d == 0)
        {//i++;
            while (input[i] == ' ')
                i++;
            if (input[i + 1] == '\0' || input[i + 1] == '|')
                return 1;
        }
        else
            i++;
    }
    return 0;
}















/*int validate_pipe(char *input)
{
    int i = 0;

    while (input[i] == 32)//any white space
        i++;
    if (input[i] == '|')
        return (1);
    while (input[i])
    {
        if (input[i] == '|')
        {
            i++;
            while (input[i] == 32)
                i++;
            if (input[i] == '\0' || input[i] == '|')
                return (1);
        }
        else
            i++;
    }
    return (0);
}*/
