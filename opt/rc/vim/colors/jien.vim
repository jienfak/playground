" Jien's VIM color file.
" Jien: Jien FAK <jienfak@protonmail.com>.
" (originally looked at slate.)
set background=dark
if exists("syntax_on")
	syntax reset
endif
"highlight clear

let colors_name = "jien"
hi Normal       cterm=none             ctermfg=white             ctermbg=none
hi Cursor       cterm=bold             ctermfg=black             ctermbg=red
hi TermCursor   cterm=reverse          ctermfg=none              ctermbg=none
hi CursorLine   cterm=bold             ctermfg=none              ctermbg=none
hi VertSplit    cterm=none             ctermfg=grey              ctermbg=grey
hi Folded       cterm=none             ctermfg=black             ctermbg=yellow
hi FoldColumn   cterm=none             ctermfg=yellow            ctermbg=white
hi IncSearch    cterm=none             ctermfg=yellow            ctermbg=green
hi ModeMsg      cterm=none             ctermfg=black             ctermbg=yellow
hi MoreMsg      cterm=none             ctermfg=darkgreen         ctermbg=none
hi NonText      cterm=none             ctermfg=darkgrey          ctermbg=none
hi Question     cterm=none             ctermfg=green             ctermbg=none
hi Search       cterm=none             ctermfg=black             ctermbg=yellow
hi SpecialKey   cterm=none             ctermfg=darkgreen         ctermbg=none
hi StatusLine   cterm=none             ctermfg=black             ctermbg=red
hi StatusLineNC cterm=reverse          ctermfg=none              ctermbg=none
hi Title        cterm=bold             ctermfg=yellow            ctermbg=none
hi Statement    cterm=none             ctermfg=blue              ctermbg=none
hi Visual       cterm=none             ctermfg=black             ctermbg=red
hi WarningMsg   cterm=none             ctermfg=1                 ctermbg=none
hi String       cterm=none             ctermfg=darkcyan          ctermbg=none
hi Comment      cterm=none             ctermfg=yellow            ctermbg=none
hi Constant     cterm=bold             ctermfg=red               ctermbg=none
hi Special      cterm=none             ctermfg=red               ctermbg=none
hi Identifier   cterm=none             ctermfg=lightgreen        ctermbg=none
hi Include      cterm=none             ctermfg=red               ctermbg=none
hi PreProc      cterm=none             ctermfg=red               ctermbg=none
hi Operator     cterm=none             ctermfg=lightblue         ctermbg=none
hi Define       cterm=none             ctermfg=red               ctermbg=none
hi Type         cterm=none             ctermfg=green             ctermbg=none
hi Function     cterm=none             ctermfg=darkmagenta       ctermbg=none
hi Structure    cterm=none             ctermfg=green             ctermbg=none
hi LineNr       cterm=none             ctermfg=black             ctermbg=yellow
hi Ignore       cterm=bold             ctermfg=7                 ctermbg=none
hi Directory    cterm=none             ctermfg=darkcyan          ctermbg=none
hi ErrorMsg     cterm=bold             ctermfg=7                 ctermbg=1
hi VisualNOS    cterm=bold,underline   ctermfg=none              ctermbg=none
hi WildMenu     cterm=none             ctermfg=black             ctermbg=yellow
hi DiffAdd      ctermbg=4              ctermfg=none              ctermbg=none
hi DiffChange   ctermbg=5              ctermfg=none              ctermbg=none
hi DiffDelete   cterm=bold             ctermfg=4                 ctermbg=6
hi DiffText     cterm=bold             ctermfg=none              ctermbg=1
hi Underlined   cterm=underline        ctermfg=5                 ctermbg=none
hi Error        cterm=bold             ctermfg=7 ctermbg=1       ctermbg=none
hi SpellErrors  cterm=bold             ctermfg=7 ctermbg=1       ctermbg=none
"hi CircleScobs  cterm=bold ctermfg=red
