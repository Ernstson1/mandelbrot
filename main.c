#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define max_iter 100

typedef struct
{
    int rows;
    int columns;
    char* buffer;
    int len;
} Terminal;

struct termios original;
Terminal* t;

Terminal* create_terminal(int rows, int cols)
{
    Terminal* term = malloc(sizeof(Terminal));
    term->rows = rows;
    term->columns = cols;
    term->buffer = malloc(cols * rows * 30);
    term->len = 0;
    return term;
}

void draw(double offset_real, double offset_imag, double zoom)
{

    // Formula: z_n+1 = z_n^2 + c
    // c is a point in the complex plain
    /*
    z = (a + bi)
    then z² = (a + bi)² = a² + 2abi + (bi)²
            = a² + 2abi - b²      (because i² = -1)
            = (a² - b²) + (2ab)i

    real part is (a² - b²) and imaginary part is 2ab
    */

    t->len = 0;

    for (int y = 0; y < t->rows; y++)
    {
        for (int x = 0; x < t->columns; x++)
        {
            double c_real = offset_real + (x / (double)t->columns) * 3.4 * zoom;
            double c_imag = offset_imag + (y / (double)t->rows) * 1.5 * zoom;

            double z_real = 0, z_imag = 0;

            int in_set = 1;
            int i = 0;
            for (i = 0; i < max_iter; i++)
            {
                double new_real = z_real * z_real - z_imag * z_imag + c_real;
                double new_imag = 2 * z_real * z_imag + c_imag;
                z_real = new_real;
                z_imag = new_imag;
                if (z_real * z_real + z_imag * z_imag > 4.0)
                {
                    in_set = 0;
                    break;
                }
            }
            if (in_set)
            {
                t->len += sprintf(t->buffer + t->len, "\033[%d;%dH  ", y + 1, x * 2 + 1);
            }
            else
            {
                t->len += sprintf(t->buffer + t->len, "\033[%d;%dH", y + 1, x * 2 + 1);
                if (i < 7)
                    t->len += sprintf(t->buffer + t->len, "  "); // empty/black for fast escapers
                else
                {
                    int color = (i % 6) + 31;
                    t->len += sprintf(t->buffer + t->len, "\033[%dm██\033[0m", color);
                }
            }
        }
    }
    write(STDOUT_FILENO, t->buffer, t->len);
}

void enable_raw_mode()
{
    struct termios raw;
    tcgetattr(0, &original);
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO); // disable line buffering and echo
    tcsetattr(0, TCSANOW, &raw);
}

void disable_raw_mode()
{
    tcsetattr(0, TCSANOW, &original);
}

void handle_sigint(int sig)
{
    (void)sig;
    disable_raw_mode();
    free(t->buffer);
    free(t);
    exit(0);
}

int main()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    t = create_terminal(w.ws_row, w.ws_col / 2);

    signal(SIGINT, handle_sigint);
    enable_raw_mode();
    double offset_real = -2.75;
    double offset_imag = -0.5;
    double zoom = 0.5;
    draw(offset_real, offset_imag, zoom); // commented for testing

    char c;
    while ((c = getchar()) != 'q')
    {
        double step = 0.1;
        if (c == 'a')
            offset_real -= step;
        if (c == 'd')
            offset_real += step;
        if (c == 'w')
            offset_imag -= step;
        if (c == 's')
            offset_imag += step;
        if (c == 'z')
            zoom -= 0.1;
        if (c == 'x')
            zoom += 0.1;

        if (zoom < 0.001)
            zoom = 0.001;
        draw(offset_real, offset_imag, zoom);
    }

    disable_raw_mode();
    free(t->buffer);
    free(t);
    return 0;
}