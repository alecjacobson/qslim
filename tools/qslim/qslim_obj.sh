#!/bin/bash
INPUT=$1
OUTPUT=$2
shift
shift
grep "^[vf] " $INPUT | \
  sed -e "s/^f *\([0-9][0-9]*\)\/[^ ]*  *\([0-9][0-9]*\)\/[^ ]*  *\([0-9][0-9]*\)\/.*/f \1 \2 \3/g" | \
  `dirname $0`/qslim $@ -M smf -o .qvis_obj.smf -
cat .qvis_obj.smf | grep "^[vf]" > $OUTPUT
