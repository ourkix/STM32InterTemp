    INCLUDE asmcore.h


    ;��ջ8�ֽڶ���
    PRESERVE8

    AREA    ASMCORE, CODE, READONLY
    THUMB


    ;��������: ʵ�������л�����, ���Ĵ������ݵ���ǰ�����ջ��, �ӽ�Ҫ���������ջ��
    ;          ȡ���Ĵ�������ֵ����ת����Ҫ��������ִ��.
    ;��ڲ���: none.
    ;�� �� ֵ: none.
WLX_ContextSwitch
	
	SUB   R13 , #0x08
	STMDB R13! , {R0-R12}
	MRS   R0   , XPSR
	STMDB R13! , {R0}
	MOV   R0   , R13
	ADD   R0  , #0x40
	STMDB R0   , {R0,R14}
	
	
	;���浱ǰ�����ָ��ֵ
	LDR   R0   , =gpuiCurTaskSpAddr
	LDR   R1   , [R0]
	CMP   R1   , #0
	BEQ   GETNEXTTASKSP
	STR   R13  , [R1] 
	
	
GETNEXTTASKSP
	;��ȡ��Ҫ��������Ķ�ջ��Ϣ������������
	LDR   R0   , =guiNextTaskSp
	LDR   R13  , [R0]
	LDMIA R13! , {R0}
	MSR   XPSR , R0
	LDMIA R13!  , {R0-R12}
	ADD   R13   , #0x04
	LDMIA R13! ,  {R14}
	BX    R14
	
	
	
	
	
	
    ALIGN

    END
