-- 't_stragg' OBJECT 타입 생성
CREATE OR REPLACE TYPE t_stragg AS OBJECT (
	g_str VARCHAR2(32767)

  , STATIC FUNCTION ODCIAggregateInitialize(sctx IN OUT t_stragg) RETURN NUMBER

  , MEMBER FUNCTION ODCIAggregateIterate(self IN OUT t_stragg, value IN VARCHAR2) RETURN NUMBER

  , MEMBER FUNCTION ODCIAggregateTerminate(
  								self IN t_stragg
  							  , retVal OUT VARCHAR2
  							  , flags IN NUMBER
  					) RETURN NUMBER

  , MEMBER FUNCTION ODCIAggregateMerge(
  								self IN OUT t_stragg
  							  , sctx2 IN t_stragg
  					) RETURN NUMBER
);


-- 't_stragg' OBJECT 타입내 선언된 함수 본문 정의
CREATE OR REPLACE TYPE BODY t_stragg
IS
  STATIC FUNCTION ODCIAggregateInitialize(sctx IN OUT t_stragg) RETURN NUMBER
  IS
  BEGIN
	 sctx := t_stragg(NULL);
	 RETURN ODCICONST.SUCCESS;
  END;

  MEMBER FUNCTION ODCIAggregateIterate(self IN OUT t_stragg, value IN VARCHAR2) RETURN NUMBER
  IS
  BEGIN
	  IF (g_str IS NOT NULL) THEN
	  	g_str := g_str || ',' || value;
	  ELSE
	  	g_str := value;
	  END IF;

	  RETURN ODCICONST.SUCCESS;
  END;

  MEMBER FUNCTION ODCIAggregateTerminate(
							self IN t_stragg
						  , retVal OUT VARCHAR2
						  , flags IN NUMBER
  				  ) RETURN NUMBER
  IS
  BEGIN
	  retVal := g_str;
	  RETURN ODCICONST.SUCCESS;
  END;

  MEMBER FUNCTION ODCIAggregateMerge(
							self IN OUT t_stragg
						  , sctx2 IN t_stragg
  				  ) RETURN NUMBER
  IS
  BEGIN
      IF (sctx2.g_str IS NOT NULL) THEN
          self.g_str := self.g_str || ',' || sctx2.g_str;
      END IF;

      RETURN ODCICONST.SUCCESS;
  END;
END;


-- 't_stragg' OBJECT 타입을 사용하여 'stragg' 함수 정의
CREATE OR REPLACE FUNCTION stragg(value IN VARCHAR2) RETURN VARCHAR2
PARALLEL_ENABLE AGGREGATE USING t_stragg;
