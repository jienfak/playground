" Jien's VIM color file.
" Jien: Jien FAK <jienfak@protonmail.com>.
" (originally looked at slate.)
set background=dark
highlight clear

	" ---------------------
	" For checking folding.
	" ---------------------

let colors_name = "jien"
hi Normal       guifg=White guibg=grey15
hi Cursor       guibg=khaki guifg=slategrey ctermbg=white ctermfg=black
hi TermCursor   cterm=reverse
" :hi 
hi CursorLine   gui=bold
hi VertSplit    guibg=#c2bfa5 guifg=grey40 gui=none ctermfg=grey ctermbg=grey
hi Folded       guibg=black guifg=grey40 ctermfg=black ctermbg=blue
hi FoldColumn   guibg=black guifg=grey20 ctermfg=4 ctermbg=7
hi IncSearch    guifg=green guibg=black cterm=none ctermfg=yellow ctermbg=green
hi ModeMsg      guifg=goldenrod cterm=none ctermfg=black ctermbg=yellow
hi MoreMsg      guifg=SeaGreen ctermfg=darkgreen
hi NonText      guifg=RoyalBlue guibg=grey15 cterm=bold ctermfg=blue
hi Question     guifg=springgreen ctermfg=green
hi Search       guibg=peru guifg=wheat cterm=none ctermfg=black ctermbg=yellow
hi SpecialKey   guifg=yellowgreen ctermfg=darkgreen
hi StatusLine   guibg=#c2bfa5 guifg=black gui=none cterm=none ctermfg=black ctermbg=red
hi StatusLineNC guibg=#c2bfa5 guifg=grey40 gui=none cterm=reverse
hi Title        guifg=gold gui=bold cterm=bold ctermfg=yellow
hi Statement    guifg=CornflowerBlue ctermfg=red
hi Visual       gui=none guifg=khaki guibg=olivedrab cterm=reverse
hi WarningMsg   guifg=salmon ctermfg=1
hi String       guifg=SkyBlue ctermfg=darkcyan
hi Comment      cterm=bold ctermfg=yellow
hi Constant     ctermfg=darkblue
hi Special      ctermfg=brown
hi Identifier   ctermfg=LightGreen
hi Include      ctermfg=red
hi PreProc      ctermfg=red
hi Operator                 ctermfg=magenta
hi Define                   ctermfg=yellow
hi Type                     ctermfg=green
hi Function                 ctermfg=brown
hi Structure                ctermfg=green
hi LineNr                   ctermfg=black ctermbg=yellow
hi Ignore       cterm=bold  ctermfg=7
hi Todo         guifg=orangered guibg=yellow2
hi Directory    ctermfg=darkcyan
hi ErrorMsg     cterm=bold guifg=White guibg=Red cterm=bold ctermfg=7 ctermbg=1
hi VisualNOS    cterm=bold,underline
hi WildMenu     ctermfg=yellow ctermbg=black "ctermfg=0 ctermbg=
hi DiffAdd      ctermbg=4
hi DiffChange   ctermbg=5
hi DiffDelete   cterm=bold ctermfg=4 ctermbg=6
hi DiffText     cterm=bold ctermbg=1
hi Underlined   cterm=underline ctermfg=5
hi Error        cterm=bold ctermfg=7 ctermbg=1
hi SpellErrors  cterm=bold ctermfg=7 ctermbg=1
hi Special      ctermfg=red