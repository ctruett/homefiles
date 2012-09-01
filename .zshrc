#
# ~/.zshrc
#

export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus

alias cls="clear"

alias ls='ls --color=auto'
alias mkdwm='makepkg -efi --skipinteg'
alias sprunge="curl -s -F 'sprunge=<-' http://sprunge.us | tr -d '\n' | xclip"
alias wifi='sudo wifi-menu eth0'

# lamp
alias golamp='sudo lampp start'
alias nolamp='sudo lampp stop'
alias relamp='sudo lampp restart'

# yaourt
alias get='yaourt -S '
alias look='yaourt -Ss '
alias remove='yaourt -R '
alias cleandeps='sudo pacman -Rns $(pacman -Qqtd)'

alias yt='youtube-viewer -n -quiet -C --resolution=480 -append_mplayer=" -vo xv -quiet -zoom" --results 5 '
alias ytv='youtube-viewer --resolution=480 -C -append_mplayer=" -vo xv -quiet -zoom" --results 5 '

bindkey ';5D' backward-word
bindkey ';5C' forward-word
setopt CORRECT
setopt EXTENDED_HISTORY
setopt MENUCOMPLETE
setopt BG_NICE
unsetopt ALL_EXPORT
EDITOR='vim'
HISTFILE=$HOME/.zhistory
HISTSIZE=2000
SAVEHIST=2000
LANG='en_US.UTF-8'
LC_ALL='en_US.UTF-8'
LC_CTYPE=C
PAGER='less'
PATH="/usr/local/bin:/usr/local/sbin/:/bin:/sbin:/usr/bin:/usr/sbin:$PATH"
PR_NO_COLOR="%{$terminfo[sgr0]%}"
#[[ $- != *i* ]] && return 
PROMPT='%c > '
autoload -U compinit
compinit
zmodload -a zsh/stat stat
zmodload -a zsh/zpty zpty
zmodload -a zsh/zprof zprof
zstyle ':completion::complete:*' cache-path ~/.zsh/cache/$HOST
zstyle ':completion:*::::' completer _expand _complete _ignored _approximate
zstyle ':completion::complete:*' use-cache on
zstyle ':completion:*:corrections' format '%B%d (errors: %e)%b'
zstyle ':completion:*:descriptions' format '%B%d%b'
zstyle ':completion:*:expand:*' tag-order all-expansions
zstyle ':completion:*:functions' ignored-patterns '_*'
zstyle ':completion:*' group-name ''
zstyle ':completion:*' hosts $(grep "^#%" /etc/hosts | awk -F% '{print $2}')
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*' list-prompt '%SAt %p: Hit TAB for more, or the character to insert%s'
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'
zstyle ':completion:*' menu select=1 _complete _ignored _approximate
zstyle ':completion:*:messages' format '%d'
zstyle ':completion:*:*:(^rm):*:*files' ignored-patterns '*?.o' '*?.c~' \
    '*?.old' '*?.pro'
zstyle ':completion:*' select-prompt '%SScrolling active: current selection at %p%s'
zstyle ':completion:*:*:-subscript-:*' tag-order indexes parameters
zstyle ':completion:*' verbose yes
zstyle ':completion:*:warnings' format 'No matches for: %d'
# zstyle -e ':completion:*:approximate:*' max-errors \
#     'reply=( $(( ($#PREFIX+$#SUFFIX)/2 )) numeric )'
#zstyle ':completion:*:*:*:users' ignored-patterns \
#        foo bar \
