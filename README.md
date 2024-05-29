# Bingo SIM

I did this project because I was curious on how many turns would a bingo game last on average given the number of players.

To run this, simply compile it using `make` and run:

```
./main MODE[FULL/LINE] NUM_PLAYERS NUM_ITERS
```

Where:
- `MODE`: Is the game mode.
    - `FULL`: The card needs to be completely filled.
    - `LINE`: Any vertical/horizontal line wins the game.
- `NUM_PLAYERS`: Number of cards playing.
- `NUM_ITERS`: Number of iterations that we will run the simulation.

In the end it should print the average number of turns, as well as the standard deviation.

Some comments:
- You can build it in debug mode and it will print additional info, but this is basically useless now that it's finished.
- You can also build with OpenMP support by running `make OPENMP=1`.
- This is not super optimized and maybe trying to find explicitly $\mathbb{E} [min(X_1, X_2, ..., X_n)]$ where $X_i$ are iid random variables representing the number of turns that it takes for a card to win probably is more effective. 