        program nums
                implicit none
                integer n, i,s

                s=0
                write (*,*) 'Enter n'
                read (*,*) n
                if(n.le.0) then
                        write (*,*) 'minus or something'
                else
                        do i=1,n
                        s=s+i
                        end do
                        write(*,*) 'sum=', s
                end if
        end


