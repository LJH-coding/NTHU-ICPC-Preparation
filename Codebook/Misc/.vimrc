syntax on
set showmode
set showcmd
set nu!
set autoindent
set cindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
vmap <C-c> y
map <C-A> ggVGY
map! <C-A> <Esc>ggVGY
map <F12> gg=G
set backspace=2
"Compiled
autocmd vimEnter *.cpp map <F5> :w <CR> :!clear ; g++ --std=c++17 %  && echo Compiled successfully. && time ./a.out; <CR>
autocmd vimEnter *.c map <F5> :w <CR> :!clear ; gcc %  && echo Compiled successfully. && time ./a.out; <CR>
