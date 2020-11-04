    INCLUDE asmcore.h


    ;堆栈8字节对齐
    PRESERVE8

    AREA    ASMCORE, CODE, READONLY
    THUMB


    ;函数功能: 实现任务切换功能, 将寄存器备份到当前任务堆栈中, 从将要运行任务堆栈中
    ;          取出寄存器保存值并跳转到将要运行任务执行.
    ;入口参数: none.
    ;返 回 值: none.
WLX_ContextSwitch
	
	SUB   R13 , #0x08
	STMDB R13! , {R0-R12}
	MRS   R0   , XPSR
	STMDB R13! , {R0}
	MOV   R0   , R13
	ADD   R0  , #0x40
	STMDB R0   , {R0,R14}
	
	
	;保存当前任务的指针值
	LDR   R0   , =gpuiCurTaskSpAddr
	LDR   R1   , [R0]
	CMP   R1   , #0
	BEQ   GETNEXTTASKSP
	STR   R13  , [R1] 
	
	
GETNEXTTASKSP
	;获取将要运行任务的堆栈信息并运行新任务
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
