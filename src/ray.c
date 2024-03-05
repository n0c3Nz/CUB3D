#include <stdio.h>

#define MAP_SIZE 10

int map[MAP_SIZE][MAP_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void castRay(int posX, int posY, int dirX, int dirY) {
    int mapX = posX;
    int mapY = posY;

    while(map[mapX][mapY] == 0) {
        printf("Ray at (%d, %d)\n", mapX, mapY);
		mapX += dirX;
        mapY += dirY;
    }

    printf("Ray hit wall at (%d, %d)\n", mapX, mapY);
}

int main() {
    castRay(5, 2, 0, 1); // Cast a ray from (5, 5) in the direction (1, 0)
    return 0;
}