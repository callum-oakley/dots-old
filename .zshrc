# .zshrc
# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
setopt autocd
bindkey -e
# End of lines configured by zsh-newuser-install

autoload -Uz compinit promptinit
compinit
promptinit

autoload -U colors
colors

autoload -U zmv
alias mmv="noglob zmv -W"

autoload -U promptinit
promptinit
PROMPT="%{$fg[green]%}%1~ ➜  %{$reset_color%}"

alias ls="ls --color=auto"
