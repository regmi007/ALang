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
    Print( "Printing Arg ", arg )

    Print()
    # Create an array
    # Empty array can be created like
    # arr = [] or arr = Array()
    arr = [ 's', 1, 2.34 ]

    Print()    
    # Create structure
    # Empty structure can be created like
    # arr = {} or arr = Struct()
    # Only string as a key is supported.
    st = { 'a' : 12, 'b' : arr }
    Print( st )

    #Iterate Structure
    For( key, val : st )
        Print( key, val, "\n" )

    #Iterate Array
    For( val : arr )
        Print( val )

# Define variables
age = 12.5
name = "Ram Poudel"
address = '1400 Pennsylvania Ave, DC'
zip = 31117

# Function call
some_func1( address, age, name )
some_func2( age, name, address, zip, 1, 'Hello', 3, 4, "World", 3 )

