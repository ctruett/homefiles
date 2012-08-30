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

alias cls="clear"

alias ls='ls --color=auto'
alias mkdwm='makepkg -efi --skipinteg'
alias sprunge="curl -F 'sprunge=<-' http://sprunge.us"
alias wifi='sudo wifi-menu eth0'

# lamp
alias golamp='sudo lampp start'
alias nolamp='sudo lampp stop'
alias relamp='sudo lampp restart'

# git
alias push='git push origin master'

# yaourt
alias get='yaourt -S '
alias look='yaourt -Ss '
alias remove='yaourt -R '
alias cleandeps='sudo pacman -Rns $(pacman -Qqtd)'

alias yt="youtube-viewer "

PS1='[\W] '
