-- '등차수열'의 n번째 항을 리턴
CREATE OR REPLACE FUNCTION NEXT_ARITHMETIC_N(init IN INTEGER, diff IN INTEGER, n IN INTEGER) RETURN INTEGER
IS
BEGIN
  RETURN init + diff * n;
END;


--
CREATE OR REPLACE FUNCTION RANGE(rStart IN INTEGER, rEnd IN INTEGER, step IN INTEGER DEFAULT 1) RETURN XS
IS
    invalid_range EXCEPTION;
    invalid_step_value EXCEPTION;
    PRAGMA EXCEPTION_INIT(invalid_range, -20000);   -- NOTE: '-20000'과 '-20999' 사이의 값을 지정해야한다.
    PRAGMA EXCEPTION_INIT(invalid_step_value, -20001);

    retVal XS;
BEGIN
    IF rStart >= rEnd THEN
        raise_application_error(-20000, 'Invalid range');
    END IF;

    IF step <= 0 THEN
        raise_application_error(-20001, 'Invalid step value');
    END IF;

    -- NOTE: 'FUNCTION' 내부에서 'WITH 절'을 사용해 그 하위에 'NEXT_ARITHMETIC_N'을 정의할 수 없다(?).
    SELECT NEXT_ARITHMETIC_N(rStart, step, LEVEL - 1)
    BULK COLLECT INTO retVal
    FROM DUAL
    CONNECT BY NEXT_ARITHMETIC_N(rStart, step, LEVEL - 1) < rEnd;

    RETURN retVal;
END;
