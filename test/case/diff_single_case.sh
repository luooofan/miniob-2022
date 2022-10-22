#!/bin/bash
set -ex
diff ${@:2} -i result/$1.result result_tmp/$1.result.tmp
