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
    Print( "Hello from VARIABLE argument func" )
    Print( "Printing Array: ", arg )

    Print( "" )
    Print( "Iterating Array: " )
    # Iterating array
    For( v : arg )
        Print( v )

# Define variables
age = 12.5
name = "Ram Poudel"
address = '1400 Pennsylvania Ave, DC'
zip = 31117

# Function call
some_func1( address, age, name )
some_func2( age, name, address, zip, 1, 2, 3, 4, 5 )

