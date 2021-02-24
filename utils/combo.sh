#!/bin/bash

if [ -z "$1" ]
then
    echo "Please input A image path/name!"
    exit
fi


if [ ! -f "$1" ]; then
  echo "$1 file not exist"
  exit
fi

FOTA_DIR=$(dirname "${1}")
FOTA_NAME=$(basename "${1}")
FOTA_NAME_EXT="${FOTA_NAME##*.}"
FOTA_NAME_WITHOUT_EXT="${FOTA_NAME%.*}"
FOTA_NULL=$FOTA_DIR/null.bin
if [ -z "$2" ]
then
    touch $FOTA_NULL
fi
FOTA_TMP=$FOTA_DIR/fota_header.tmp

FOTA_GET_PROJECT_NAME="${FOTA_NAME_WITHOUT_EXT%_*}"
FOTA_USE_NAME=_fota.bin
FOTA_ALL=$FOTA_DIR/$FOTA_GET_PROJECT_NAME$FOTA_USE_NAME
if [ -f "$FOTA_TMP" ]; then
  rm $FOTA_TMP
fi

if [ -f "$FOTA_ALL" ]; then
  rm $FOTA_ALL
fi

MAJOR=00000001
MINOR=00000000
FOTA_SIZE_A=$(wc -c $1 | awk '{printf("%08x",$1)}')
if [ -z "$2" ]; then
FOTA_SIZE_B=$(wc -c $FOTA_NULL | awk '{printf("%08x",$1)}')
else
FOTA_SIZE_B=$(wc -c $2 | awk '{printf("%08x",$1)}')
fi
FOTA_MD5_A=$(md5sum $1 | awk '{printf("%32s",$1)}')
if [ "$FOTA_SIZE_B" == "00000000" ]
then
	MAGIC=84848711
	FOTA_MD5_B=00000000000000000000000000000000
else
	MAGIC=73737600
	FOTA_MD5_B=$(md5sum $2 | awk '{printf("%32s",$1)}')
fi
echo -n ${MAGIC:6:2}${MAGIC:4:2}${MAGIC:2:2}${MAGIC:0:2} > $FOTA_TMP
echo -n ${FOTA_SIZE_A:6:2}${FOTA_SIZE_A:4:2}${FOTA_SIZE_A:2:2}${FOTA_SIZE_A:0:2} >> $FOTA_TMP
echo -n ${FOTA_SIZE_B:6:2}${FOTA_SIZE_B:4:2}${FOTA_SIZE_B:2:2}${FOTA_SIZE_B:0:2} >> $FOTA_TMP
echo -n ${MAJOR:6:2}${MAJOR:4:2}${MAJOR:2:2}${MAJOR:0:2} >> $FOTA_TMP
echo -n ${MINOR:6:2}${MINOR:4:2}${MINOR:2:2}${MINOR:0:2} >> $FOTA_TMP
xxd -r -p $FOTA_TMP  > $FOTA_ALL
echo -n $FOTA_MD5_A >> $FOTA_ALL
echo -n $FOTA_MD5_B >> $FOTA_ALL
cat $1 $2 >> $FOTA_ALL 

if [ -f "$FOTA_TMP" ]; then
  rm $FOTA_TMP
fi

if [ -f "$FOTA_NULL" ]; then
  rm $FOTA_NULL
fi
exit 0

