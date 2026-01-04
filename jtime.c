#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// [cite: 1, 2] Digital font for the clock
char font[128][5][4] = {
    ['0'] = {{"###"},{"# #"},{"# #"},{"# #"},{"###"}},
    ['1'] = {{"  #"},{"  #"},{"  #"},{"  #"},{"  #"}},
    ['2'] = {{"###"},{"  #"},{"###"},{"#  "},{"###"}},
    ['3'] = {{"###"},{"  #"},{"###"},{"  #"},{"###"}},
    ['4'] = {{"# #"},{"# #"},{"###"},{"  #"},{"  #"}},
    ['5'] = {{"###"},{"#  "},{"###"},{"  #"},{"###"}},
    ['6'] = {{"###"},{"#  "},{"###"},{"# #"},{"###"}},
    ['7'] = {{"###"},{"  #"},{"  #"},{"  #"},{"  #"}},
    ['8'] = {{"###"},{"# #"},{"###"},{"# #"},{"###"}},
    ['9'] = {{"###"},{"# #"},{"###"},{"  #"},{"###"}},
    [':'] = {{"   "},{" # "},{"   "},{" # "},{"   "}}
};

// [cite: 3, 4] Fetch weather using wttr.in with improved formatting
void get_weather(char *dest) {
    FILE *fp;
    char path[150];
    // Formats: %t(temp), %f(feels like), %w(wind), %C(condition)
    fp = popen("curl -s 'wttr.in/Melbourne?format=%C+%t(Feels:%f)+Wind:%w' | tr -dc '[:alnum:][:punct:][:space:]'", "r");
    if (fp == NULL) {
        strcpy(dest, "Weather Unavailable"); // 
        return;
    }
    if (fgets(path, sizeof(path), fp) != NULL) {
        path[strcspn(path, "\n")] = 0; // [cite: 6]
        strcpy(dest, path); // [cite: 7]
    }
    pclose(fp);
}

//  Fetch Raspberry Pi CPU Temperature
void get_cpu_temp(char *dest) {
    FILE *fp = popen("vcgencmd measure_temp", "r");
    if (fp != NULL) {
        if (fgets(dest, 20, fp) != NULL) {
            char *temp = strchr(dest, '=');
            if (temp) strcpy(dest, temp + 1);
            dest[strcspn(dest, "\n")] = 0;
        }
        pclose(fp);
    } else {
        strcpy(dest, "N/A");
    }
}

// [cite: 8] Helper to draw the large digits
void draw_big_digit(int ch, int x_offset, int y_offset) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            if (font[ch][row][col] == '#') {
                attron(COLOR_PAIR(1));
                mvaddch(y_offset + row, x_offset + col, ' ');
                attroff(COLOR_PAIR(1));
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int chosen_color = COLOR_GREEN; // [cite: 8]
    if (argc > 1) { // [cite: 9]
        if (strcmp(argv[1], "red") == 0) chosen_color = COLOR_RED; // [cite: 9]
        else if (strcmp(argv[1], "blue") == 0) chosen_color = COLOR_BLUE; // [cite: 10]
    }

    initscr(); noecho(); curs_set(0); nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, chosen_color); // [cite: 11]
    init_pair(2, COLOR_CYAN, COLOR_BLACK);   // [cite: 11]
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    time_t rawtime, last_weather_time = 0;
    struct tm *timeinfo;
    char time_buf[9], date_buf[64], weather_buf[150] = "Loading...";
    char cpu_temp[20] = "N/A";

    while (getch() != 'q') {
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        // Update weather every 15 minutes [cite: 13, 24]
        if (rawtime - last_weather_time > 900) {
            get_weather(weather_buf);
            last_weather_time = rawtime; // [cite: 14]
        }
        
        // Update CPU Temp every loop 
        get_cpu_temp(cpu_temp);

        strftime(time_buf, sizeof(time_buf), "%H:%M:%S", timeinfo); // [cite: 14]
        strftime(date_buf, sizeof(date_buf), "%A, %d %B %Y", timeinfo); // [cite: 15]

        erase();
        int clock_x = (COLS - (8 * 5)) / 2; // [cite: 15]
        int clock_y = (LINES - 12) / 2;    // [cite: 16]

        // 1. Draw Big Clock [cite: 16]
        for (int i = 0; i < 8; i++) 
            draw_big_digit(time_buf[i], clock_x + (i * 5), clock_y);

        // 2. Draw Date [cite: 17]
        attron(A_BOLD);
        mvprintw(clock_y + 7, (COLS - strlen(date_buf)) / 2, "%s", date_buf);
        attroff(A_BOLD);

        // 3. Draw Weather Info [cite: 18, 19, 20]
        attron(COLOR_PAIR(2) | A_ITALIC);
        mvprintw(clock_y + 9, (COLS - strlen(weather_buf) - 11) / 2, "Melbourne: %s", weather_buf);
        attroff(COLOR_PAIR(2) | A_ITALIC);

        // 4. Draw System Vitals 
        attron(COLOR_PAIR(3));
        char vital_str[50];
        sprintf(vital_str, "CPU Temp: %s", cpu_temp);
        mvprintw(clock_y + 11, (COLS - strlen(vital_str)) / 2, "%s", vital_str);
        attroff(COLOR_PAIR(3));

        refresh();
        usleep(500000); // [cite: 21]
    }

    endwin();
    return 0;
}
