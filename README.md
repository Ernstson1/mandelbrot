# mandelbrot

A Mandelbrot set renderer in the terminal using ANSI escape codes and Unicode block characters. Adapts to your terminal size and supports real-time pan and zoom.

## Requirements

- A terminal with true color (24-bit) support (iTerm2, Kitty, most modern Linux terminals)
- GCC or Clang

## Build

```sh
gcc main.c -o main
```

## Run

```sh
./main
```

Zoom in before panning for best results — the default view shows the full set.

## Controls

| Key | Action |
|-----|--------|
| `w a s d` | Pan up / left / down / right |
| `z` | Zoom in |
| `x` | Zoom out |
| `q` | Quit |

## Notes
- Best experienced in a large terminal window — the example screenshot was taken at 456 × 2533
- True color (24-bit) terminal required (iTerm2, Kitty, most modern Linux terminals)
- Fine details near the boundary may shift when panning/zooming due to iteration limits

## Example output
This is an example of the output for a terminal of size: 456 x 2533

![an example of the output](mandelbrot_example.png)