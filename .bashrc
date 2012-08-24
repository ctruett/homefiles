#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# alias ls='ls --color=auto'
# PS1='[\u@\h \W]\$ '
alias mkdwm='makepkg -efi --skipinteg'
alias play='~/Develop/vlc-play'

alias ls="ls -h --color=auto"
export PS1='\[\033[01;32m\]\u@\h \[\033[00;31m\]\W \$ \[\033[00m\]'

export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus
