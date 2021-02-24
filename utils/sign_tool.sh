#!/bin/sh

EC_PARAM_FILE=./security/ec_param.pem
EC_PUB_KEY_FILE=./security/public.pem
EC_SIGNATURE_DER_FILE=./security/signature.bin
EC_SIGNATURE_TXT_FILE=./security/sign
EC_SIGNATURE_RAW_FILE=./security/sign.bin
OUTPUT_FILE_NAME=$2
PUB_KEY_C_FILE=./security/pub.c
PUB_KEY_RAW_FILE=./security/pub.key
PUB_KEY_TXT_FILE=./security/pub.txt

if [ $# -eq 2 ]; then
    TARGET_FILE=$1
if [ ! -f "$TARGET_FILE" ]; then
    echo "$TARGET_FILE doesn't exist"
    exit
fi
else
    echo "Usage: $0 <input file name> <output file name>"
    exit
fi

#######################################
#  1. Gen key pair if needed
#######################################
if [ ! -f "$EC_PARAM_FILE" ]; then
    echo "$EC_PARAM_FILE doesn't exist"
    openssl ecparam -genkey -name prime256v1 -out $EC_PARAM_FILE -param_enc explicit
fi

openssl ec -in $EC_PARAM_FILE -noout -text -conv_form compressed| awk '{if (NR < 10) print $0}'| tail -3| sed 's/:/, 0x/g'| sed 's/^    /    0x/g'| sed 's/ 0x$//g'| awk 'NR == 1 { print "uint8_t pub_Q[33] = {" $0; next } { print } END {print "};"}' > $PUB_KEY_C_FILE
openssl ec -in $EC_PARAM_FILE -noout -text -conv_form compressed| awk '{if (NR < 10) print $0}'| tail -3| sed 's/://g' > $PUB_KEY_TXT_FILE
openssl ec -in $EC_PARAM_FILE -noout -text -conv_form compressed| awk '{if (NR < 10) print $0}'| tail -3| tr -d '\n'| sed 's/$/\n/g'| sed 's/:/\n/g'| sed 's/^    //g'| sed 's/^/0x/g'| ./utils/crc_tool.sh >> $PUB_KEY_TXT_FILE
echo "D0" >> $PUB_KEY_TXT_FILE
xxd -p -r $PUB_KEY_TXT_FILE $PUB_KEY_RAW_FILE

#######################################
#  2. Extract pub key
#######################################
openssl ec -in $EC_PARAM_FILE -pubout -out $EC_PUB_KEY_FILE

#######################################
#  3. Sign bl
#######################################
openssl dgst -sha512 -sign $EC_PARAM_FILE -binary -keyform PEM < $TARGET_FILE > $EC_SIGNATURE_DER_FILE
#######################################
#  4. Gen bl signature image (64B)
#######################################
openssl asn1parse -in $EC_SIGNATURE_DER_FILE -inform DER| awk '{print $7}'| sed 's/://g'| tail -2 > $EC_SIGNATURE_TXT_FILE
xxd -r -p $EC_SIGNATURE_TXT_FILE $EC_SIGNATURE_RAW_FILE

#######################################
#  5. Gen full bl header image (128B)
#######################################
rm -f $OUTPUT_FILE_NAME
cat $EC_SIGNATURE_RAW_FILE >> $OUTPUT_FILE_NAME

#######################################
#  6. Remove tmp files
#######################################
rm -f $EC_SIGNATURE_TXT_FILE
rm -f $EC_SIGNATURE_DER_FILE
rm -f $EC_SIGNATURE_RAW_FILE
rm -f $PUB_KEY_TXT_FILE
