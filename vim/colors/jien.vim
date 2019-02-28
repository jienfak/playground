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
hi CursorLine   cterm=bold
hi VertSplit    ctermfg=grey ctermbg=grey
hi Folded       ctermfg=black ctermbg=yellow
hi FoldColumn   ctermfg=black ctermbg=white
hi IncSearch    cterm=none ctermfg=yellow ctermbg=green
hi ModeMsg      cterm=none ctermfg=black ctermbg=yellow
hi MoreMsg      ctermfg=darkgreen
hi NonText      cterm=bold ctermfg=darkgrey
hi Question     ctermfg=green
hi Search       cterm=none ctermfg=black ctermbg=yellow
hi SpecialKey   ctermfg=darkgreen
hi StatusLine   cterm=none ctermfg=white ctermbg=red
hi StatusLineNC cterm=reverse
hi Title        cterm=bold  ctermfg=yellow
hi Statement    cterm=bold  ctermfg=cyan
hi Visual       cterm=reverse
hi WarningMsg                     ctermfg=1
hi String                         ctermfg=darkcyan
hi Comment                        ctermfg=yellow
hi Constant                       ctermfg=red cterm=bold
hi Special                        ctermfg=brown
hi Identifier                     ctermfg=LightGreen
hi Include                        ctermfg=red
hi PreProc                  ctermfg=red
hi Operator                 ctermfg=lightblue
hi Define                   ctermfg=lightblue
hi Type                     ctermfg=green
hi Function                 ctermfg=magenta
hi Structure                ctermfg=green
hi LineNr                   ctermfg=black ctermbg=yellow
hi Ignore       cterm=bold  ctermfg=7
"hi Todo         guifg=orangered guibg=yellow2
hi Directory    ctermfg=darkcyan
hi ErrorMsg     cterm=bold         ctermfg=7 ctermbg=1
hi VisualNOS    cterm=bold,underline
hi WildMenu                 ctermfg=black ctermbg=yellow
hi DiffAdd      ctermbg=4
hi DiffChange   ctermbg=5
hi DiffDelete   cterm=bold ctermfg=4 ctermbg=6
hi DiffText     cterm=bold ctermbg=1
hi Underlined   cterm=underline ctermfg=5
hi Error        cterm=bold ctermfg=7 ctermbg=1
hi SpellErrors  cterm=bold ctermfg=7 ctermbg=1
"hi Special      ctermfg=red
