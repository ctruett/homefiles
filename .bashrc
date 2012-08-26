#
# ~/.bashrc
#

. /etc/profile
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# alias ls='ls --color=auto'
# PS1='[\u@\h \W]\$ '
alias mkdwm='makepkg -efi --skipinteg'
alias play='~/Develop/vlc-play'

alias lamp='sudo lampp start'
alias nolamp='sudo lampp stop'
alias newlamp='sudo lampp restart'

alias wifi='sudo wifi-menu eth0'

alias cleandeps='sudo pacman -Rns $(pacman -Qqtd)'

alias ls="ls -h --color=auto"
#] PS1='[\u@\h \W]\$ '
# PS1='\[\e[1;32m\][\u@\h \W]\$\[\e[0m\] '
red="\[\e[0;33m\]"
yellow="\[\e[0;31m\]"

PS1='[\W] '
#PS1="\[\e[01;32m\]\u@\h \[\e[01;34m\]\W \`if [ \$? = 0 ]; then echo -e '\[\e[01;32m\]:)'; else echo -e '\[\e[01;31m\]:('; fi\` \[\e[01;34m\]$\[\e[00m\]"

export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus
VST_PATH=/home/chris/vst
