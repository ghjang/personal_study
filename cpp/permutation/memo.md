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

//==============================================================================
/*
{ }
*/


/*
{ 0 }
*/


/*
{ 0, 1 }

{ 0, 1 } <== complete


{ 0, 1 }

{ 1, 0 }

{ 1, 0 } <== complete
*/


/*
{ 0, 1, 2 }

{ 0, 2, 1 }
{ 0, 1, 2 } <== complete


{ 0, 1, 2 }

{ 1, 0, 2 }
{ 1, 2, 0 }

{ 1, 0, 2 } <== complete


{ 1, 0, 2 }

{ 2, 0, 1 }
{ 2, 1, 0 }

{ 2, 0, 1 } <== complete
*/

/*
- current index
- element index to swap

{ 0, 1, 2, 3 }

{ 0, 1, 3, 2 }
{ 0, 3, 1, 2 }
{ 0, 3, 2, 1 }
{ 0, 2, 3, 1 }
{ 0, 2, 1, 3 }

{ 0, 1, 2, 3 } <== complete

{ 0, 1, 2, 3 }

{ 1, 0, 2, 3 }
{ 1, 0, 3, 2 }
{ 1, 3, 0, 2 }
{ 1, 3, 2, 0 }
{ 1, 2, 3, 0 }
{ 1, 2, 0, 3 }

{ 1, 0, 2, 3 } <== complete

{ 1, 0, 2, 3 }

{ 2, 0, 1, 3 }
{ 2, 0, 3, 1 }
{ 2, 3, 0, 1 }
{ 2, 3, 1, 0 }
{ 2, 1, 3, 0 }
{ 2, 1, 0, 3 }

{ 2, 0, 1, 3 } <== complete

{ 2, 0, 1, 3 }

{ 3, 0, 1, 2 }
{ 3, 0, 2, 1 }
{ 3, 2, 0, 1 }
{ 3, 2, 1, 0 }
{ 3, 1, 2, 0 }
{ 3, 1, 0. 2 }

{ 3, 0, 1, 2 } <== complete
*/


//== revision
/*
{ 0, 1, <2, <3>> }

{ 0, 1, <2, <3>> } <== complete

{ 0, 1, <2, 3> }

{ 0, 1, <3, <2>> }

{ 0, 1, <3, <2>> } <== complete

{ 0, <1, 2, 3> }

{ 0, 3, 1, 2 }
{ 0, 3, 2, 1 }
{ 0, 2, 3, 1 }
{ 0, 2, 1, 3 }

{ 0, 1, 2, 3 } <== complete

{ 0, 1, 2, 3 }

{ 1, 0, 2, 3 }
{ 1, 0, 3, 2 }
{ 1, 3, 0, 2 }
{ 1, 3, 2, 0 }
{ 1, 2, 3, 0 }
{ 1, 2, 0, 3 }

{ 1, 0, 2, 3 } <== complete

{ 1, 0, 2, 3 }

{ 2, 0, 1, 3 }
{ 2, 0, 3, 1 }
{ 2, 3, 0, 1 }
{ 2, 3, 1, 0 }
{ 2, 1, 3, 0 }
{ 2, 1, 0, 3 }

{ 2, 0, 1, 3 } <== complete

{ 2, 0, 1, 3 }

{ 3, 0, 1, 2 }
{ 3, 0, 2, 1 }
{ 3, 2, 0, 1 }
{ 3, 2, 1, 0 }
{ 3, 1, 2, 0 }
{ 3, 1, 0. 2 }

{ 3, 0, 1, 2 } <== complete
*/

/*
1. add the given sequence to the result.
2. process until the completion condition.
3. ignore the completion sequence.
4. continue with the next swap.
*/


    while (cnt < num_of_perm) {
        if (sp < N - 1) {
            ++sp;
            stack[sp] = sp;
        }
        else if (N - 1 == sp) {
            std::copy(seq.begin(), seq.end(), indices[cnt++].begin());

            
        }
        else {
            std::copy(seq.begin(), seq.end(), indices[cnt++].begin());
        }
    }



    for (auto k = j; k < N1; ++k) {
        permutation_index_impl(seq, i + 1, i + 1, out, cnt);
    }

    // reversing the sub-sequence
    for (auto k = i + 1; k < N1 - 1; ++k) {
        for (auto l = N1 - 1; l > k; --l) {
            std::swap(seq[k], seq[l]);
            std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, " "));
        }
    }

    std::copy(seq.begin(), seq.end(), out[cnt++].begin());
    std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, " "));




template <std::size_t N1, std::size_t N2>
void permutation_index_impl(std::array<int, N1> & seq, int i, int j,
                            std::array<std::array<int, N1>, N2> & out,
                            int & cnt)
{
    if (i == j) {
        std::copy(seq.begin(), seq.end(), out[cnt++].begin());

        std::cout << "temp1: ";
        std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

        return;
    }

    int k = i;
    int l = i + 1;
    for ( ; l <= j; ++l) {
        permutation_index_impl(seq, i + 1, j, out, cnt);

        std::swap(seq[k], seq[l]);

        std::cout << "temp2: ";
        std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }

    std::reverse(seq.begin() + i, seq.end());
}
