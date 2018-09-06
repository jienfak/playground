package mod ;
require Exporter ;
@ISA = qw(Exporter) ;
@EXPORT = qw(func1) ;

{
	sub func1(){
		print "func1\n" ;
	}

	1;
}

