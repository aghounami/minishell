# Minishell

Welcome to the Minishell project! This project involves creating a simple shell, akin to your own little version of bash. Through this project, you will gain a deeper understanding of processes and file descriptors.

**Authors:**

- <a href="https://profile.intra.42.fr/users/aghounam" style="display: inline-flex; align-items: center; text-decoration: none;" target="_blank">
    <img src="images/aghounam.jpg" alt="Ahmed's picture" width="50" height="50" style="border-radius: 50%; margin-right: 10px;">
    <span style="font-weight: bold;">aghounam</span>
  </a>
- <a href="https://profile.intra.42.fr/users/hel-magh" style="display: inline-flex; align-items: center; text-decoration: none;" target="_blank">
    <img src="images/helmagh.jpg" alt="Hamza's picture" width="50" height="50" style="border-radius: 50%; margin-right: 10px;">
    <span style="font-weight: bold;">hel-magh</span>
  </a>



## Table of Contents

- [Introduction](#introduction)
- [Common Instructions](#common-instructions)
- [Mandatory Part](#mandatory-part)

## Introduction

The existence of shells is intertwined with the very existence of IT. Initially, developers found it tedious to communicate with computers using aligned 1/0 switches. Consequently, they conceived the idea of creating software to interact with computers using interactive command lines in a human-readable language. With Minishell, you’ll revisit the challenges faced in the era before Windows.

## Common Instructions

- Your project must be written in C.
- Adhere to the Norm. If you have bonus files/functions, they are included in the norm check. A norm error results in a grade of 0.
- Your functions should not cause unexpected quits (segmentation fault, bus error, double free, etc.), except for undefined behaviors. Such occurrences will render your project non-functional and result in a grade of 0.
- Properly free all heap-allocated memory. No leaks will be tolerated.
- If required by the subject, submit a Makefile that compiles your source files to the required output with the flags `-Wall`, `-Wextra`, and `-Werror`, using `cc`. Your Makefile must not relink.
- Your Makefile must contain at least the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- For bonus parts, include a `bonus` rule in your Makefile, adding all headers, libraries, or forbidden functions from the main part. Bonuses must be in separate files `_bonus.{c/h}` unless specified otherwise. Mandatory and bonus parts are evaluated separately.
- If allowed to use your `libft`, copy its sources and Makefile into a `libft` folder. Your project’s Makefile must compile the library using its Makefile before compiling the project.
- Create test programs for your project, even though they are not for submission or grading. These tests will be particularly useful during your defense.
- Submit your work to your assigned git repository. Only the repository content will be graded. If Deepthought grades your work, it will clone your repository and perform various tests to check your program’s validity.

## Mandatory Part

### Requirements

- You must create a program called `minishell`.
- The program should have a prompt that displays when waiting for a new command.
- It should handle input of command lines with arguments.
- It should handle `’` (single quotes) and `"` (double quotes) correctly.
- Implement redirections:
  - `<` should redirect input.
  - `>` should redirect output.
  - `>>` should append output.
- Implement pipes (`|`).
- Handle environment variables (`$` followed by a sequence of characters).
- Implement `exit` to exit the shell.
- Implement `cd` to change directories.
- Implement `export` to set environment variables.
- Implement `unset` to unset environment variables.
- Implement `env` to display the environment variables.
- Implement `pwd` to display the current directory.
- Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` signals.
