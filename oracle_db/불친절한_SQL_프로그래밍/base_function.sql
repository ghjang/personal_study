-- '등차수열'의 n번째 항을 리턴
CREATE OR REPLACE FUNCTION NEXT_ARITHMETIC_N(init IN INTEGER, diff IN INTEGER, n IN INTEGER) RETURN INTEGER
IS
BEGIN
  RETURN init + diff * n;
END;
