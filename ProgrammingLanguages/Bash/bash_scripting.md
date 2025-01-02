Bash Scripting
==============
[URL](https://www.youtube.com/watch?v=tK9Oc6AEnR4)


# What is Bash
"**B**orn **A**gain **Sh**ell"
Used for managing the OS
Ducktape for system programming

Useful in shell
Comes as part of most linux distros

Lacks OOP/ FP
Can be hard to read

# What do you need
WSL/ Linux/ Bash on mac

# Basic commands

`echo` displays some text

```bash
echo Hello
```

`cat` takes in files and outputs file content
```bash
cat textfile.txt
```

`pwd` prints working dir location and `ls` prints dir content

# Bash Scripts

scripts can end in `.sh` or have the header `#!/usr/bin/env bash`
`bash [name].sh` will run a `.sh` file explicitly.

The $SHELL environmental variable shows the current shell active
for example:
```bash
/bin/bash
/usr/bin/zsh
```

## Variables

```bash
# Bad
cp /my/location/from /my/location/to
cp /my/location/from/here /my/location/to/there

# Good
MY_LOCATION_FROM=/my/location/from
MY_LOCATION_TO=/my/location/to

cp $MY_LOCATION_FROM $MY_LOCATION_TO
cp "$MY_LOCATION_FROM/here" "$MY_LOCATION_TO/there"
```

The syntax:
```bash
NAME=Herbert
```
stores the string "Herbert" as a value in the variable NAME

Variables can then be used either plainly using the `$` sign and within other strings in quotations
```bash
$NAME
"Hello $NAME"
```

## Interactivity

Read can take user input from the shell environment and store it:
```bash
echo "What is your first name?"
read FIRST_NAME
echo "What is your last name?"
read LAST_NAME
```

## Positional args

You can index params absolutely like variables
This script takes two arguments meant for names
```bash
echo Hello $1 $2
```

## Piping

piping takes the stdout of one command as the stdin of another, done with `|`
piping stdin into dest files:
`stdin > dest` overwrites a stdin value to a file 
`stdin >> dest` appends a stdin value to a file
piping src file content to commands
`command < src` submits a single file's content to a command
`command << src` 
