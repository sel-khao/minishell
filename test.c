#include <unistd.h>
#include <stdio.h>

/*int quote(char *str)
{
    int i = 0;
    int d = 0;
    int s = 0;

    while (str[i])
    {
        if (str[i] == '\'' && d == 0)
            s = !s;
        else if (str[i] == '"' && s == 0)
            d = !d;
        i++;
    }
    if (s == 1 || d == 1)
        return (0);//unclosed quotes
    return (1);//success
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s \"<string_to_test>\"\n", argv[0]);
        return (1);
    }

    if (quote(argv[1]))
        printf("✅ Quotes are valid.\n");
    else
        printf("❌ Quotes are NOT valid.\n");

    return (0);
}*/