		AREA test, DATA, READWRITE
		export	inputdata
		export	filtereddata
		export	length
		export	kalmanstate

inputdata			DCFS	1.0, 4.0, 7.0, 10.0, 12.0, 24.0, 30.0
filtereddata	FILL	50, 0xAB
length				DCB		7
kalmanstate		DCFS	0.0, 0.0, 0.1, 0.1, 0.1, 0.8, 1.2		;INITIAL STATES: x, k, q, r, p, f, h ...

							END	