	AREA kalman, CODE, READONLY
		EXPORT Kalmanfilter_asm
		 
Kalmanfilter_asm
		PUSH {R4-R12}
		MOV		R4, 	#0

;A POINTER TO THE INPUT DATA ARRAY PLACED IN R0
;A POINTER TO THE FILTER DATA ARRAY PLACED IN R1
;THE ARRAYS' LENGTH PLACED IN R2
;A POINTER TO THE KALMAN FILTER(STRUCT)


;MAKING OF KALMAN FILTER
;PREDIT
				ADD	R5, R0, R4, LSL #2


;CONSTAN VALUES
;		VLDR.F32	S9, 	=0.8			;VALUE OF f
;		VLDR.F32	S10,	=1.2			;VALUE OF h
;		VLDR.F32	S11,	=0.64			;VALUE OF f^2
;		VLDR.F32	S12,	=1.44			;VALUE OF h^2
		
;GETTING INTIAL INPUT FROM USER
;		VLDR.F32	s4, [R3, #0]		;q
;		VLDR.F32	s5, [R3, #4]		;r 
;		VLDR.F32	S6, [R3, #8]		;x 
;		VLDR.F32	S7, [R3, #12]		;p 
;		VLDR.F32	S8, [R3, #16]		;k


PREDICTION
		VMUL.F32	S6, S6, S9			;Xk|k-1 = F*Xk-1|k-1
		
		VMUL.F32	S3, S11, S7			;Pk|k-1 = (F^2)*Pk-1|k-1
		VADD.F32	S3, S3, S4			;Pk|k-1 = (F^2)*Pk-1|k-1 + Q
		
UPDATE
		VMUL.F32	S0, S7, S10
		VMUL.F32	S1, S7, S12
		
		
		
		END