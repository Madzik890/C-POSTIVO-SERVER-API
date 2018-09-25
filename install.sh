#!/bin/sh

cp lib/libcrypto.so.0.9.8 /lib64
cp lib/libssl.so.0.9.8 /lib64

ldconfig

echo "Copied all files." 

make all
