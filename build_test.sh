#!/bin/bash
# make sure pushd, popd, flex, bison, cmake, make, python3 is available
set -ex
set +f

# flex & bison
pushd ./src/observer/sql/parser/
flex --header-file=lex.yy.h lex_sql.l
bison -d -b yacc_sql yacc_sql.y # -v --debug
popd

# make
mkdir -p build
pushd build
# make clean
cmake .. -DDEBUG=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make -j8
popd

if [ "$1" == "test" ]; then
  # test component
  pushd build/bin
  for exe in $(pwd)/*_test; do
    if [ $exe != $(pwd)/"client_performance_test" ] && [ $exe != $(pwd)/"clog_test" ]; then
      $exe
    fi
  done
  popd

  # test case without build
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
          --log=stdout
  popd
fi
