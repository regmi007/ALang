#!/usr/bin/ALang
#---------------------------------------------------------------
# ALang is a case-sensitive typeless language.
#---------------------------------------------------------------

# This is how you define a function
Func some_func1( a, b, c )
    Print( "Hello from FIXED argument func", a, b )

    # You can define nested function too.
    Func nested_func( a )
        Print( "Hello from NESTED function", a )

    # Function call
    nested_func( c )

# This function takes variable number of arguments
Func some_func2( arg ... )
    Print( "Hello from VARIABLE argument func", arg )

# Define variables
age = 12.5
name = "Ram Poudel"
address = '1400 Pennsylvania Ave, DC'

# Function call
some_func1( address, age, name )
some_func2( 1, 2, 'Hi', 4, 'Hello World' )

