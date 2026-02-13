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
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=5, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

// Цвета для змей и еды
enum {SNAKE1_COLOR=1, SNAKE2_COLOR=2, FOOD_COLOR_BASE=3};

struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
};

struct control_buttons default_controls1 = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};
struct control_buttons default_controls2 = {'s', 'w', 'a', 'd'};

typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
    int color;
    int is_ai;
    int player_id;
} snake_t;

typedef struct tail_t
{
    int x;
    int y;
} tail_t;

typedef struct food_t
{
    int x;
    int y;
    int color;
    time_t put_time;
} food_t;

food_t food[MAX_FOOD_SIZE];

int game_mode = 0;
int snake1_color = 1;
int snake2_color = 2;
struct control_buttons player1_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};
struct control_buttons player2_controls = {'s', 'w', 'a', 'd'};

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

void initSnake(snake_t *head, size_t size, int x, int y, int color, int is_ai, int player_id)
{
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    if (tail == NULL) {
        fprintf(stderr, "Memory allocation failed for tail\n");
        exit(EXIT_FAILURE);
    }
    
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;
    head->tsize = size;
    head->color = color;
    head->is_ai = is_ai;
    head->player_id = player_id;
    
    if (player_id == 1) {
        head->controls = player1_controls;
    } else {
        head->controls = player2_controls;
    }
}

void go(struct snake_t *head)
{
    char ch = '@';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(head->y, head->x, " ");
    
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
    
    if (head->x < 0) head->x = 0;
    if (head->x >= max_x) head->x = max_x - 1;
    if (head->y < MIN_Y) head->y = MIN_Y;
    if (head->y >= max_y) head->y = max_y - 1;
    
    attron(COLOR_PAIR(head->color));
    mvprintw(head->y, head->x, "%c", ch);
    attroff(COLOR_PAIR(head->color));
    refresh();
}

void changeDirection(struct snake_t* snake, const int32_t key)
{
    int key_lower = tolower(key);
    
    if ((key == snake->controls.down || (snake->player_id == 2 && key_lower == 's')) && snake->direction != UP)
        snake->direction = DOWN;
    else if ((key == snake->controls.up || (snake->player_id == 2 && key_lower == 'w')) && snake->direction != DOWN)
        snake->direction = UP;
    else if ((key == snake->controls.right || (snake->player_id == 2 && key_lower == 'd')) && snake->direction != LEFT)
        snake->direction = RIGHT;
    else if ((key == snake->controls.left || (snake->player_id == 2 && key_lower == 'a')) && snake->direction != RIGHT)
        snake->direction = LEFT;
}

void aiMove(snake_t *ai_snake, snake_t *player_snake)
{
    // ИИ ищем ближайшую еду
    int closest_food = -1;
    int min_distance = 1000;
    
    for (int i = 0; i < MAX_FOOD_SIZE; i++) {
        if (food[i].x != -1) {
            int dist = abs(ai_snake->x - food[i].x) + abs(ai_snake->y - food[i].y);
            if (dist < min_distance) {
                min_distance = dist;
                closest_food = i;
            }
        }
    }
    
    if (closest_food != -1) {
        // Двигаемся к еде
        int dx = food[closest_food].x - ai_snake->x;
        int dy = food[closest_food].y - ai_snake->y;
        
        if (abs(dx) > abs(dy)) {
            if (dx > 0 && ai_snake->direction != LEFT)
                ai_snake->direction = RIGHT;
            else if (dx < 0 && ai_snake->direction != RIGHT)
                ai_snake->direction = LEFT;
        } else {
            if (dy > 0 && ai_snake->direction != UP)
                ai_snake->direction = DOWN;
            else if (dy < 0 && ai_snake->direction != DOWN)
                ai_snake->direction = UP;
        }
    }
}

void goTail(struct snake_t *head)
{
    char ch = '*';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    
    int last_idx = head->tsize - 1;
    if (head->tail[last_idx].x >= 0 && head->tail[last_idx].x < max_x &&
        head->tail[last_idx].y >= MIN_Y && head->tail[last_idx].y < max_y) {
        mvprintw(head->tail[last_idx].y, head->tail[last_idx].x, " ");
    }
    
    for(size_t i = last_idx; i > 0; i--)
    {
        head->tail[i] = head->tail[i-1];
    }
    
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
    
    for(size_t i = 1; i < head->tsize; i++)
    {
        if(head->tail[i].x >= 0 && head->tail[i].y >= MIN_Y) {
            attron(COLOR_PAIR(head->color));
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
            attroff(COLOR_PAIR(head->color));
        }
    }
}

