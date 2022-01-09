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

mkdir test_{1..3}

set +e
docker run --rm -e INPUT_DIR=/app/test_1 -e OUTPUT_DIR=/output/test_1 -e ROM_DIR=/output -e ROM_FILE=main.gb -e DELAY=40 -e BGB_TIMEOUT=60 -v `pwd`:/output stickrpg-automated-test-tool:latest
test_1_failed=$?

docker run --rm -e INPUT_DIR=/app/test_2 -e OUTPUT_DIR=/output/test_2 -e ROM_DIR=/output -e ROM_FILE=main.gb -e DELAY=40 -e BGB_TIMEOUT=60 -v `pwd`:/output stickrpg-automated-test-tool:latest
test_2_failed=$?

docker run --rm -e INPUT_DIR=/app/test_3 -e OUTPUT_DIR=/output/test_3 -e ROM_DIR=/output -e ROM_FILE=main.gb -e DELAY=40 -e BGB_TIMEOUT=60 -v `pwd`:/output stickrpg-automated-test-tool:latest
test_3_failed=$?

docker run --rm -e INPUT_DIR=/app/test_4 -e OUTPUT_DIR=/output/test_4 -e ROM_DIR=/output -e ROM_FILE=main.gb -e DELAY=40 -e BGB_TIMEOUT=60 -v `pwd`:/output stickrpg-automated-test-tool:latest
test_4_failed=$?



set -e

if [ "$test_1_failed" != "0" ] || [ "$test_1_failed" != "0" ] || [ "$test_1_failed" != "0" ] || [ "$test_4_failed" != "0" ]
then
  echo One or more tests failed
  exit 1
fi

