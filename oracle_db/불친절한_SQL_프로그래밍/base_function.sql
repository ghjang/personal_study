-- 'CS'를 'Output' 콘솔 윈도에 출력한다.
CREATE OR REPLACE PROCEDURE DEBUG_PRINT(rows CS)
IS
BEGIN
    DBMS_OUTPUT.PUT_LINE('rows.COUNT = ' || rows.COUNT);

    FOR i IN 1..rows.COUNT LOOP
        DBMS_OUTPUT.put_line(rows(i));
    END LOOP;

    DBMS_OUTPUT.PUT(CHR(10));   -- newline
END;


-- '등차수열'의 n번째 항을 리턴
CREATE OR REPLACE FUNCTION NEXT_ARITHMETIC_N(init IN INTEGER, diff IN INTEGER, n IN INTEGER) RETURN INTEGER
IS
BEGIN
  RETURN init + diff * n;
END;
