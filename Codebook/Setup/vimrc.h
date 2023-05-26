se nu ai hls et ru ic is sc cul
se re=1 ts=4 sts=4 sw=4 ls=2 mouse=a
syntax on
hi cursorline cterm=none ctermbg=89
set bg=dark
autocmd vimEnter *.cpp map <F5> :w <CR> :!clear ; g++ -g --std=c++17 %  && echo Compiled successfully. && time ./a.out; <CR>
