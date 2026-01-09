#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <windows.h>
  static void sleep_ms(int ms) { Sleep(ms); }
  static void clear_screen(void) { system("cls"); }
#else
  #include <unistd.h>
  static void sleep_ms(int ms) { usleep(ms * 1000); }
  static void clear_screen(void) { system("clear"); }
#endif

// ANSI Farben (funktioniert in vielen Terminals; unter Windows ggf. "Virtual Terminal" aktivieren)
#define C_RESET  "\x1b[0m"
#define C_RED    "\x1b[31m"
#define C_BLUE   "\x1b[34m"
#define C_WHITE  "\x1b[97m"
#define C_YELLOW "\x1b[33m"

static void draw_flower(int stage, const char *color)
{
    // stage: 0..3 (geschlossen -> offen)
    const char *a1 = "     ";
    const char *a2 = "     ";
    const char *a3 = "     ";

    if (stage == 0) {
        a1 = "  .  ";
        a2 = "  |  ";
        a3 = "  '  ";
    } else if (stage == 1) {
        a1 = " \\|/ ";
        a2 = "  |  ";
        a3 = " / \\ ";
    } else if (stage == 2) {
        a1 = " \\ | /";
        a2 = "-- * --";
        a3 = " / | \\";
    } else { // stage 3
        a1 = " \\  |  /";
        a2 = "--  *  --";
        a3 = " /  |  \\";
    }

    printf("%s%s%s\n", color, a1, C_RESET);
    printf("%s%s%s\n", color, a2, C_RESET);
    printf("%s%s%s\n", color, a3, C_RESET);
    printf("   ||   \n");
    printf("   ||   \n");
}

int main(void)
{
    const char *colors[] = { C_RED, C_BLUE, C_WHITE, C_YELLOW };
    const int n = (int)(sizeof(colors) / sizeof(colors[0]));

    for (int stage = 0; stage <= 3; stage++) {
        clear_screen();
        for (int i = 0; i < n; i++) {
            draw_flower(stage, colors[i]);
            printf("\n");
        }
        sleep_ms(600);
    }

    // Kleine "Wackel"-Animation
    for (int t = 0; t < 12; t++) {
        clear_screen();
        for (int i = 0; i < n; i++) {
            if ((t + i) % 2 == 0) printf(" ");
            draw_flower(3, colors[i]);
            printf("\n");
        }
        sleep_ms(180);
    }

    return 0;
}
