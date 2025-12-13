#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int modulo100rest(int n)
{
    return (n+100000)%100;
}

int countpoints(int dial, int current)
{
    int counter = 0;
    int whole_steps = current / 100;
    if (whole_steps < 0)
        whole_steps = -whole_steps;
    if ((dial + current % 100 >= 100) || (dial != 0 && dial + current % 100 <= 0))
        counter++;
    return counter + whole_steps;
}

int day1(void)
{
    FILE *stream;
    char buffer[256];
    int dial_part1 = 50;
    int dial_part2 = 50;
    int count_part1 = 0;
    int count_part2 = 0;
    stream = fopen("./Day1/day1.txt", "r");
    int current;
    char direction;
    while (fgets(buffer, sizeof(buffer), stream))
    {
        current = atoi(&buffer[1]);
        direction = buffer[0];
        if (direction == 'R')dial_part1 = modulo100rest(dial_part1 + current);
        else
        {
            dial_part1 = modulo100rest(dial_part1 + 100 - current);
            current = -current;
        }

        if (dial_part1 == 0 || dial_part1 == 100)count_part1 += 1;
        count_part2 += countpoints(dial_part2, current);
        dial_part2 = modulo100rest(dial_part2 + current);
    }
    fseek(stream, 0, SEEK_SET);
    fclose(stream);
    printf("day 1 part 1 : %d\n", count_part1);
    printf("day 1 part 2 : %d\n", count_part2);
    return 0;
}
