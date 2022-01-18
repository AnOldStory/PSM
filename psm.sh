#!/bin/sh
echo 'PARAM:' $0 # psm.sh
RELATIVE_DIR=`dirname "$0"`
echo 'Dir:' $RELATIVE_DIR #running position directory

CANONICAL_DIR=`readlink -f $RELATIVE_DIR`
echo 'CANONICAL DIR:' $CANONICAL_DIR # absolute directory


APPS_SCRIPT=/test/apps/  
                                                                                
if [ -e "$APPS_SCRIPT" ]; then
    SCRIPT_LIST=`ls $APPS_SCRIPT`
    for SCRIPT in $SCRIPT_LIST; do
        $APPS_SCRIPT/$SCRIPT
    done                                                     
fi

# first argument evalutaion
case $1 in
    test)
        find $CANONICAL_DIR/archive/ -name $2.*
        
        ;;
    push)
        ;;
    *)
        echo "need first argument"
        ;;
esac

# if [ $1 -eq "commit" ]; then
    
# elif [ $1 -eq "push" ]; then

# elif [ $1 -eq "test" ]; then 
    
# else 
    
# fi