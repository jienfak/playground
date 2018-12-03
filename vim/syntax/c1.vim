
" Useful C keywords.

syn keyword cStatement   toto break return continue asm
syn keyword cLabel       case default
syn keyword cConditional if else switch

syn keyword cTodo        contained TODO FIXME XXX

if !exists("c_no_c99")
 	syn keyword cConstant
endif

hi def link cUserLabel
