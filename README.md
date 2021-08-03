# Quadris

`<m>left`: Moves the current block left `m` times.

`<m>right`: Moves the current block right `m` times.

`<m>down`: Moves the current block down `m` times.

`<m>clockwise`: Rotates the current block counterclockwise by `m * 90` degrees.

`<m>counterclockwise`: Rotates the current block counterclockwise by `m * 90` degrees.

`<m>drop`: Drop the current block right `m` times.

`<m>levelup`: Levels up `m` times.

`<m>leveldown`: Levels down`m` times.

`norandom <file>`: Uses block sequence from `file` for Levels 3 and 4.

`random`: Uses randomization for Levels 3 and 4.

`sequence <file>`: Executes commands from `file` in sequence.

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