void initFood(int max_x, int max_y)
{
    for (int i = 0; i < MAX_FOOD_SIZE; i++) {
        food[i].x = -1;
        food[i].y = -1;
        food[i].color = FOOD_COLOR_BASE + (i % 6);
        food[i].put_time = 0;
    }
}

int checkCollision(int x, int y, snake_t *snake1, snake_t *snake2)
{
    // Проверка с хвостом первой змеи
    for (size_t j = 0; j < snake1->tsize; j++) {
        if (snake1->tail[j].x == x && snake1->tail[j].y == y) {
            return 1;
        }
    }
    // Проверка с головой первой змеи
    if (snake1->x == x && snake1->y == y) {
        return 1;
    }
    
    if (snake2 != NULL) {
        // Проверка с хвостом второй змеи
        for (size_t j = 0; j < snake2->tsize; j++) {
            if (snake2->tail[j].x == x && snake2->tail[j].y == y) {
                return 1;
            }
        }
        // Проверка с головой второй змеи
        if (snake2->x == x && snake2->y == y) {
            return 1;
        }
    }
    
    // Проверка с другой едой
    for (int j = 0; j < MAX_FOOD_SIZE; j++) {
        if (food[j].x == x && food[j].y == y) {
            return 1;
        }
    }
    
    return 0;
}

void putFood(int max_x, int max_y, snake_t *snake1, snake_t *snake2)
{
    for (int i = 0; i < MAX_FOOD_SIZE; i++) {
        if (food[i].x == -1) {
            int x, y;
            int collision;
            do {
                collision = 0;
                x = rand() % max_x;
                y = rand() % (max_y - MIN_Y) + MIN_Y;
                
                collision = checkCollision(x, y, snake1, snake2);
                
            } while (collision);

            food[i].x = x;
            food[i].y = y;
            food[i].put_time = time(NULL);
            break;
        }
    }
}

void updateFood(int max_x, int max_y, snake_t *snake1, snake_t *snake2)
{
    for (int i = 0; i < MAX_FOOD_SIZE; i++) {
        if (food[i].x != -1) {
            // Проверка на старение еды
            if (time(NULL) - food[i].put_time > FOOD_EXPIRE_SECONDS) {
                food[i].x = -1;
                food[i].y = -1;
                continue;
            }

            // Отрисовка еды
            attron(COLOR_PAIR(food[i].color));
            mvprintw(food[i].y, food[i].x, "$");
            attroff(COLOR_PAIR(food[i].color));

            // Проверка поедания еды первой змеей
            if (snake1->x == food[i].x && snake1->y == food[i].y) {
                if (snake1->tsize < MAX_TAIL_SIZE - 1) {
                    snake1->tsize++;
                    snake1->tail[snake1->tsize - 1].x = snake1->tail[snake1->tsize - 2].x;
                    snake1->tail[snake1->tsize - 1].y = snake1->tail[snake1->tsize - 2].y;
                }
                food[i].x = -1;
                food[i].y = -1;
            }
            
            // Проверка поедания еды второй змеей
            if (snake2 != NULL && snake2->x == food[i].x && snake2->y == food[i].y) {
                if (snake2->tsize < MAX_TAIL_SIZE - 1) {
                    snake2->tsize++;
                    snake2->tail[snake2->tsize - 1].x = snake2->tail[snake2->tsize - 2].x;
                    snake2->tail[snake2->tsize - 1].y = snake2->tail[snake2->tsize - 2].y;
                }
                food[i].x = -1;
                food[i].y = -1;
            }
        }
    }
}

int checkSnakeCollision(snake_t *snake1, snake_t *snake2)
{
    if (game_mode == 1) {
        if (snake2 != NULL) {
            for (size_t i = 0; i < snake2->tsize; i++) {
                if (snake1->x == snake2->tail[i].x && snake1->y == snake2->tail[i].y) {
                    return 1;
                }
            }
            if (snake1->x == snake2->x && snake1->y == snake2->y) {
                return 1;
            }
        }
        return 0;
    }
    for (size_t i = 1; i < snake1->tsize; i++) {
        if (snake1->x == snake1->tail[i].x && snake1->y == snake1->tail[i].y) {
            return 1;
        }
    }
    
    if (snake2 != NULL) {
        for (size_t i = 0; i < snake2->tsize; i++) {
            if (snake1->x == snake2->tail[i].x && snake1->y == snake2->tail[i].y) {
                return 1;
            }
        }
        if (snake1->x == snake2->x && snake1->y == snake2->y) {
            return 1;
        }
    }
    
    return 0;
}

