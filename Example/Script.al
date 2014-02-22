# ALang 
#--------------------------

Func my_func( arr1, arr2 )

    i = 0

    While i < Size( arr1 )  # Size() is used to find the length of an array.

        res = arr1[ i ] + arr1[ i ]
        
        Print( res )

arr1 = 1, 'A'
arr2 = 4, 'B'

arr3 = 1.8, 'Hello-', arr1
arr4 = 2.2, "-World", arr2

my_func( arr1, arr2 )
