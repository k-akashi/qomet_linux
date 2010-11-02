#!/bin/sh -x

text_file=$1
tmp_file=$1.tmp

awk 'BEGIN{
    FS = " ";
}
NR <= 2 {
	print $0;
}
NR >= 3 {
    time = $1;
    delay = $18;
	if(time ~ /^[1,3,5,7,9].[0-9]+$/) {
		delay = "1000.0000";
    	print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
	else {
		delay = "1.0000";
	    print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
}' ${text_file} > test1.out