int showMainMenu()
{
    int choice = 0;
    int key;
    char *menu_items[] = {
        "1. Start Single Player",
        "2. Start vs AI",
        "3. Start Co-op (2 players)",
        "4. Change Snake Colors",
        "5. Change Controls",
        "6. Exit"
    };
    int menu_size = 6;

    while (1) {
        clear();
        mvprintw(3, 10, "=== SNAKE GAME MAIN MENU ===");
        
        for (int i = 0; i < menu_size; i++) {
            if (i == choice) {
                attron(A_REVERSE);
            }
            mvprintw(5 + i * 2, 15, "%s", menu_items[i]);
            if (i == choice) {
                attroff(A_REVERSE);
            }
        }
        
        mvprintw(20, 10, "Use UP/DOWN arrows to select, ENTER to confirm");
        refresh();

        key = getch();
        if (key == KEY_UP && choice > 0) {
            choice--;
        } else if (key == KEY_DOWN && choice < menu_size - 1) {
            choice++;
        } else if (key == '\n') {
            return choice + 1;
        }
    }
}

int showColorMenu(int player_num)
{
    int choice = 0;
    int key;
    int colors[] = {1, 2, 3, 4, 5, 6, 7, 8};
    char *color_names[] = {
        "Red", "Green", "Yellow", "Blue", 
        "Magenta", "Cyan", "White", "White (Default)"
    };

    clear();
    mvprintw(5, 10, "CHOOSE COLOR FOR PLAYER %d:", player_num);
    
    for (int i = 0; i < 8; i++) {
        if (i == choice) {
            attron(A_REVERSE);
        }
        attron(COLOR_PAIR(colors[i]));
        mvprintw(7 + i, 15, "%s", color_names[i]);
        attroff(COLOR_PAIR(colors[i]));
        if (i == choice) {
            attroff(A_REVERSE);
        }
    }
    
    mvprintw(16, 10, "Use UP/DOWN arrows to select, ENTER to confirm");
    refresh();

    while (1) {
        key = getch();
        if (key == KEY_UP && choice > 0) {
            choice--;
        } else if (key == KEY_DOWN && choice < 7) {
            choice++;
        } else if (key == '\n') {
            return colors[choice];
        }
        
        // Обнов отображ
        for (int i = 0; i < 8; i++) {
            if (i == choice) {
                attron(A_REVERSE);
            }
            attron(COLOR_PAIR(colors[i]));
            mvprintw(7 + i, 15, "%s", color_names[i]);
            attroff(COLOR_PAIR(colors[i]));
            if (i == choice) {
                attroff(A_REVERSE);
            }
        }
        refresh();
    }
}

void showControlsMenu()
{
    int choice = 0;
    int key;
    char *menu_items[] = {
        "1. Player 1 Controls",
        "2. Player 2 Controls",
        "3. Back to Main Menu"
    };
    
    while (1) {
        clear();
        mvprintw(3, 10, "=== CONTROL SETTINGS ===");
        
        for (int i = 0; i < 3; i++) {
            if (i == choice) {
                attron(A_REVERSE);
            }
            mvprintw(5 + i * 2, 15, "%s", menu_items[i]);
            if (i == choice) {
                attroff(A_REVERSE);
            }
        }
        
        mvprintw(12, 10, "Current controls:");
        mvprintw(13, 15, "Player 1: Arrows (UP/DOWN/LEFT/RIGHT)");
        mvprintw(14, 15, "Player 2: WASD (W/A/S/D)");
        
        refresh();

        key = getch();
        if (key == KEY_UP && choice > 0) {
            choice--;
        } else if (key == KEY_DOWN && choice < 2) {
            choice++;
        } else if (key == '\n') {
            if (choice == 2) return;
            
            clear();
            mvprintw(5, 10, "Controls for Player %d", choice + 1);
            mvprintw(7, 10, "Press keys for: DOWN, UP, LEFT, RIGHT");
            mvprintw(8, 10, "(in that order)");
            refresh();
            
            int keys[4];
            for (int i = 0; i < 4; i++) {
                keys[i] = getch();
            }
            
            if (choice == 0) {
                player1_controls.down = keys[0];
                player1_controls.up = keys[1];
                player1_controls.left = keys[2];
                player1_controls.right = keys[3];
            } else {
                player2_controls.down = keys[0];
                player2_controls.up = keys[1];
                player2_controls.left = keys[2];
                player2_controls.right = keys[3];
            }
        }
    }
}

