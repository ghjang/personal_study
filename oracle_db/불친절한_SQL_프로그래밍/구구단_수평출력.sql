-- 굳이 'PARTITION BY' 절을 사용해서 작성함.
WITH xs AS (
    SELECT (LEVEL + 1) AS n
    FROM DUAL
    CONNECT BY LEVEL < 9
)
, ys AS (
    SELECT n FROM xs
        UNION
    SELECT 1 FROM DUAL
)
, fs AS (
    SELECT x.n AS a, y.n AS b
    FROM xs x, ys y
)
SELECT DISTINCT LISTAGG(f.a || 'x' || f.b || '=' || f.a * f.b, '      ')
                    WITHIN GROUP(ORDER BY f.a)
                    OVER(PARTITION BY f.b)
FROM fs f;


/*
    위의 쿼리에서 'DISTINCT'와 'PARTITION BY' 절을 제거하고
    'GROUP BY' 절을 추가하여 결과를 출력하였다.
*/
WITH xs AS (
    SELECT (LEVEL + 1) AS n
    FROM DUAL
    CONNECT BY LEVEL < 9
)
, ys AS (
    SELECT n FROM xs
        UNION
    SELECT 1 FROM DUAL
)
, fs AS (
    SELECT x.n AS a, y.n AS b
    FROM xs x, ys y
)
SELECT LISTAGG(
            f.a || 'x' || f.b || '=' || f.a * f.b,
            '      '
        ) WITHIN GROUP(ORDER BY f.a)
FROM fs f
GROUP BY f.b;


-- 사용자 정의 타입 'XS'를 사용해 '구구단' 출력
WITH factors AS ( 
    SELECT
        xs.column_value AS a
      , ys.column_value AS b
    FROM
        XS(2, 3, 4, 5, 6, 7, 8, 9) xs
      , XS(1, 2, 3, 4, 5, 6, 7, 8, 9) ys
)
SELECT LISTAGG(
            f.a || 'x' || f.b || '=' || f.a * f.b,
            '      '
        ) WITHIN GROUP(ORDER BY f.a)
FROM factors f
GROUP BY f.b;


/*
    'LISTAGG'의 구분자 인수를 사용하지 않고
    'RPAD' 함수를 이용해서 적당한 출력폭을 지정함.

    NOTE: '12'는 '구구단'에서 가장 긴 문자열의 '2배' 길이이다.
            ex.> 9x9=81     <== 6자
*/
WITH factors AS ( 
	SELECT
		xs.column_value AS a
	  , ys.column_value AS b
	FROM
		XS(2, 3, 4, 5, 6, 7, 8, 9) xs
	  , XS(1, 2, 3, 4, 5, 6, 7, 8, 9) ys
)
SELECT LISTAGG(
			RPAD(f.a || 'x' || f.b || '=' || f.a * f.b, 12)
		) WITHIN GROUP(ORDER BY f.a)
FROM factors f
GROUP BY f.b;


-- 'RANGE' 함수를 사용해서 '구구단' 출력
SELECT LISTAGG(
			RPAD(a.n || 'x' || b.n || '=' || a.n * b.n, 12)
		) WITHIN GROUP(ORDER BY a.n)
FROM R(2, 9) a, R(1, 9) b
GROUP BY b.n;
