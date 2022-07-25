/*
	*
	**
	***
	****
	*****
	******
	*******
	********
	*********
 */
SELECT LPAD('*', LEVEL, '*')
FROM DUAL
CONNECT BY LEVEL < 10;


/*
	*********
	********
	*******
	******
	*****
	****
	***
	**
	*
 */
SELECT LPAD('*', 10 - LEVEL, '*')
FROM DUAL
CONNECT BY LEVEL < 10;


/*
	         *
	        **
	       ***
	      ****
	     *****
	    ******
	   *******
	  ********
	 *********
 */
SELECT LPAD(LPAD('*', LEVEL, '*'), 9, ' ')
FROM DUAL
CONNECT BY LEVEL <= 9;


/*
	**********
	 *********
	  ********
	   *******
	    ******
	     *****
	      ****
	       ***
	        **
	         *
 */
SELECT LPAD(LPAD('*', 10 - LEVEL, '*'), 9, ' ')
FROM DUAL
CONNECT BY LEVEL <= 9;
