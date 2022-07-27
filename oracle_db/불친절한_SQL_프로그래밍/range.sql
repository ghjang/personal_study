-- 'rStart'와 'rEnd' 사이의 '등차수열'을 리턴
CREATE OR REPLACE FUNCTION RANGE(rStart IN INTEGER, rEnd IN INTEGER, diff IN INTEGER DEFAULT 1) RETURN XS
IS
    invalid_diff_value EXCEPTION;
    PRAGMA EXCEPTION_INIT(invalid_diff_value, -20000);   -- NOTE: '-20000'과 '-20999' 사이의 값을 지정해야한다.

    retVal XS;
BEGIN
    IF diff <= 0 THEN
        raise_application_error(-20000, 'diff must be greater than 0');
    END IF;

    -- NOTE: 'FUNCTION' 내부에서 'WITH 절'을 사용해 그 하위에 'NEXT_ARITHMETIC_N'을 정의할 수 없다(?).
    -- FIXME: 아래의 중복된 NEXT_ARITHMETIC_N 함수 호출을 제거하는 방법을 찾아볼 것. 필요하다면 'PL/SQL'의 'FOR LOOP' 같은 것을 이용해 변경할 것.

    IF rStart <= rEnd THEN
        SELECT NEXT_ARITHMETIC_N(rStart, diff, LEVEL - 1)
        BULK COLLECT INTO retVal
        FROM DUAL
        CONNECT BY NEXT_ARITHMETIC_N(rStart, diff, LEVEL - 1) <= rEnd;
    ELSE
        SELECT NEXT_ARITHMETIC_N(rStart, -diff, LEVEL - 1)
        BULK COLLECT INTO retVal
        FROM DUAL
        CONNECT BY NEXT_ARITHMETIC_N(rStart, -diff, LEVEL - 1) >= rEnd;
    END IF;

    RETURN retVal;
END;


-- 'RANGE' 함수를 좀더 짧게 적어 사용하기 위해서 추가함.
CREATE SYNONYM R FOR RANGE;
