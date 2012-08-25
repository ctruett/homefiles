call pathogen#infect()

set t_Co=256
colo zenburn
" colo github
set go=-T
set go=-t
set go=-r
set go=-R
set guifont=DejaVu\ Sans\ Mono\ 8

" Forget compatibility with Vi. Who cares.
set nocompatible

" Turn backup off, since most stuff is in SVN, git et.c anyway...
set nobackup
set nowb
set noswapfile

" Enable filetypes
filetype on
filetype plugin on
filetype indent on
syntax on

" Display current cursor position in lower right corner.
set ruler

" Want a different map leader than \
let mapleader = ","
let g:mapleader = ","

" Ever notice a slight lag after typing the leader key + command? This lowers
"the timeout.
set timeoutlen=500

" Indent stuff
set smartindent
set autoindent

" Always show the status line
set laststatus=2

" Prefer a slightly higher line height
set linespace=3

"Shortcut for editing  vimrc file in a new tab
nmap <leader>ev :edit $MYVIMRC<cr>

" make : commands easier
nnoremap ; :

" Source the vimrc file after saving it. This way, you don't have to reload Vim to see the changes.
if has("autocmd")
  augroup myvimrchooks
    au!
    autocmd bufwritepost .vimrc source ~/.vimrc
  augroup END
endif

" easier window navigation
nmap <C-h> <C-w>h
nmap <C-j> <C-w>j
nmap <C-k> <C-w>k
nmap <C-l> <C-w>l

" tab navigation
nmap <leader>f :bNext<cr>
nmap <leader>d :bprevious<cr>

" Pressing ,ss will toggle and untoggle spell checking
map <leader>ss :setlocal spell!<cr>


""""""""""""" STOLEN FROM JANUS

" format the entire file
nmap <leader>fef ggVG=''

" upper/lower word
nmap <leader>` mQviwU`Q
nmap <leader>~ mQviwu`Q

" cd to the directory containing the file in the buffer
nmap <silent> <leader>cd :lcd %:h<CR>

" set text wrapping toggles
nmap <silent> <leader>tw :set invwrap<CR>:set wrap?<CR>

" Map the arrow keys to be based on display lines, not physical lines
map <j> gj
map <k> gk

" Adjust viewports to the same size
map <Leader>= <C-w>=

" Map command-[ and command-] to indenting or outdenting
" while keeping the original selection in visual mode
vmap <A-]> >gv
vmap <A-[> <gv

nmap <A-]> >>
nmap <A-[> <<

omap <A-]> >>
omap <A-[> <<

imap <A-]> <Esc>>>i
imap <A-[> <Esc><<i



"" Whitespace
set nowrap " don't wrap lines
set tabstop=2 " a tab is two spaces
set shiftwidth=2 " an autoindent (with <<) is two spaces
set expandtab " use spaces, not tabs
set list " Show invisible characters
set backspace=indent,eol,start " backspace through everything in insert mode






" List chars
set listchars="" " Reset the listchars
set listchars=tab:\ \ " a tab should display as " ", trailing whitespace as "."
set listchars+=trail:. " show trailing spaces as dots
set listchars+=extends:> " The character to show in the last column when wrap is
" off and the line continues beyond the right of the screen
set listchars+=precedes:< " The character to show in the last column when wrap is
" off and the line continues beyond the right of the screen

"" Searching
set nohlsearch " highlight matches
set incsearch " incremental searching
set ignorecase " searches are case insensitive...
set smartcase " ... unless they contain at least one capital letter

" Toggle hlsearch with <leader>hs
nmap <leader>hs :set hlsearch! hlsearch?<CR>

" Statusline
if has("statusline") && !&cp
  set laststatus=2 " always show the status bar

  "" Start the status line
  set statusline=%f\ %m\ %r
  set statusline+=Line:%l/%L
endif


"""""""""""""""""""""""""""""""""""
" EasyMotion
"""""""""""""""""""""""""""""""""""
let g:EasyMotion_leader_key = '<Leader>m'


" NERDCommenter
nmap <leader>cc :NERDComToggleComment<CR>
" NERDTree
nmap <leader>g :NERDTreeToggle<CR>



" Close the current buffer
map <leader>bd :Bclose<cr>

" Don't close window, when deleting a buffer
command! Bclose call <SID>BufcloseCloseIt()
function! <SID>BufcloseCloseIt()
  let l:currentBufNum = bufnr("%")
  let l:alternateBufNum = bufnr("#")

  if buflisted(l:alternateBufNum)
    buffer #
  else
    bnext
  endif

  if bufnr("%") == l:currentBufNum
    new
  endif

  if buflisted(l:currentBufNum)
    execute("bdelete! ".l:currentBufNum)
  endif
endfunction

" Load / Save calls
" nnoremap <leader>g :browse confirm e<CR>
" nnoremap <leader>b :browse confirm w<CR>

" Zen Coding keys
let g:user_zen_expandabbr_key = '<c-e>'

" NarrowRegion
nmap <leader>nr :NarrowRegion<CR>
au BufRead,BufNew *.less set filetype=css

"A mapping to make a backup of the current file.
function! WriteBackup()
  let l:fname = expand('%:p') . strftime('%Y_%m_%d_%H.%M.%S')
  silent execute 'write' l:fname
  echomsg 'Wrote' l:fname
endfunction

nnoremap <Leader>ba :<C-U>call WriteBackup()<CR>

nnoremap <leader>da "=strftime("%B %d, %Y - %I:%M %p")<CR>P

set mouse=a
let g:CSApprox_attr_map = { 'bold' : 'bold', 'italic' : '', 'sp' : '' }

nnoremap <leader>dws :%s/\s\+$//e<CR>

map <F10> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<'
      \ . synIDattr(synID(line("."),col("."),0),"name") . "> lo<"
      \ . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<CR>
