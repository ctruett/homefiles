#
# ~/.bashrc
#
. /etc/profile.d/autojump.bash
. /etc/profile.d/autojump.sh

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus

alias ls='ls --color=auto'
alias mkdwm='makepkg -efi --skipinteg'
alias play='~/Develop/vlc-play'
alias lamp='sudo lampp start'
alias nolamp='sudo lampp stop'
alias newlamp='sudo lampp restart'
alias sprunge="curl -F 'sprunge=<-' http://sprunge.us"
alias wifi='sudo wifi-menu eth0'
# git aliases
alias gp='git push origin master'
alias gc='git commit -m '
alias ga='git add '
alias grm='git rm -f '
# Yaourt aliases
alias get='yaourt -S '
alias look='yaourt -Ss '
alias remove='yaourt -R '
alias cleandeps='sudo pacman -Rns $(pacman -Qqtd)'

PS1='[\W] '
