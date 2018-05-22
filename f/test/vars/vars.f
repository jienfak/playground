        program numbers
                implicit none
                ! Variables

                integer n,i,s

                ! Body of numbers

                s=0
                write(*,*) 'Enter n'
                read (*,*) n
                if (n.le.0) then
                        write(*,*)
                else
                        do i = 1,n

