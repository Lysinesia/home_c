#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
};
struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t
{
    int x;
    int y;
} tail_t;

void initTail(struct tail_t t[], size_t size)
{
    for(size_t i=0; i<size; i++)
    {
        t[i].x = -1;
        t[i].y = -1;
    }
}

void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    if (tail == NULL) {
        fprintf(stderr, "Memory allocation failed for tail\n");
        exit(EXIT_FAILURE);
    }
    
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size;
    head->controls = default_controls;
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(struct snake_t *head)
{
    char ch = '@';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head->y, head->x, " ");
    
    // Сохраняем старые координаты для обновления
    int old_x = head->x;
    int old_y = head->y;
    
    switch (head->direction)
    {
        case LEFT:
            head->x--;
            if(head->x < 0)
                head->x = max_x - 1;
            break;
        case RIGHT:
            head->x++;
            if(head->x >= max_x)
                head->x = 0;
            break;
        case UP:
            head->y--;
            if(head->y < MIN_Y)
                head->y = max_y - 1;
            break;
        case DOWN:
            head->y++;
            if(head->y >= max_y)
                head->y = MIN_Y;
            break;
        default:
            break;
    }
    
    // Проверка границы
    if (head->x < 0) head->x = 0;
    if (head->x >= max_x) head->x = max_x - 1;
    if (head->y < MIN_Y) head->y = MIN_Y;
    if (head->y >= max_y) head->y = max_y - 1;
    
    mvprintw(head->y, head->x, "%c", ch);
    refresh();
}

void changeDirection(struct snake_t* snake, const int32_t key)
{
    int key_lower = tolower(key);
    
    if ((key == snake->controls.down || key_lower == 's') && snake->direction != UP)
        snake->direction = DOWN;
    else if ((key == snake->controls.up || key_lower == 'w') && snake->direction != DOWN)
        snake->direction = UP;
    else if ((key == snake->controls.right || key_lower == 'd') && snake->direction != LEFT)
        snake->direction = RIGHT;
    else if ((key == snake->controls.left || key_lower == 'a') && snake->direction != RIGHT)
        snake->direction = LEFT;
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(struct snake_t *head)
{
    char ch = '*';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    
    // Очищаем последний сегмент хвоста, если он на экране
    int last_idx = head->tsize - 1;
    if (head->tail[last_idx].x >= 0 && head->tail[last_idx].x < max_x &&
        head->tail[last_idx].y >= MIN_Y && head->tail[last_idx].y < max_y) {
        mvprintw(head->tail[last_idx].y, head->tail[last_idx].x, " ");
    }
    
    // Сдвигаем хвост
    for(size_t i = last_idx; i > 0; i--)
    {
        head->tail[i] = head->tail[i-1];
    }
    
    // Первый сегмент хвоста получает старую позицию головы
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
    
    // Отрисовываем хвост (пропускаем первый сегмент, там теперь голова)
    for(size_t i = 1; i < head->tsize; i++)
    {
        if(head->tail[i].x >= 0 && head->tail[i].y >= MIN_Y) {
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
        }
    }
}

int main()
{
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    if (snake == NULL) {
        fprintf(stderr, "Memory allocation failed for snake\n");
        return EXIT_FAILURE;
    }
    
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Отключаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);    // Отключаем курсор
    nodelay(stdscr, TRUE); // Делаем getch неблокирующим
    
    // Рисуем верхнюю границу
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    for (int i = 0; i < max_x; i++) {
        mvprintw(MIN_Y - 1, i, "-");
    }
    
    mvprintw(0, 0, "Use arrows for control. Press 'F10' for EXIT");
    refresh();
    
    clock_t last_move_time = clock();
    const long move_interval = 50 * CLOCKS_PER_SEC / 1000; // 50ms в тиках clock
    
    while(1)
    {
        // Проверяем нажатие клавиши
        int key_pressed = getch();
        if (key_pressed == STOP_GAME) {
            break;
        }
        
        // Меняем направление если нажата клавиша
        if (key_pressed != ERR) {
            changeDirection(snake, key_pressed);
        }
        
        // Двигаем змейку каждые 50ms
        clock_t current_time = clock();
        if (current_time - last_move_time >= move_interval) {
            go(snake);
            goTail(snake);
            refresh();
            last_move_time = current_time;
        }
        
        usleep(1000); // 1ms
    }
    
    // Освобождаем память
    if (snake->tail != NULL) {
        free(snake->tail);
    }
    free(snake);
    
    endwin(); // Завершаем режим curses mod
    return 0;
}