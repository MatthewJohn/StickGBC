# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.

#!/bin/bash

set -e
set -x


# Obtain artifact
# Attempt for 60 seconds
for i in {1..60}
do
  { curl --output main.gb --fail http://pub-jenkins.dock.studios/artifacts/GameboyDev/StickGBC/Build_PR/$gitlabMergeRequestLastCommit/main.gb && break; } || true
  sleep 1
done

if [ ! -f main.gb ]
then
  echo Unable to obtain artifact
  exit 1
fi

tests_failed=0

for test_name in test_{1..4}
do
  mkdir $test_name

  set +e
  docker run --rm -e INPUT_DIR=/app/${test_name} -e OUTPUT_DIR=/output/${test_name} -e ROM_DIR=/output -e ROM_FILE=main.gb -e DELAY=20 -e BGB_TIMEOUT=30 -v `pwd`:/output stickrpg-automated-test-tool:latest
  if [ "$?" != "0" ]
  then
    tests_failed=1
  fi
  set -e
done

if [ "$tests_failed" != "0" ]
then
  echo One or more tests failed
  exit 1
fi

