#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
static int	find_long_line(char *buffer)
{
	int i;
	int prev_chars;
	int chars;
	chars = 0;
	prev_chars = 0;
	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			if (chars > prev_chars)
				prev_chars = chars;
			chars = 0;
		}
		else
			chars++;
		i++;
	}
	return prev_chars;
}
static char	**allocate_memory(int lines)
{
    char **mold = malloc(sizeof(char *) * lines);
    if (!mold)
        return NULL;//msg_error("Error: malloc()\n");
    return mold;
}
void fill_mold(char **lines, char *buffer, int line_length)
{
    int i = 0, j = 0, k = 0;
	lines[i] = malloc(sizeof(char) * line_length + 1);
	if (!lines[i])
		msg_error("Error: malloc()\n");
    while (buffer[k])
    {
        if (buffer[k] != '\n')
        {
            lines[i][j] = buffer[k];
            j++;
        }
		else if (buffer[k] == ' ')
		{
			lines[i][j] = '1';
			j++;
		}
        else
        {
            while (j < line_length)
                lines[i][j++] = '1';
            lines[i][j] = '\0';
            if (buffer[k+1]) // Check if not at the end of buffer
            {
                i++;
                lines[i] = malloc(sizeof(char) * line_length + 1);
                if (!lines[i])
                    exit(1); // Exit if memory allocation fails
                j = 0;
            }
        }
        k++;
    }
    while (j < line_length)
        lines[i][j++] = '1';
    lines[i][j] = '\0';
}
void	fill_map(t_cub *cub, char *buffer)
{
	int line_length;
	line_length = find_long_line(buffer);//Importante
	cub->map.lines = allocate_memory(cub->map.map_size);
	if (!cub->map.lines)
		error_msg("Error: malloc()\n");
	fill_mold(cub->map.lines, buffer, line_length);
}
int main(void)
{
	char buffer[] = "1111111\n101\n100001\n111111\n";
	printf("%s\n", buffer);
	int line_length = find_long_line(buffer);//Importante
	printf("Longest line: %d\n", line_length);
	char **mold = allocate_memory(4);//cub->map.lines
	if (!mold)
		return (1);
	fill_mold(mold, buffer, line_length);
	//Imprimir moldura
	printf("Mold:\n");
	int i = 0;
	i = 0;
	while (i < 4)
	{
		printf("%s\n", mold[i]);
		i++;
	}
	return (0);
}