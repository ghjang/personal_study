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
