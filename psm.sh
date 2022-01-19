#!/bin/bash

##################################
######## Must Run in BASH ########
##################################

#   
#   Problem Solving Manager V 1.0
#

######
###### log manager 
######
function .log () {
  LOG_LEVELS=([0]="emerg" [1]="alert" [2]="crit" [3]="err" [4]="warning" [5]="notice" [6]="info" [7]="debug")
  local LEVEL=${1}
  shift
  if [[ ${ISVERBOSE} -ge ${LEVEL} ]]; then
    echo "[${LOG_LEVELS[$LEVEL]}]" "$@"
  fi
}

######
###### parse argument && set global 
######

ISBUILD=false
ISTEST=false
ISPRESERVE=false
ISVERBOSE=0

POSITIONAL_ARGS=()
RELATIVE_DIR=""
CANONICAL_DIR=""
SOURCE_DIR=""
TESTCASE_DIR=""


function parseArg () {
    while [[ $# -gt 0 ]];
    do
        case $1 in
            -b|--build|build)
                # build source code
                ISBUILD=true
                QUESTION_NUMBER="$2"
                shift # past argument
                shift # past value
                ;;
            -t|--test|test)
                # test with testcase
                ISBUILD=true
                ISTEST=true
                QUESTION_NUMBER="$2"
                shift # past argument
                shift # past value
                ;;
            -s|--save|save)
                # TODO: commit & push code to repositiory 
                ;;
            -v|--verbose|verbose)
                # print info
                ISVERBOSE=7
                shift # past argument
                ;;
            -p|--preserve|preserve)
                # preserve binary code
                ISPRESERVE=true
                echo "tset"
                shift # past argument
                ;;
            -*|--*)
                .log 3 "Unknown option $1"
                exit 1
                ;;
            *)
                POSITIONAL_ARGS+=("$1") # save positional argument
                shift # past argument
                ;;
        esac
    done
}

function setDir() {
    .log 7 'PARAM:' $0 # psm.sh
    RELATIVE_DIR=`dirname "$0"`
    .log 7 'Dir:' $RELATIVE_DIR #running position directory

    CANONICAL_DIR=`readlink -f $RELATIVE_DIR`
    .log 7 'CANONICAL DIR:' $CANONICAL_DIR # absolute directory

    SOURCE_DIR=$CANONICAL_DIR/archive
    TESTCASE_DIR=$CANONICAL_DIR/testcase
}


######
###### Building Script with each language 
######

function buildScript () {
    .log 6 "Checking Question Number..."
    file=`find $SOURCE_DIR -name $QUESTION_NUMBER.*` # find file in archived
    if [[ -e $SOURCE_DIR/$file ]]; then # TODO: Why Working reverse??
        .log 3 "File not exists. [$file]"
        exit 1
    fi

    .log 6 "Build Start with [$file]"
    case ${file##*.} in ## check file extension && build
        c)
            gcc $SOURCE_DIR/$QUESTION_NUMBER.c -o $CANONICAL_DIR/$QUESTION_NUMBER
        ;;
        cpp)
            g++ $SOURCE_DIR/$QUESTION_NUMBER.cpp -o $CANONICAL_DIR/$QUESTION_NUMBER
        ;;
        *)
            .log 3 "Unsupported file extension."
            exit 1
        ;;
    esac
}

######
###### Testing
######

function testAll () {
    .log 6 "Run Test with $TESTCASE_DIR/input"
    for test in "$TESTCASE_DIR"/input/*
    do
        if [ -e $test ]; then 
            cat $test | $CANONICAL_DIR/$QUESTION_NUMBER > $TESTCASE_DIR/output/$(basename $test)
        fi 
    done        
}

######
###### Making Clean
######

function before_clean () {
    .log 6 "Clear Before Temp File"
    rm -rf $TESTCASE_DIR/output
    mkdir $TESTCASE_DIR/output
}

function after_clean () {
    .log 6 "Clear After Temp File"
    rm -f $CANONICAL_DIR/$QUESTION_NUMBER
}

function main() {
    parseArg $@

    setDir

    before_clean

    if [[ $ISBUILD ]]; then 
        buildScript     
    fi

    if [[ $ISTEST ]]; then
        testAll
    fi

    if [[ ! $ISPRESERVE ]]; then
        after_clean
    fi

    echo "Success!"
}

main $@