int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    srand(time(NULL));
    
    while (1) {
        int menu_choice = showMainMenu();
        
        if (menu_choice == 6) {
            break;
        }
        
        switch (menu_choice) {
            case 4: {
                snake1_color = showColorMenu(1);
                snake2_color = showColorMenu(2);
                continue;
            }
            case 5: {
                showControlsMenu();
                continue;
            }
        }
        
        clear();
        refresh();
        
        game_mode = menu_choice;
        
        nodelay(stdscr, TRUE);
        
        snake_t* snake1 = (snake_t*)malloc(sizeof(snake_t));
        snake_t* snake2 = NULL;
        
        if (snake1 == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            endwin();
            return EXIT_FAILURE;
        }
        
        initSnake(snake1, START_TAIL_SIZE, max_x/3, max_y/2, snake1_color, 0, 1);
        
        if (game_mode == 2) {
            snake2 = (snake_t*)malloc(sizeof(snake_t));
            initSnake(snake2, START_TAIL_SIZE, 2*max_x/3, max_y/2, snake2_color, 1, 2);
        } else if (game_mode == 3) {
            snake2 = (snake_t*)malloc(sizeof(snake_t));
            initSnake(snake2, START_TAIL_SIZE, 2*max_x/3, max_y/2, snake2_color, 0, 2);
        }
        
        initFood(max_x, max_y);
        
        // верхняя гран
        for (int i = 0; i < max_x; i++) {
            mvprintw(MIN_Y - 1, i, "-");
        }
        
        mvprintw(0, 0, "Mode: ");
        if (game_mode == 1) mvprintw(0, 6, "Single Player");
        else if (game_mode == 2) mvprintw(0, 6, "vs AI");
        else mvprintw(0, 6, "Co-op");
        
        mvprintw(1, 0, "F10 - Exit");
        refresh();
        
        // нач еда
        for (int i = 0; i < 5; i++) {
            putFood(max_x, max_y, snake1, snake2);
        }
        
        clock_t last_move_time = clock();
        const long move_interval = 70 * CLOCKS_PER_SEC / 1000;
        
        int game_over = 0;
        
        while(!game_over)
        {
            int key_pressed = getch();
            if (key_pressed == STOP_GAME) {
                break;
            }
            
            if (key_pressed != ERR) {
                changeDirection(snake1, key_pressed);
                if (snake2 != NULL && !snake2->is_ai) {
                    changeDirection(snake2, key_pressed);
                }
            }
            
            clock_t current_time = clock();
            if (current_time - last_move_time >= move_interval) {
                // Движение ИИ
                if (snake2 != NULL && snake2->is_ai) {
                    aiMove(snake2, snake1);
                }
                
                // Движение змей
                go(snake1);
                goTail(snake1);
                
                if (snake2 != NULL) {
                    go(snake2);
                    goTail(snake2);
                }
                
                updateFood(max_x, max_y, snake1, snake2);
                
                // новая еда
                static int food_counter = 0;
                food_counter++;
                if (food_counter % 8 == 0) {
                    putFood(max_x, max_y, snake1, snake2);
                }
                
                // Проверка столкновений
                if (checkSnakeCollision(snake1, snake2)) {
                    game_over = 1;
                    mvprintw(max_y/2, max_x/2 - 5, "GAME OVER - PLAYER 1 DIED");
                }
                
                if (snake2 != NULL && checkSnakeCollision(snake2, snake1)) {
                    game_over = 1;
                    mvprintw(max_y/2, max_x/2 - 5, "GAME OVER - PLAYER 2 DIED");
                }
                
                refresh();
                last_move_time = current_time;
            }
            
            usleep(1000);
        }
        
        // Оч памяти
        if (snake1->tail != NULL) free(snake1->tail);
        free(snake1);
        
        if (snake2 != NULL) {
            if (snake2->tail != NULL) free(snake2->tail);
            free(snake2);
        }
        
        nodelay(stdscr, FALSE);
        
        if (!game_over) {
            clear();
            mvprintw(max_y/2, max_x/2 - 10, "Thanks for playing! Press any key...");
            refresh();
            getch();
        } else {
            mvprintw(max_y/2 + 1, max_x/2 - 10, "Press any key to continue...");
            refresh();
            getch();
        }
    }
    
    endwin();
    return 0;
}