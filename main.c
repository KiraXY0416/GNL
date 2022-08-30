#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char    *ft_substr(const char *s, unsigned int start, size_t len);
char    *ft_strjoin(const char *s1, const char *s2);

static void    gnl_read(int fd, char *buf, char **str)
{
    int        i;
    char    *tmp;

    if (*str == 0 || strchr(*str, '\n') == 0)
    {
        i = read(fd, buf, 42);
        while (i > 0)
        {
            buf[i] = 0;
            if (!*str)
                *str = ft_substr(buf, 0, i);
            else
            {
                tmp = *str;
                *str = ft_strjoin(*str, buf);
                free(tmp);
            }
            if (strchr(buf, '\n'))
                break ;
            i = read(fd, buf, 42);
        }
    }
    free(buf);
}

char    *ft_substr(const char *s, unsigned int start, size_t len)
{
    char    *ret;
    char    *tmp;
    size_t    i;

    ret = malloc(sizeof(char) * (len + 1));
    if (!ret)
        return (0);
    tmp = (char *)s + start;
    i = 0;
    while (*tmp && i < len)
        ret[i++] = *tmp++;
    ret[i] = 0;
    return (ret);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    int        i;
    char    *ret;
    size_t    len;

    len = strlen(s1) + strlen(s2);
    ret = malloc(sizeof(char) * (len + 1));
    if (!ret)
        return (0);
    i = 0;
    while (*s1)
        ret[i++] = *s1++;
    while (*s2)
        ret[i++] = *s2++;
    ret[i] = 0;
    return (ret);
}

int main(void)
{
    char          *buf;
    static char    *str;
    int fd = open("text.txt", O_RDONLY);

    buf = malloc(sizeof(char) * (42 + 1));
    if (!buf)
        return (0);
    if (42 <= 0 || fd < 0 )
    {
        free(buf);
        return (0);
    }
    gnl_read(fd, buf, &str);
}