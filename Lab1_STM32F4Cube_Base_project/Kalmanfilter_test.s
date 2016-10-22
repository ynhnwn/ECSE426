		AREA test, CODE, READONLY
		EXPORT	kalmantest
		IMPORT 	inputdata
		IMPORT	filtereddata
		IMPORT	kalmanstate
		IMPORT	kalmanfilterasm

kalmantest

		LDR				R0, =test_input
		VLDR.F32	S0, [R0]
		LDR				R1, =inputdata
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		
		LDR				R0, =init_state
		VLDR.F32	S0, [R0]
		LDR				R1, =kalmanstate
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1] 
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]
		ADD				R0, R0, #4
		ADD				R1, R1, #4
		VLDR.F32	S0, [R0]
		VSTR.F32	S0, [R1]

		LDR 			R0, =inputdata					;LOAD ADRESS OF INPUT DATA
		LDR				R1, =filtereddata				;LOAD ADRESS OF FILTERED DATA
		MOV				R2, #10									;LOAD ADRESS OF LENGTH
		LDR				R3, =kalmanstate				;LOAD ADRESS OF KALMANSTATE DATA
		LDR				R5,	=kalmanfilterasm		;
		
		BX				R5
		
		ALIGN
init_state		DCFS	0.0, 0.0, 0.1, 0.1, 0.1, 0.8, 1.2
test_input		DCFS	1.2, -0.9, 0.7, -0.9, 1.1, -0.8, 0.6, 0.8, -1.3, 0.0

		END