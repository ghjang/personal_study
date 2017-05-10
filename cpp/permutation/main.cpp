/*
{ 0, 1 }
{ 1, 0 }

//====
1.
{ 0, 1 }

2.
{ 1 - 0, 1 - 1 }

==>
{ 1, 0 }

3.
{ 0, 1 }
{ 1, 0 }
*/

/*
{ 0, 1, 2 }
{ 0, 2, 1 }
{ 1, 0, 2 }
{ 1, 2, 0 }
{ 2, 0, 1 }
{ 2, 1, 0 }

//====
1. take the first 3-row.
{ 0, 1, 2 }
{ 0, 2, 1 }
{ 1, 0, 2 }

2. generate the rest 3-row from the matrix genrated at the above step-1.
{ 2 - 1, 2 - 0, 2 - 2 }     <== difference between 2 and the 3rd row elements
{ 2 - 0, 2 - 2, 2 - 1 }     <== difference between 2 and the 2nd row elements
{ 2 - 0, 2 - 1, 2 - 2 }     <== difference between 2 and the 1st row elements

this becomes:
{ 1, 2, 0 }
{ 2, 0, 1 }
{ 2, 1, 0 }

3. concatenating the first and the second results in:
{ 0, 1, 2 }
{ 0, 2, 1 }
{ 1, 0, 2 }
{ 1, 2, 0 }
{ 2, 0, 1 }
{ 2, 1, 0 }
*/

/*
//== interesting
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 0, 3, 2, 1 }
{ 0, 2, 3, 1 }
{ 0, 2, 1, 3 }

//== reversing steps, huh?
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 3, 0, 1, 2 }
{ 3, 0, 2, 1 }
{ 3, 2, 0, 1 }
{ 3, 2, 1, 0 }

//== 1, 2, 3, 4 in reverse order
1
{ 0, 1, 2, 3 }  <== just for the last 3

2
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }

3
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 0, 3, 2, 1 }
{ 0, 2, 3, 1 }
{ 0, 2, 1, 3 }

--
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 } <== reversed at this point. wrong!!

{ 0, 3, 2, 1 } <== re-reversing
{ 0, 2, 3, 1 }
{ 0, 2, 1, 3 }
{ 0, 1, 2, 3 } <== completed condition

4
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 3, 0, 1, 2 }
{ 3, 0, 2, 1 }
{ 3, 2, 0, 1 }
{ 3, 2, 1, 0 } <== revered at this point

{ 2, 3, 1, 0 }
{ 2, 1, 3, 0 }
{ 2, 1, 0, 3 }
{ 2, 0, 1, 3 }
{ 2, 0, 3, 1 }
{ 2, 0, 1, 3 }
*/

//========
/*
{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 0, 3, 2, 1 } <== reversed
{ 0, 2, 3, 1 } <== re-reversing
{ 0, 2, 1, 3 }
{ 0, 1, 2, 3 } <== 1st completion

--
{ 0, 1, 2, 3 }

{ 1, 0, 2, 3 }
{ 1, 0, 3, 2 }
{ 1, 3, 0, 2 }
{ 1, 3, 2, 0 }
{ 1, 2, 3, 0 }
{ 1, 2, 0, 3 }
{ 1, 0, 2, 3 } <== 2nd completion

--
{ 1, 0, 2, 3 }

{ 2, 0, 1, 3 }
{ 2, 0, 3, 1 }
{ 2, 3, 0, 1 }
{ 2, 3, 1, 0 }
{ 2, 1, 3, 0 }
{ 2, 1, 0, 3 }
{ 2, 0, 1, 3 } <== 3rd completion

--
{ 2, 0, 1, 3 } <== note that 2 is the array index of the 4th elememt, 3.
                    absolute index & 'relative index + base index'

{ 3, 0, 1, 2 }
{ 3, 0, 2, 1 }
{ 3, 2, 0, 1 }
{ 3, 2, 1, 0 }
{ 3, 1, 2, 0 }
{ 3, 1, 0, 2 }
{ 3, 0, 1, 2 } <== 4th completion

--
note: need to re-order the sub-order. re-think the algorithm.

{ 0, 1, 2, 3 }
{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 0, 3, 2, 1 } <== reversed
{ 0, 2, 3, 1 } <== re-reversing
{ 0, 2, 1, 3 }

{ 1, 0, 2, 3 }
{ 1, 0, 3, 2 }
{ 1, 3, 0, 2 }
{ 1, 3, 2, 0 }
{ 1, 2, 3, 0 }
{ 1, 2, 0, 3 }

{ 2, 0, 1, 3 }
{ 2, 0, 3, 1 }
{ 2, 3, 0, 1 }
{ 2, 3, 1, 0 }
{ 2, 1, 3, 0 }
{ 2, 1, 0, 3 }

{ 3, 0, 1, 2 }
{ 3, 0, 2, 1 }
{ 3, 2, 0, 1 }
{ 3, 2, 1, 0 }
{ 3, 1, 2, 0 }
{ 3, 1, 0, 2 }
*/

/*
- reversing
- re-reversing
- completion condition
- sub-element
- recursion
*/
