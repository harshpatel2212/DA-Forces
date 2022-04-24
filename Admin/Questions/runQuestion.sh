#! /bin/bash

qID=$1
qPath="./$qID"
uID=$2
uPath="../users/$uID"
iId="$qPath/in.txt"
oId="$qPath/out.txt"
vID="$qPath/verdict.txt"

gcc $uPath/$qID/submission.c -o $uPath/$qID/submission.out
./$uPath/$qID/submission.out < $iId > $vID

if [ $? == 0 ]
then
    cmp --silent $oId $vID && echo 'All Correct' || echo 'Wrong Answer'
else
    cat $vID
fi

rm $vID
rm $uPath/$qID/submission.out