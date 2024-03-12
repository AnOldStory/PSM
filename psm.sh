#!/bin/bash

##################################
######## Must Run in BASH ########
##################################

#   
#   Problem Solving Manager V 2.1
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
ISVERBOSE=3

POSITIONAL_ARGS=()
RELATIVE_DIR=""
CANONICAL_DIR=""
FILE_DIR=""
TARGET_DIR=""
TARGET_FILE=""


function parseArg () {
    while [[ $# -gt 0 ]];
    do
        case $1 in
            # -b|--build|build)
            #     # build source code
            #     ISBUILD=true
            #     shift # past value
            #     ;;
            -f|--file|file)
                ISBUILD=true
                # ISTEST=true
                setDir "$@"
                shift # -d
                shift # dir...
                ;;
            # -t|--test|test)
            #     # test with testcase
            #     ISBUILD=true
            #     ISTEST=true
            #     shift # past value
            #     ;;
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
                shift # past argument
                ;;
            -*|--*)
                .log 3 "Unknown option $1"
                exit 1
                ;;
            # ''|*[!0-9]*)
            #     .log 3 "Question Number is required."
            #     exit 1
            #     ;;
            *)
                .log 3 "Unknown arg $1"
                # QUESTION_NUMBER="$1"
                shift # past argument
                ;;
        esac
    done
}

function setDir() {
    .log 7 "Set Directory"

    .log 7 'PARAM:' $0 # psm.sh

    FILE_ARG="$2"
    .log 7 'FILE ARG :' "$FILE_ARG"

    TARGET_DIR=`dirname "$FILE_ARG"`
    .log 7 'Target Dir:' $TARGET_DIR # -> target base 

    TARGET_FILE=`basename "$FILE_ARG"`
    .log 7 'Target File:' $TARGET_FILE

    RELATIVE_DIR=`dirname "$0"`
    .log 7 'RELATIVE DIR:' $RELATIVE_DIR # running position directory -> terminalbase

    CANONICAL_DIR=`readlink -f "$RELATIVE_DIR"`
    .log 7 'CANONICAL DIR:' $CANONICAL_DIR # absolute directory
}

######
###### Testing
######

function testAll () {
    .log 6 "Test Dir $TARGET_DIR/input in $@"
    for test in "$TARGET_DIR"/input/*
    do
        if [ -e "$test" ]; then 
            .log 6 "Run Test with $test"
            cat "$test" | "$@" > "$TARGET_DIR"/output/$(basename "$test")
            if [ $? -ne 0 ]; then
                .log 3 "Error in $test"
                exit 1
            else
                .log 2 "------$test------"
                cat "$TARGET_DIR"/output/$(basename "$test")
                .log 2 "------$test------"
            fi
        fi 
    done        
}


######
###### Building Script with each language 
######

function buildScript () {
    .log 6 "Checking Main File At $TARGET_DIR"

    if [ -n "$TARGET_FILE" ]; then
        file=$TARGET_FILE
    else
        file=`find $TARGET_DIR -name Main.*` # find file in archived
        # file=`find . -type f | grep -E "/(Main|Solution)"` # include Solution
    fi

    if [[ ! -e $TARGET_DIR/$file ]]; then
        .log 3 "File not exists. [$TARGET_DIR/$file]"
        exit 1
    fi

    .log 6 "Build Start with [$file]"
    case ${file##*.} in ## check file extension && build
        c)
            gcc "$TARGET_DIR"/*.c -o "$TARGET_DIR/bin"
            testAll "$TARGET_DIR/bin"
        ;;
        cpp)
            g++ "$TARGET_DIR"/*.cpp -o "$TARGET_DIR/bin"
            testAll "$TARGET_DIR/bin"
        ;;
        java)
            javac "$TARGET_DIR"/*.java
            TARGET_FILE=$(grep -l -r --include='*.java' 'public static void main(String\[\] args)' "$TARGET_DIR" | xargs -d '\n' basename -s .java)
            # testAll java "$TARGET_DIR/$TARGET_FILE"
            testAll java -cp "$TARGET_DIR" "$TARGET_FILE"
        ;;
        *)
            .log 3 "Unsupported file extension."
            # exit 1
        ;;
    esac
}


######
###### Making Clean
######

function before_clean () {
    .log 6 "Clear Before Temp File"
    rm -rf "$TARGET_DIR/output"
    mkdir "$TARGET_DIR/output"
}

function after_clean () {
    .log 6 "Clear After Temp File"
    rm -f "$TARGET_DIR/bin"
    rm -rf "$TARGET_DIR"/*.class
}

function main() {
    parseArg "$@"

    .log 7 "Clean before start"
    before_clean

    if [[ $ISBUILD == "true" ]]; then 
        .log 7 "Build Start"
        buildScript     
    fi

    # if [[ $ISTEST == "true" ]]; then
    #     .log 7 "Test Start"
    #     testAll
    # fi

    if [[ $ISPRESERVE == "false" ]]; then
        .log 7 "Clean after Start"
        after_clean
    fi

    echo "Success!"
}

main "$@"


 


 
