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
