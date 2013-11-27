	
	Underexposed=samples/underexposed.JPG
	Overexposed=samples/overexpose.JPG
	Normal=samples/normal.JPG
	NUME_PROG=main
	OUT_HDR=hdr_out.JPG
	

#	export OMP_SCHEDULE="dynamic"
	export OMP_NUM_THREADS=$1
	./$NUME_PROG $Underexposed $Normal $Overexposed $OUT_HDR
