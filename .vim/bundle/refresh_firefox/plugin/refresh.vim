if exists('g:reload_firefox')
    finish
endif

command -nargs=0 Setreloadfirefox :call SetMozreplReloadFirefox()

function! ReloadFirefox()
        " for Cygwin: path relative to home directory
        let script_file = '/.vim/bundle/refresh_firefox/plugin/refresh.sh'

        if filereadable($HOME . script_file) 
            call system("$HOME" . script_file) 
        else
            echo "ERROR : File \"" . script_file . "\" is NOT found."
        endif
endfunction

function! SetMozreplReloadFirefox()
    if exists('g:reload_firefox')
        autocmd! mozreplreloadfirefox
        unlet g:reload_firefox
        echo "\"mozreplreloadfirefox\" of augroup has been deleted."
    else
        augroup mozreplreloadfirefox
           autocmd BufWritePost *.html,*.htm,*.php,*.js,*.css,*.less call ReloadFirefox()
        augroup END
        let g:reload_firefox=1
        echo "Firefox browser content is reloaded when file(*.html,*htm,*.php,*.js,*.css,*less) is saved."
    endif
endfunction
