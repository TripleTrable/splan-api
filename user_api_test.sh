#!/bin/sh

echo "run server"
./build/src/splan-server&

echo "wait for server"
sleep 2

pid=$(pidof splan-server)
echo "server pid: ${pid}"

echo "test health endpoint"
health=$(curl "http://127.0.0.1:8080/health")
expected_healt="{\"message\": \"Not implemented yet\"}"
if [[ $health != $expected_healt ]]; then
    kill $pid
    exit -1
fi


echo "test faculties endpoint"
faculties=$(curl "http://127.0.0.1:8080/faculties")
expected_faculties="{\"message\": \"Not implemented yet\"}"

if [[ $faculties != $expected_faculties ]]; then
    echo "faculties endpoint test failed"
    kill $pid
    exit -1
fi

echo "test timetable endpoint"
timetable=$(curl "http://127.0.0.1:8080/timetable")
expected_timetable="{\"message\": \"Not implemented yet\"}"

if [[ $timetable != $expected_timetable ]]; then
    echo "timetable endpoint test failed"
    kill $pid
    exit -1
fi

echo "test semesters endpoint"
semesters=$(curl "http://127.0.0.1:8080/semesters")
expected_semesters="{\"message\": \"Not implemented yet\"}"

if [[ $semesters != $expected_semesters ]]; then
    echo "semesters endpoint test failed"
    kill $pid
    exit -1
fi

echo "test non existing endpoint"
not_found=$(curl "http://127.0.0.1:8080/not_found")
expected_not_found="{\"message\": \"404 Not found\"}"

if [[ $not_found != $expected_not_found ]]; then
    echo "non existing endpoint test failed"
    kill $pid
    exit -1
fi

echo "kill ${pid}"
kill ${pid}
