# mandelbrot

A Mandelbrot set renderer that runs in the terminal using ANSI escape codes and 24-bit color. Each character cell is drawn as a colored background block, so the terminal works like a pixel canvas. It adapts to your terminal size and supports real-time pan and zoom.

## Requirements

- macOS or Linux (uses `termios` and `ioctl`, so it won't build natively on Windows)
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

The default view shows the full set. Zoom in before panning for best results.

## Controls

| Key | Action |
|-----|--------|
| `w a s d` | Pan up / left / down / right |
| `z` | Zoom in |
| `x` | Zoom out |
| `q` | Quit |

## Tips

- **Shrink your terminal font for higher resolution.** Every character cell is one "pixel", so zooming the font out (e.g. `Cmd -` in iTerm2) gives a much sharper image. Resize *before* starting the program, since it reads the terminal size at launch.
- Fine details near the boundary may shift when panning or zooming due to the iteration limit (100).

## Example output

Rendered at 456 rows × 2533 columns with the terminal font zoomed far out.

![Example output of the Mandelbrot renderer](mandelbrot_example.png)
