# Quadris

`<m>left`: Moves the current block left `m` times.

`<m>right`: Moves the current block right `m` times.

`<m>down`: Moves the current block down `m` times.

`<m>clockwise`: Rotates the current block clockwise by `m * 90` degrees.

`<m>counterclockwise`: Rotates the current block counterclockwise by `m * 90` degrees.

`<m>drop`: Drop the current block right `m` times.

`<m>levelup`: Levels up `m` times.

`<m>leveldown`: Levels down`m` times.

`norandom <file>`: Uses block sequence from `file` for Levels 3 and 4. Make sure to include the file extension.

`random`: Uses randomization for Levels 3 and 4.

`sequence <file>`: Executes commands from `file` in sequence. Make sure to include the file extension.

`I J L S Z O T`: Spawn a block based on the letter used.

`restart`: Clear score, level, and grid.

`hint`: Suggests where to drop block using `?` symbol.

### Bonus Features

**Renaming commands**

`rename <original> <new>`: Rename a command named `original` with a new name `new`.

**Macro creation**

`macro new <name>`: Create a new macro called `name`, and listen for input for commands to add to the macro. Input commands, each separated by a newline.

`macro save`: Indicate that the you are done listing commands for the macro and save the macro.

`macro exec` <name>: Execute the macro called `name`.

**Save/Load game** 

`save <savefile>`: Save the current state of the game to a file called `savefile`

`load <savefile>`: Load a saved game file called `savefile`, replacing the current state of the game.

## Assumptions
- The heaviness property of the current and next block will change as the level changes (based on P2 design document)
- The bonus score is calculated using the level in which the block was dropped (based on P2 design document)
- The randomness setting for Levels 3 and 4 are preserved for the specific level the command was ran on. For example, if `norandom` was run on Level 3, and the user levels up to Level 4, Level 4 will still be random. Going back to Level 3, the blocks will still be generated non-randomly.
- If an invalid filename is passed with the `-scriptfile` flag, the program will use the default file `sequence.txt` for Level 0. If an invalid file is passed in the `norandom` command, the program will do nothing, staying in its current randomness state.
- `hint` will suggest the block placement that puts the block in the lowest point.
- Star blocks are included in the calculation of the scores
- For levels that use non-random block generation, the position in the block sequence is preserved after level changes. For example, if the user is on block #5 in the sequence in Level 0, levels up to Level 1, and then levels down to Level 0, they will still be on block #5.
