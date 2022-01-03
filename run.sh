#!/bin/sh
echo 'PARAM:' $0
RELATIVE_DIR=`dirname "$0"`
echo 'Dir:' $RELATIVE_DIR

CANONICAL_DIR=`readlink -f $RELATIVE_DIR`
echo 'CANONICAL DIR:' $CANONICAL_DIR


APPS_SCRIPT=/test/apps/  
                                                                                
if [ -e "$APPS_SCRIPT" ]; then
    SCRIPT_LIST=`ls $APPS_SCRIPT`
    for SCRIPT in $SCRIPT_LIST; do
        $APPS_SCRIPT/$SCRIPT
    done                                                     
fi