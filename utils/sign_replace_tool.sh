#!/bin/sh

EC_NEW_PUB_KEY_RAW_FILE=./security/public.pem
EC_SIGNATURE_DER_FILE=./security/signature.bin
EC_SIGNATURE_TXT_FILE=./security/sign
EC_SIGNATURE_RAW_FILE=./security/sign.bin
OUTPUT_FILE_NAME=$2
NEW_PUB_KEY_C_FILE=./security/pub.c
NEW_PUB_KEY_RAW_FILE=./security/pub.key
NEW_PUB_KEY_TXT_FILE=./security/pub.txt

if [ $# -eq 3 ]; then
    INPUT_FILE=$1
if [ ! -f "$INPUT_FILE" ]; then
    echo "$INPUT_FILE doesn't exist"
    exit
fi
    TRUNC_INPUT_FILE=$INPUT_FILE.trunc
    
    EC_PARAM_FILE=$3
if [ ! -f "$EC_PARAM_FILE" ]; then
    echo "$EC_PARAM_FILE doesn't exist"
    exit
fi
else
    echo "Usage: $0 <input file name> <output file name> <pem file name>"
    exit
fi

#######################################
#  1. Gen new pub key
#######################################
openssl ec -in $EC_PARAM_FILE -noout -text -conv_form compressed| awk '{if (NR < 10) print $0}'| tail -3| sed 's/:/, 0x/g'| sed 's/^    /    0x/g'| sed 's/ 0x$//g'| awk 'NR == 1 { print "uint8_t pub_Q[33] = {" $0; next } { print } END {print "};"}' > $NEW_PUB_KEY_C_FILE
openssl ec -in $EC_PARAM_FILE -noout -text -conv_form compressed| awk '{if (NR < 10) print $0}'| tail -3| sed 's/://g' > $NEW_PUB_KEY_TXT_FILE
echo "0000D0" >> $NEW_PUB_KEY_TXT_FILE
xxd -p -r $NEW_PUB_KEY_TXT_FILE $NEW_PUB_KEY_RAW_FILE
#######################################
#  2. Extract new pub key
#######################################
openssl ec -in $EC_PARAM_FILE -pubout -out $EC_NEW_PUB_KEY_RAW_FILE

#######################################
#  3. Sign bl
#######################################
dd bs=64 skip=1 if=$INPUT_FILE of=$TRUNC_INPUT_FILE
openssl dgst -sha512 -sign $EC_PARAM_FILE -binary -keyform PEM < $TRUNC_INPUT_FILE > $EC_SIGNATURE_DER_FILE
#######################################
#  4. Gen bl signature image (64B)
#######################################
openssl asn1parse -in $EC_SIGNATURE_DER_FILE -inform DER| awk '{print $7}'| sed 's/://g'| tail -2 > $EC_SIGNATURE_TXT_FILE
xxd -r -p $EC_SIGNATURE_TXT_FILE $EC_SIGNATURE_RAW_FILE

#######################################
#  5. Gen full image
#######################################
rm -f $OUTPUT_FILE_NAME
cat $EC_SIGNATURE_RAW_FILE $TRUNC_INPUT_FILE >> $OUTPUT_FILE_NAME

#######################################
#  7. Remove tmp files
#######################################
rm -f $EC_SIGNATURE_TXT_FILE
rm -f $EC_SIGNATURE_DER_FILE
rm -f $EC_SIGNATURE_RAW_FILE
rm -f $NEW_PUB_KEY_TXT_FILE
rm -f $TRUNC_INPUT_FILE
