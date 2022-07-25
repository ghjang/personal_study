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


-- '문자열' 리스트 생성용 타입 'CS'를 생성
CREATE OR REPLACE TYPE CS IS TABLE OF VARCHAR2(256);

-- '밑변'의 길이가 'bottomWidth'인 '기본 아스키 삼각형'을 리턴
CREATE OR REPLACE FUNCTION BASE_ASCII_TRIANGLE(bottomWidth IN INTEGER) RETURN CS
IS
    retVal CS;
BEGIN
    SELECT LPAD('*', LEVEL, '*')
    BULK COLLECT INTO retVal
    FROM DUAL
    CONNECT BY LEVEL <= bottomWidth;

    RETURN retVal;
END;

/*
    '기본 아스키 삼각형'을 이용해서 '다이아몬드' 출력

             *
            ***        
           *****       
          *******      
         *********     
        ***********    
       *************   
      ***************  
     ***************** 
    *******************
    *******************
     ***************** 
      ***************  
       *************   
        ***********    
         *********     
          *******      
           *****       
            ***        
             *
*/
WITH t1 AS (
    SELECT * FROM BASE_ASCII_TRIANGLE(9)
)
, t2 AS (
    SELECT * FROM t1 ORDER BY COLUMN_VALUE DESC
)
, rightHalfDiamond AS (
    SELECT RPAD(COLUMN_VALUE, 9, ' ') r FROM t1
        UNION ALL
    SELECT RPAD(COLUMN_VALUE, 9, ' ') r FROM t2
)
, fullDiamond AS (
    SELECT LPAD('*', 10, ' ') FROM DUAL
        UNION ALL
    SELECT REVERSE(d.r) || '*' || d.r FROM rightHalfDiamond d
        UNION ALL
    SELECT LPAD('*', 10, ' ') FROM DUAL
)
SELECT * FROM fullDiamond;
