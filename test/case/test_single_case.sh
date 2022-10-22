#!/bin/bash
set -ex

pushd test/case/
python3 miniob_test.py \
        --test-case-dir=./test  \
        --test-case-scores=case-scores.json \
        --test-result-dir=result \
        --test-result-tmp-dir=./result_tmp \
        --use-unix-socket \
        --code-type=none \
        --db-base-dir=../../build \
        --db-data-dir=./miniob_data_test \
        --db-config=../../etc/observer.ini \
        --target-dir=./miniob \
        --log=stdout \
        --test-cases=$1
popd
