#!/bin/sh -x

text_file=$1
tmp_file=$1.tmp

awk 'BEGIN{
    FS = " ";
	delay = "1.0000"
}
NR <= 2 {
	print $0;
}
NR >= 3 {
    time = $1;
    delay = $18;
	if(time ~ /^[0-9]+\.00/) {
		delay = "1.0000";
    	print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
	else if(time ~ /^[0-9]+\.[1,9]0/) {
		delay = "200.0000";
    	print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
	else if(time ~ /^[0-9]+\.[2,8]0/) {
		delay = "400.0000";
	    print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
	else if(time ~ /^[0-9]+\.[3,7]0/) {
		delay = "600.0000";
	    print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
	else if(time ~ /^[0-9]+\.[4,6]0/) {
		delay = "800.0000";
	    print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
	else if(time ~ /^[0-9]+\.50/) {
		delay = "1000.0000";
	    print time, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, "1000000000.00", "0.0000", delay, "0.0000";
	}
}' ${text_file} > test3.out
