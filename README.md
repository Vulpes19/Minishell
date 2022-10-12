# Minishell
## TwoBrosShell - Our own shell in C Language
Minishell is a 1337 project about creating a simple shell, this is a group project so me and my brother decided to do a TwoBrosShell.
## The feautures of our Shell
- A working history.
- Handles ' (single quote) and " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence
- Redirections (< redirect input) (> redirect output) (<< heredoc) (>> redirect output in append mode)
- Handles pipes.
- Handles environment variables which should expand to their values.
- Handles $? which should expand the exit status.
- Handles ctrl-C, ctrl-D and ctrl-\ .
- The following builtins are made by the executer:
  echo with (-n)<br/>
  cd<br/>
  pwd<br/><br/>
  export<br/>
  unset<br/>
  env<br/>
  exit<br/>
## The team
The parser: [@0xDopamine]<br/>
The executer: [@Vulpes19]
