# ALang 
#--------------------------

Func some_func1( a, b, c )
    Print( "Hello from FIXED argument func" )
    Print( a )
    Print( b )
    Print( c )

    Func nested_func( a )
        Print( "Hello from NESTED function" )
        Print( a )

    nested_func( 2 )

Func some_func2( arg ... )
    Print( "Hello from VARIABLE argument func" )
  
age = 12.5
name = "Ram Poudel"
address = '1400 Penselvenia Ave, DC'

some_func1( address, age, name )

some_func2( 1, 2, 3, 4, 5 )
