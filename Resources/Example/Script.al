#!/usr/bin/ALang
#---------------------------------------------------------------
# ALang is a case-sensitive typeless language.
#---------------------------------------------------------------

# This is how you define a function
Func fixed_arg_func( a, b, c )
    Print( "Hello from FIXED argument func", a, b )

    # You can define nested function too.
    Func nested_func( a )
        Print( "Hello from NESTED function", a )

    # Function call
    nested_func( c )

# This function takes variable number of arguments
Func var_arg_func( arg ... )
    Print( "Hello from VARIABLE argument func" )
    Print( "Printing Arg ", arg )

    Print()

    # Create an array
    # Empty array can be created like
    # arr = [] or arr = Array()
    arr = [ 'Creating', 2.34, "Array" ]

    #Iterate Array
    For( val : arr )
        Print( val )

    Print()

    return arr
    
    # Create structure
    # Empty structure can be created like
    # arr = {} or arr = Struct()
    # Only string as a key is supported.
    #st = { 'a' : 12, 'b' : arr }
    #Print( st )

    #Iterate Structure
    #For( key, val : st )
    #    Print( key, val, "\n" )

# Define variables
age = 12.5
name = "Ram Poudel"
address = '1400 Pennsylvania Ave, DC'
zip = 31117

# Function call
fixed_arg_func( address, age, name )
var_arg_func( age, name, address, zip, 1, 'Hello', 3, 4, "World", 3 )

