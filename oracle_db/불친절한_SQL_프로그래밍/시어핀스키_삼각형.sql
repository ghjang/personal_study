-- 'level'의 'ASCII 삼각형'의 밑변의 길이를 리턴
CREATE OR REPLACE FUNCTION TRIANGLE_BOTTOM_WIDTH(level INTEGER) RETURN INTEGER
IS
    width INTEGER;
BEGIN
    IF level = 1 THEN
        width := 3;
    ELSE
        width := TRIANGLE_BOTTOM_WIDTH(level - 1) * 2 + 1;
    END IF;

    RETURN width;
END;


-- '시어핀스키 삼각형'을 리턴
CREATE OR REPLACE FUNCTION SIERPINSKI_TRIANGLE(level INTEGER) RETURN CS
IS
    preLevelTriangle CS;                        -- 이전 레벨의 삼각형
    preLevelTriangleBottomWidth INTEGER;        -- 'preLevelTriangle'의 밑변의 길이
    curLevelTriangle CS;                        -- 현재 레벨의 삼각형
    curLevelTriangleBottomWidth INTEGER;        -- 'curLevelTriangle'의 밑변의 길이
    upperTrianglePartPaddingWidth INTEGER;      -- 현재 레벨의 삼각형의 upper tringle part의 padding width
BEGIN
    IF level = 1 THEN   -- base case
        curLevelTriangle := CS(' * ',
                               '***');
    ELSE
        SELECT COLUMN_VALUE
        BULK COLLECT INTO preLevelTriangle
        FROM SIERPINSKI_TRIANGLE(level - 1);

        preLevelTriangleBottomWidth := TRIANGLE_BOTTOM_WIDTH(level - 1);
        curLevelTriangleBottomWidth := TRIANGLE_BOTTOM_WIDTH(level);
        upperTrianglePartPaddingWidth := TRUNC(curLevelTriangleBottomWidth / 4) + 1;

        DEBUG_PRINT(preLevelTriangle);

        SELECT r
        BULK COLLECT INTO curLevelTriangle
        FROM (SELECT LPAD(
                        RPAD(COLUMN_VALUE, preLevelTriangleBottomWidth + upperTrianglePartPaddingWidth, ' '),
                        preLevelTriangleBottomWidth + upperTrianglePartPaddingWidth * 2, ' '
                     ) AS r                                         -- upper triangle part
              FROM TABLE(preLevelTriangle)
                    UNION
              SELECT COLUMN_VALUE || ' ' || COLUMN_VALUE AS r       -- lower triangle parts
              FROM TABLE(preLevelTriangle));
    END IF;

    RETURN curLevelTriangle;
END;
